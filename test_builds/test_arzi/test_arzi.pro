QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += F:\Different\testruns\qtestzip\zlib123
win32{

    LIBS += -LF:\Different\testruns\qtestzip\zlib123 -lz
}

win32:RC_ICONS += arzi.ico

SOURCES += \
    main.cpp \
    arzi.cpp \
    zip.cpp

HEADERS += \
    arzi.h\
    qzipreader_p.h\
    qzipwriter_p.h \
    zconf.h \
    zipreader.h \
    zipwriter.h \
    zlib.h


FORMS += \
    arzi.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
