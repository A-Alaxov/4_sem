QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

INCLUDEPATH += gui
INCLUDEPATH += objects
INCLUDEPATH += managers
INCLUDEPATH += loading
INCLUDEPATH += matrix
INCLUDEPATH += solution

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    commands.cpp \
    facade.cpp \
    gui/canvas.cpp \
    gui/drawer.cpp \
    gui/drawer_factory.cpp \
    gui/mainwindow.cpp \
    gui/visitor.cpp \
    loading/builder.cpp \
    loading/camera_file_loader.cpp \
    loading/model_file_loader.cpp \
    loading/scene_file_loader.cpp \
    loading/secretary.cpp \
    main.cpp \
    managers/draw_manager.cpp \
    managers/load_manager.cpp \
    managers/reform_manager.cpp \
    managers/scene_manager.cpp \
    managers/solution_manager.cpp \
    matrix/transform_matrix.cpp \
    objects/camera.cpp \
    objects/composite.cpp \
    objects/details.cpp \
    objects/edge.cpp \
    objects/model.cpp \
    objects/point.cpp \
    objects/scene.cpp \
    solution/camera_load_solution.cpp \
    solution/drawer_solution.cpp \
    solution/model_load_solution.cpp \
    solution/registration.cpp \
    solution/scene_load_solution.cpp \
    solution/solution.cpp

HEADERS += \
    commands.hpp \
    errors.hpp \
    facade.hpp \
    gui/canvas.hpp \
    gui/drawer.hpp \
    gui/drawer_factory.hpp \
    gui/mainwindow.hpp \
    gui/visitor.hpp \
    loading/base_loader.hpp \
    loading/builder.hpp \
    loading/camera_file_loader.hpp \
    loading/model_file_loader.hpp \
    loading/scene_file_loader.hpp \
    loading/secretary.hpp \
    managers/base_manager.hpp \
    managers/draw_manager.hpp \
    managers/load_manager.hpp \
    managers/reform_manager.hpp \
    managers/scene_manager.hpp \
    managers/solution_manager.hpp \
    matrix/matrix.hpp \
    matrix/matrix_base.hpp \
    matrix/transform_matrix.hpp \
    objects/camera.hpp \
    objects/composite.hpp \
    objects/details.hpp \
    objects/edge.hpp \
    objects/model.hpp \
    objects/object.hpp \
    objects/point.hpp \
    objects/scene.hpp \
    solution/camera_load_solution.hpp \
    solution/drawer_solution.hpp \
    solution/loaders.hpp \
    solution/model_load_solution.hpp \
    solution/registration.hpp \
    solution/scene_load_solution.hpp \
    solution/solution.hpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

FORMS += \
    mainwindow.ui

DISTFILES += \
    3.pro.user \
    cam1.txt \
    cube.txt \
    lab_3.mdj \
    pyra.txt \
    Схема.PNG
