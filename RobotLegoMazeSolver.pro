
DESTDIR = bin/
OBJECTS_DIR = obj/

QMAKE_CXXFLAGS += -lm -lbluetooth -std=c++11 -pthread -lpthread

QT += widgets

TEMPLATE = app

CONFIG += console c++11t

LIBS += -lbluetooth

SOURCES = \
    src/ia/connection.cpp \
    src/main.cpp \
    src/ui/qapp.cpp \
    src/ui/walldrawer.cpp \
    src/ia/representation.cpp \
    src/ia/global.cpp \
    src/ia/backup.cpp \
    src/ia/astar.cpp \
    src/ia/squareexploration.cpp \
    src/ia/wall_dir.cpp \
    src/ia/wall_dir_scan.cpp \
    src/ia/murs_impasse.cpp

HEADERS = \
    src/ia/connection.h \
    src/ia/robot.h \
    src/ia/representation.h \
    src/ia/global.h \
    src/ui/qapp.h \
    src/ui/walldrawer.h \
    src/ia/backup.h \
    src/ia/astar.h \
    src/ia/squareexploration.h \
    src/ia/wall_dir.h \
    src/ia/wall_dir_scan.h \
    src/ia/murs_impasse.h


FORMS += \
    src/ui/qapp.ui \
    src/ui/walldrawer.ui
