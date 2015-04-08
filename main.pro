CONFIG += c++11
MAKE_CXXFLAGS += -Wall -g
QT += widgets opengl

HEADERS += $$files(*.hpp)
SOURCES += $$files(*.cpp)
SOURCES -= $$files(moc_*.cpp)

# Bullet physics library
INCLUDEPATH += /usr/include/bullet/
LIBS += -lBulletDynamics -lBulletCollision -lLinearMath
QMAKE_CXXFLAGS += -Wno-unused-variable
