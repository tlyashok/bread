QT += testlib
QT += network
QT += sql
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_check_task1_test.cpp \
    ../server/database.cpp \
    ../server/dbrequests.cpp \
    ../server/functions.cpp \
    ../server/mytcpserver.cpp \
    ../server/taskmanager.cpp

HEADERS += \
    ../server/database.h \
    ../server/dbrequests.h \
    ../server/functions.h \
    ../server/mytcpserver.h \
    ../server/singleton.h \
    ../server/taskmanager.h
