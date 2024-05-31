QT -= gui
QT += network

CONFIG += c++11
CONFIG -= app_bundle

TARGET = udp-discover

DESTDIR = "$$_PRO_FILE_PWD_/bin/"

TEMPLATE = lib
#CONFIG += staticlib

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
#        main.cpp \
    discserver.cpp \
    discclient.cpp \
    discverify.cpp \
    udpdiscover.cpp

HEADERS += \
    discserver.h \
    discclient.h \
    discverify.h \
    udpdiscover.h
