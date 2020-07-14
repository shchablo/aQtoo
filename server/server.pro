QT += core
QT -= gui

DESTDIR = ../../bin
TARGET = server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

INCLUDEPATH += ${OMNIORB_PATH}/include 
INCLUDEPATH += ${OMNIORB_PATH}/stub 
VPATH += ${OMNIORB_PATH}/idl 
#VPATH += ${OMNIORB_PATH}/stub 


QMAKE_CXXFLAGS += -std=gnu++17
INCLUDEPATH += /usr/include
LIBS += -L${OMNIORB_PATH}/lib  -lomniORB4 -lomniDynamic4 -lomnithread -lpthread -lncurses

OBJECTS += ${OMNIORB_PATH}/stub/echoSK.o
HEADERS += omniorbthread.h
SOURCES += main.cpp omniorbthread.cpp
