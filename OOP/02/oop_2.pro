# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = oop_2

QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

DEFINES += QT_DEPRECATED_WARNINGS

qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS = \
    abstract_container.h \
    const_set_iterator.h \
    const_set_iterator.hpp \
    set.h \
    set.hpp \
    set_expectations.h \
    set_iterator.h \
    set_iterator.hpp \
    set_node.h \
    set_node.hpp

SOURCES = \
    main.cpp

INCLUDEPATH =

#DEFINES = 

