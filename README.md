# blockbuster
C++ programming project spring 2015

## Building and running

```shell
sudo apt-get install qt5-qmake qtbase5-dev libbox2d-dev qt5-default g++ gdb libgtest-dev doxygen graphviz
qmake # Generate Makefile
make
bin/blockbuster
```

## Generating documentation

```shell
make doc
# The documentation opens automatically in your browser
```

Note that `make clean` does not remove generated documentation. To
remove it, run `rm -rf doc`.

## Building and testing on Ubuntu 14.04 with vagrant

```shell
make distclean
vagrant up
vagrant ssh
cd /vagrant
qmake
make test
```

## Running tests

```shell
qmake
make test
```

# Playing the game

## Overview

## Controls

# Architecture

The game uses Qt and QGraphicsView.

## Scene, view and items

## Boxes and balls

## Box2D

* Bodies
* CollisionCallback

# maps

## The GameLoader



## Inspiration

* http://stackoverflow.com/a/3632065/2719221 - using make to generate c++ from moc
* http://stackoverflow.com/a/28573370/2719221 - overview of Qt for game development
* http://stackoverflow.com/a/2224305/2719221 - using QGlWidget and Qtimer
* http://stackoverflow.com/a/4711082/2719221 - fullscreen qt windows
* http://stackoverflow.com/a/9118745/2719221 - basic bullet physics example
* https://code.google.com/p/bullet/issues/detail?id=208 - Applying 2D-constraints to bullet
