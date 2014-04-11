#ifndef PICLOADER_H
#define PICLOADER_H

#include <QObject>
#include <QImage>
#include <QDir>

#include "picviewer.h"

class PicLoader : public QObject
{
    Q_OBJECT
public:
    explicit PicLoader(PicViewer *viewer, QObject *parent = 0);

    void setNewDir(const QString& fileName);

signals:
    void loadedImage(QImage*);

public slots:
    void loadPicture(const QString &fileName);
    void loadPrevPicture();
    void loadNextPicture();

private:
    QDir        m_dir;
    QStringList m_fileList;
    QString     m_currentFile;

    PicViewer*  m_viewer;
};

#endif // PICLOADER_H
