#ifndef MAINVIEWER_H
#define MAINVIEWER_H

#include <QMainWindow>
#include <QMenuBar>
#include <QFileDialog>
#include <QThread>
#include <QtQuick/QQuickView>
#include <QVBoxLayout>
#include <QQuickPaintedItem>
#include <QPainter>

#include "picloader.h"
#include "picviewer.h"


class MainViewer : public QMainWindow
{
    Q_OBJECT

public:
    MainViewer(QWidget *parent = 0);
    ~MainViewer();

signals:
    void updateImage(QImage*);

public slots:
    void onClickedOpen();

private slots:
    void onPicLoaded(QImage*);
    void onClickedLeftButt();
    void onClickedRightButt();

private:
    void initGui();
    void initQml();

private:
    QWidget*    m_central;

    QMenuBar*   m_menuBar;
    QMenu*      m_menuFile;
    QAction*    m_actOpen;
    QAction*    m_actExit;

    QString     m_fileName;

    QThread*    m_thread;
    PicLoader*  m_loader;
    PicViewer*  m_picViewer;
    QQuickView* m_qmlView;

    QVBoxLayout*   m_layout;
};

#endif // MAINVIEWER_H
