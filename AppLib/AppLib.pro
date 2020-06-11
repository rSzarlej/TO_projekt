#-------------------------------------------------
#
# Project created by QtCreator 2020-06-11T11:32:25
#
#-------------------------------------------------

QT       += gui widgets core 3drender 3dinput 3dlogic 3dextras qml quick 3dquick 3danimation

TARGET = AppLib
TEMPLATE = lib

DEFINES += APPLIB_LIBRARY MYSHAREDLIB_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        applib.cpp \
    mainsource.cpp \
    NewFile/newfile.cpp \
    NewFile/newfile2d.cpp \
    NewFile/newfile3d.cpp \
    NewFile/newfiletxt.cpp \
    fileManagers/filemanager2d.cpp \
    fileManagers/filemanager3d.cpp \
    fileManagers/filemanagertxt.cpp

HEADERS += \
        applib.h \
        applib_global.h \ 
    mainsource.h \
    NewFile/newfile.h \
    NewFile/newfile2d.h \
    NewFile/newfile3d.h \
    NewFile/newfiletxt.h \
    fileManagers/filemanager2d.h \
    fileManagers/filemanager3d.h \
    fileManagers/filemanagertxt.h \
    mysharedlib_global.h

FORMS += \
    fileManagers/filemanager2d.ui \
    fileManagers/filemanager3d.ui \
    fileManagers/filemanagertxt.ui

unix {
    target.path = /usr/lib
    INSTALLS += target
}
