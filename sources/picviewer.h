#ifndef PICVIEWER_H
#define PICVIEWER_H

#include <QQuickPaintedItem>
#include <QPainter>

/*----------------------------------------------------
    класс, работающий с отображением картинки в Qml
------------------------------------------------------*/
class PicViewer : public QQuickPaintedItem
{
    Q_OBJECT

public:
    PicViewer();
    ~PicViewer();

    void paint(QPainter *painter);

    void startLoadAnimation();
    void stopLoadAnimation();

    void setLeftButton(QObject *button);
    void setRightButton(QObject *button);
    QObject* leftButton();
    QObject* rightButton();

    void setAnimLoader(QObject *loader);
    QObject* animLoader();

signals:
    void clickedLeftButton();
    void clickedRightButton();

public slots:
    void onUpdateImage(QImage *image);

private:
    QImage*  m_image;
    QObject* m_leftButton;
    QObject* m_rightButton;
    QObject* m_animLoad;
};

#endif // PICVIEWER_H
