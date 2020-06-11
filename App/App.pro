#-------------------------------------------------
#
# Project created by QtCreator 2020-06-09T00:17:06
#
#-------------------------------------------------

QT       += core gui xml 3dcore 3drender 3dinput 3dlogic 3dextras qml quick 3dquick 3danimation

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = App
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dlg/dialogopenfile.cpp \
    tablemodelfiles.cpp \
    dlg/filedetailswidget.cpp

HEADERS += \
        mainwindow.h \
    dlg/dialogopenfile.h \
    tablemodelfiles.h \
    dlg/filedetailswidget.h

FORMS += \
        mainwindow.ui \
    dlg/dialogopenfile.ui \
    dlg/filedetailswidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc

INCLUDEPATH += $$PWD/../AppLib

DEPENDPATH += $$PWD/../AppLib

LIBS += -L"C:/Program Files (x86)/Windows Kits/8.1/Lib/winv6.3/um/x64" -lUser32

CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AppLib/release/ -lAppLib
else:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AppLib/debug/ -lAppLib


