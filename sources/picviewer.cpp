#include "picviewer.h"
#include "defines.h"


PicViewer::PicViewer()
: QQuickPaintedItem()
, m_image(NULL)
, m_leftButton(NULL)
, m_rightButton(NULL)
, m_animLoad(NULL)
{
}

PicViewer::~PicViewer()
{
    delete m_image;
}

void PicViewer::paint(QPainter *painter)
{
    if (m_image == NULL)
        return;

    QImage* oldImage = m_image;
    m_image = new QImage(m_image->scaledToWidth(APP_WIDTH));
    delete oldImage;

    painter->drawImage(0, APP_HEIGHT/2 - m_image->height()/2, *m_image);

    if (m_leftButton)
        m_leftButton->setProperty("opacity", QVariant(0.7));
    if (m_rightButton)
        m_rightButton->setProperty("opacity", QVariant(0.7));
}

void PicViewer::startLoadAnimation()
{
    QMetaObject::invokeMethod(m_animLoad, "showLoading", Qt::QueuedConnection);
}

void PicViewer::stopLoadAnimation()
{
    QMetaObject::invokeMethod(m_animLoad, "hideLoading", Qt::QueuedConnection);
}

void PicViewer::setLeftButton(QObject *button)
{
    m_leftButton = button;
}

void PicViewer::setRightButton(QObject *button)
{
    m_rightButton = button;
}

QObject *PicViewer::leftButton()
{
    return m_leftButton;
}

QObject *PicViewer::rightButton()
{
    return m_rightButton;
}

void PicViewer::setAnimLoader(QObject *loader)
{
    m_animLoad = loader;
}

QObject *PicViewer::animLoader()
{
    return m_animLoad;
}

void PicViewer::onUpdateImage(QImage *image)
{
    QImage* oldImage = m_image;
    m_image = image;
    delete oldImage;
    update(QRect(0, 0, APP_WIDTH, APP_HEIGHT));
}
