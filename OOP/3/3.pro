QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    builder.cpp \
    commands.cpp \
    composite.cpp \
    controller.cpp \
    creator.cpp \
    details.cpp \
    draw_manager.cpp \
    drawer.cpp \
    drawer_factory.cpp \
    edge.cpp \
    errors.cpp \
    facade.cpp \
    main.cpp \
    mainwindow.cpp \
    model.cpp \
    model_loader.cpp \
    object.cpp \
    point.cpp \
    scene.cpp \
    scene_manager.cpp \
    source_loader.cpp \
    visitor.cpp

HEADERS += \
    builder.hpp \
    commands.hpp \
    composite.hpp \
    controller.hpp \
    creator.hpp \
    details.hpp \
    draw_manager.hpp \
    drawer.hpp \
    drawer_factory.hpp \
    edge.hpp \
    errors.hpp \
    facade.hpp \
    mainwindow.hpp \
    model.hpp \
    model_loader.hpp \
    object.hpp \
    point.hpp \
    scene.hpp \
    scene_manager.hpp \
    source_loader.hpp \
    visitor.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
