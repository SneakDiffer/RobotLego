DESTDIR = bin/
OBJECTS_DIR = obj/

QMAKE_CXXFLAGS += -lm -lbluetooth

QT += widgets

TEMPLATE = app

LIBS += -lbluetooth

SOURCES = \
    src/ia/connection.cpp \
    src/main.cpp \
    src/ui/qapp.cpp \
    src/ui/walldrawer.cpp \
    src/ia/representation.cpp \
    src/ia/global.cpp \
    src/ia/backup.cpp \
    src/ia/astar.cpp

HEADERS = \
    src/ia/connection.h \
    src/ia/robot.h \
    src/ia/representation.h \
    src/ia/global.h \
    src/ui/qapp.h \
    src/ui/walldrawer.h \
    src/ia/backup.h \
    src/ia/astar.h

FORMS += \
    src/ui/qapp.ui \
    src/ui/walldrawer.ui
