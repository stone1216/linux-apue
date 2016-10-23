TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS  += -pthread
SOURCES += main.c \
    apue.c \
    8-12.c \
    10-22.c \
    error.c \
    10-23.c \
    10-2.c \
    10-15.c \
    10-20.c \
    11-2.c \
    11-3.c \
    11-5.c \
    11-13.c \
    13-1.c \
    test.c \
    15-6.c \
    15-11.c \
    15-14.c \
    1515.c \
    15-17.c \
    15-18.c \
    16-9.c \
    16-16.c \
    16-11.c \
    16-12.c \
    16-17.c


HEADERS += \
    apue.h

DISTFILES +=


QMAKE_CXXFLAGS += -Wno-unused-parameter

QMAKE_CXXFLAGS += -Wno-unused-variable

