QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    builder.cpp \
    commands.cpp \
    controller.cpp \
    details.cpp \
    edge.cpp \
    errors.cpp \
    facade.cpp \
    loader.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    object.cpp \
    point.cpp

HEADERS += \
    builder.hpp \
    commands.hpp \
    controller.hpp \
    details.hpp \
    edge.hpp \
    errors.hpp \
    facade.hpp \
    loader.hpp \
    mainwindow.hpp \
    model.hpp \
    object.hpp \
    point.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
