QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17 debug

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    model/cave/generator/basic/basic.cc \
    model/cave/io/cave_reader.cc \
    model/cave/io/cave_writer.cc \
    model/cave/cave.cc \
    model/maze/generator/eller/eller.cc \
    model/maze/io/maze_reader.cc \
    model/maze/io/maze_writer.cc \
    model/maze/solver/a_star/a_star.cc \
    model/maze/maze.cc \
    model/model.cc \
    view/drawer/cave_drawer.cc \
    view/drawer/maze_drawer.cc \
    view/main_window.cc \
    main.cc

HEADERS += \
    controller/controller.h \
    model/cave/generator/basic/basic.h \
    model/cave/generator/generators.h \
    model/cave/io/cave_reader.h \
    model/cave/io/cave_writer.h \
    model/cave/cave.h \
    model/maze/generator/eller/eller.h \
    model/maze/generator/base_generator.h \
    model/maze/generator/generators.h \
    model/maze/io/maze_reader.h \
    model/maze/io/maze_writer.h \
    model/maze/solver/a_star/a_star.h \
    model/maze/solver/base_solver.h \
    model/maze/solver/solvers.h \
    model/maze/maze.h \
    model/app_config.h \
    model/model.h \
    model/utils.h \
    view/drawer/cave_drawer.h \
    view/drawer/maze_drawer.h \
    view/main_window.h

FORMS += \
    view/main_window.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
