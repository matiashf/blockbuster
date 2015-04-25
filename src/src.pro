CONFIG += c++11
CONFIG += debug
QT += core gui widgets opengl

HEADERS += $$files(../src/*.hpp)
SOURCES += $$files(../src/*.cpp)
RESOURCES += $$files(../resources/*.qrc)

TARGET=blockbuster

DESTDIR = ../bin
OBJECTS_DIR = ../build
MOC_DIR = ../build
RCC_DIR = ../build
UI_DIR = ../build

# Box2D physics library
INCLUDEPATH += /usr/include/Box2D/
LIBS += -lBox2D
