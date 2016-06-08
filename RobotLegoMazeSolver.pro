DESTDIR = bin/
OBJECTS_DIR = obj/

QMAKE_CXXFLAGS += -lm -lbluetooth

LIBS += -lbluetooth

SOURCES = \
          src/ia/connection.cpp \
          src/ia/main.cpp \
    src/ia/representation.cpp \
    src/ia/global.cpp

HEADERS = \
          src/ia/connection.h \
          src/ia/robot.h \
          src/ia/representation.h \
          src/ia/global.h
