#include "mainviewer.h"
#include "defines.h"


MainViewer::MainViewer(QWidget *parent)
: QMainWindow(parent)
{
    setFixedSize(APP_WIDTH, APP_HEIGHT);
    initGui();
    initQml();

    // создаем загрузчик и засовываем его в рабочий поток
    m_thread = new QThread(this);
    m_loader = new PicLoader(m_picViewer);
    m_loader->moveToThread(m_thread);
    QObject::connect( m_loader, SIGNAL(loadedImage(QImage*)), SLOT(onPicLoaded(QImage*)) );
    m_thread->start();
}

MainViewer::~MainViewer()
{
    m_thread->exit();
    delete m_loader;
    delete m_qmlView;
    m_thread->deleteLater();
}

void MainViewer::initGui()
{
    // создаём меню File
    m_menuBar = new QMenuBar();
    setMenuBar(m_menuBar);
    m_menuFile = m_menuBar->addMenu(QString::fromUtf8("&File"));

    m_actOpen = new QAction(QString::fromUtf8("&Open folder"), m_menuBar);
    m_actOpen->setStatusTip(QString::fromUtf8("Open images directory"));
    m_actOpen->setShortcuts(QKeySequence::Open);
    QObject::connect(m_actOpen, SIGNAL(triggered()), this, SLOT(onClickedOpen()) );

    m_actExit = new QAction(QString::fromUtf8("&Exit"), m_menuBar);
    QObject::connect(m_actExit, SIGNAL(triggered()), this, SLOT(close()) );

    m_menuFile->addAction(m_actOpen);
    m_menuFile->addAction(m_actExit);

    // выбираем центральный виджет и слой
    m_central = new QWidget(this);
    setCentralWidget(m_central);

    m_layout = new QVBoxLayout(m_central);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_central->setLayout(m_layout);
}

void MainViewer::initQml()
{
    // подготовка работы с qml
    m_qmlView = new QQuickView();
    qmlRegisterType<PicViewer>("picviewer", 1, 0, "PicViewer");

    m_qmlView->setSource(QUrl(g_strMainQml));
    m_qmlView->setResizeMode(QQuickView::SizeRootObjectToView);

    QWidget* container = QWidget::createWindowContainer(m_qmlView, m_central);
    m_layout->addWidget(container);

    QQmlComponent component(m_qmlView->engine(), QUrl(g_strMainQml));
    if (component.status() != component.Ready)
    {
        foreach (QQmlError err, component.errors())
            qDebug() << "Error loading qml component: " << err.description();
        return;
    }

    // запоминаем объекты qml для последующей работы с ними
    QObject* object = m_qmlView->rootObject()->findChild<QObject*>("QmlPic");
    if (object)
        m_picViewer = (PicViewer*)object;

    m_picViewer->setLeftButton(m_qmlView->rootObject()->findChild<QObject*>("leftButton"));
    m_picViewer->setRightButton(m_qmlView->rootObject()->findChild<QObject*>("rightButton"));
    m_picViewer->setAnimLoader(m_qmlView->rootObject()->findChild<QObject*>("animLoading"));

    QObject::connect( m_picViewer->leftButton(), SIGNAL(clickedLeftButt()), this, SLOT(onClickedLeftButt()) );
    QObject::connect( m_picViewer->rightButton(), SIGNAL(clickedRightButt()), this, SLOT(onClickedRightButt()) );
}


void MainViewer::onClickedOpen()
{
    // отображаем окно открытия файла
    m_fileName = QFileDialog::getOpenFileName(
                this,
                QString::fromUtf8("Choose image or directory"),
                QString::fromUtf8(""),
                QString::fromUtf8("Image Files (*.png *.jpg)") );
    if (m_fileName.isEmpty())
        return;

    // требуем загрузить выбранную картинку
    QMetaObject::invokeMethod(m_loader, "loadPicture", Qt::QueuedConnection, Q_ARG(QString, m_fileName));

    // делаем видимой анимацию загрузки
    m_picViewer->startLoadAnimation();
}

void MainViewer::onPicLoaded(QImage *image)
{
    // картинка загружена, теперь отображаем её
    m_picViewer->stopLoadAnimation();
    m_picViewer->onUpdateImage(image);
}

void MainViewer::onClickedLeftButt()
{
    // требуем загрузить предыдущую картинку
    m_picViewer->startLoadAnimation();
    QMetaObject::invokeMethod(m_loader, "loadPrevPicture", Qt::QueuedConnection);
}

void MainViewer::onClickedRightButt()
{
    // требуем загрузить следующую картинку
    m_picViewer->startLoadAnimation();
    QMetaObject::invokeMethod(m_loader, "loadNextPicture", Qt::QueuedConnection);
}
