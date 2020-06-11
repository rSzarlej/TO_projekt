QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TARGET = tst_test

TEMPLATE = app

RESOURCES += \
    rsc.qrc

SOURCES += *.cpp

INCLUDEPATH += $$PWD/../AppLib

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../AppLib/release/ -lAppLib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../AppLib/debug/ -lAppLib


