CONFIG += c++11
CONFIG += debug
QT += core gui widgets opengl

HEADERS += $$files(src/*.hpp)
SOURCES += $$files(src/*.cpp)
RESOURCES += $$files(resources/*.qrc)

mkpath(build)
DEST_DIR = build
OBJECTS_DIR = build
MOC_DIR = build
RCC_DIR = build
UI_DIR = build

# Bullet physics library
INCLUDEPATH += /usr/include/Box2D/
LIBS += -lBox2D
