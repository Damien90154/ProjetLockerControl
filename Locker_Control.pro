#-------------------------------------------------
#
# Project created by QtCreator 2015-03-10T09:09:00
#
#-------------------------------------------------

QT       += core gui
QT       += sql
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Locker_Control
TEMPLATE = app


SOURCES += main.cpp\
    boxchoice.cpp \
    deliveryconfirm.cpp \
    customer.cpp \
    login.cpp \
    setting.cpp \
    scanpackage.cpp \
    openemptybox.cpp \
    menudelivery.cpp \
    stowpackages.cpp \
    showpackagebox.cpp \
    consolewindows.cpp \
    showwidgets.cpp \
    drawbox.cpp \
    csqlite_local_db.cpp \
    clms_db.cpp \
    threaddeleteextractcode.cpp \
    custompushbutton.cpp \
    threadsavedelivery.cpp \
    cdoors.cpp \
    thread_statusdoors.cpp \
    customtreewidget.cpp \
    keyboard.cpp \
    country.cpp \
    maintenancemenu.cpp \
    sqlite_local_databasemanager.cpp \
    thread_databasemanager.cpp \
    doorsmanager.cpp \
    thread_localdatabase_autosave.cpp \
    settingsystem.cpp \
    customxml.cpp

HEADERS  += \
    boxchoice.h \
    deliveryconfirm.h \
    customer.h \
    login.h \
    setting.h \
    scanpackage.h \
    openemptybox.h \
    menudelivery.h \
    stowpackages.h \
    showpackagebox.h \
    consolewindows.h \
    showwidgets.h \
    drawbox.h \
    DataStructures.h \
    csqlite_local_db.h \
    clms_db.h \
    threaddeleteextractcode.h \
    custompushbutton.h \
    threadsavedelivery.h \
    cdoors.h \
    thread_statusdoors.h \
    customtreewidget.h \
    keyboard.h \
    country.h \
    maintenancemenu.h \
    sqlite_local_databasemanager.h \
    thread_databasemanager.h \
    doorsmanager.h \
    thread_localdatabase_autosave.h \
    settingsystem.h \
    customxml.h

FORMS    += \
    boxchoice.ui \
    deliveryconfirm.ui \
    customer.ui \
    login.ui \
    scanpackage.ui \
    openemptybox.ui \
    menudelivery.ui \
    setting.ui \
    stowpackages.ui \
    showpackagebox.ui \
    consolewindows.ui \
    keyboard.ui \
    maintenancemenu.ui \
    sqlite_local_databasemanager.ui \
    doorsmanager.ui \
    settingsystem.ui

RESOURCES += \
    Src.qrc

TRANSLATIONS = english.ts french.ts german.ts spain.ts
