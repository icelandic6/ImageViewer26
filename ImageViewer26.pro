QT += core gui declarative quick

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ImageViewer26
TEMPLATE = app


SOURCES += \
    sources/main.cpp \
    sources/mainviewer.cpp \
    sources/picloader.cpp \
    sources/picviewer.cpp

HEADERS  += \
    sources/defines.h \
    sources/mainviewer.h \
    sources/picloader.h \
    sources/picviewer.h

RESOURCES += resources.qrc

OTHER_FILES += main.qml
