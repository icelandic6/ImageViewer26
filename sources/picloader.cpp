#include "picloader.h"

#include <QDebug>
#include <QMessageBox>

PicLoader::PicLoader(PicViewer *viewer, QObject *parent)
: QObject(parent)
, m_viewer(viewer)
{
}

void PicLoader::setNewDir(const QString &fileName)
{
    // список файлов не будет обновляться на лету,
    // только при выборе нового файла через окно открытия
    int lastInd = fileName.lastIndexOf("/");
    if (lastInd == -1)
        lastInd = fileName.lastIndexOf("\\");

    m_dir.setPath(fileName.mid(0, lastInd));
    m_dir.setFilter(QDir::Files);
    m_dir.setSorting(QDir::Name);

    // выбираем только файлы типа jpg и png
    QStringList mask;
    mask << "*.jpg" << "*.png";

    m_dir.setNameFilters(mask);
    m_fileList = m_dir.entryList(mask);
}


void PicLoader::loadPicture(const QString &fileName)
{
    // запоминаем директорию и список её файлов
    setNewDir(fileName);
    m_currentFile = fileName.mid(fileName.lastIndexOf("/") + 1);

    // загружаем изображение
    QImage *image = new QImage(fileName);
    if (image->isNull())
    {
        QMessageBox::about(
            NULL,
            QString::fromUtf8("Failed loading"),
            QString::fromUtf8("Image wasn't loaded correctly.\nPlease, try again."));
        return;
    }

    emit loadedImage(image);
}

void PicLoader::loadPrevPicture()
{
    // загружаем предыдущее по списку директории изображение, если сейчас не граничное
    if (!m_fileList.contains(m_currentFile) || (m_fileList.indexOf(m_currentFile) - 1 < 0))
    {
        m_viewer->stopLoadAnimation();
        return;
    }

    loadPicture(m_dir.path() + "/" + m_fileList.at(m_fileList.indexOf(m_currentFile) - 1));
}

void PicLoader::loadNextPicture()
{
    // загружаем сдедующее по списку директории изображение, если сейчас не граничное
    if (!m_fileList.contains(m_currentFile) || (m_fileList.indexOf(m_currentFile) + 1 >= m_fileList.size()))
    {
        m_viewer->stopLoadAnimation();
        return;
    }

    loadPicture(m_dir.path() + "/" + m_fileList.at(m_fileList.indexOf(m_currentFile) + 1));
}
