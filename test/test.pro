include(../src/src.pro)

INCLUDEPATH += ../src

TARGET = test

# http://askubuntu.com/questions/145887/why-no-library-files-installed-for-google-test
INCLUDEPATH += /usr/src/gtest/
HEADERS += $$files(/usr/src/gtest/src/*.h)
SOURCES += $$files(/usr/src/gtest/src/*.cc)

HEADERS += $$files(*.hpp)
SOURCES += $$files(*.cpp)
SOURCES -= ../src/main.cpp

QT += testlib
