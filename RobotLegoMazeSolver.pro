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
<<<<<<< HEAD
    src/ia/representation.cpp \
    src/ia/global.cpp \
    src/ia/backup.cpp
=======
    src/ia/astar.cpp
>>>>>>> 57dee211b04348f5fffd4decb6e7965db15000e9

HEADERS = \
    src/ia/connection.h \
    src/ia/robot.h \
    src/ia/representation.h \
    src/ia/global.h \
    src/ui/qapp.h \
    src/ui/walldrawer.h \
<<<<<<< HEAD
    src/ia/backup.h
=======
    src/ia/astar.h
>>>>>>> 57dee211b04348f5fffd4decb6e7965db15000e9

FORMS += \
    src/ui/qapp.ui \
    src/ui/walldrawer.ui
