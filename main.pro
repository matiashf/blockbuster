HEADERS += $$files(*.hpp)
SOURCES += $$files(*.cpp)

INCLUDEPATH += /usr/include/bullet/
LIBS += -lBulletDynamics -lBulletCollision -lLinearMath

QMAKE_CXXFLAGS += -std=c++11 #-Wall -Wno-unused-variable -g

QT += widgets
