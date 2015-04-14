CONFIG += c++11
QT += core gui widgets opengl

HEADERS += $$files(*.hpp)
SOURCES += $$files(*.cpp)
SOURCES -= $$files(moc_*.cpp)

# Bullet physics library
INCLUDEPATH += /usr/include/Box2D/
LIBS += -lBox2D
