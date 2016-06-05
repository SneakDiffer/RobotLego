TEMPLATE = app
CONFIG += console c++11
CONFIG += lbluetooth
CONFIG -= app_bundle
CONFIG -= qt


SOURCES += main.cpp \
    connection.cpp \
    board.cpp \
    case.cpp

HEADERS += \
    connection.h \
    board.h \
    case.h \
    path.h \
    robot.h \
    pathelem.h \
    global.h
