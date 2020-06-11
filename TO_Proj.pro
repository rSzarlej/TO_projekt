TEMPLATE = subdirs

SUBDIRS += \
    App \
    Tests \
    AppLib

App.depends = AppLib
Tests.depends = AppLib

