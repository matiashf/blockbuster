# dave3605-project
C++ programming project spring 2015

## Building and running

```shell
sudo apt-get install qt5-qmake qtdeclarative5-dev libbox2d-dev qt5-default g++ gdb
qmake # Generate Makefile
make
./blockbuster
```

## Building and running on Ubuntu 14.04 with vagrant

```shell
vagrant up
vagrant ssh
cd /vagrant
qmake && make clean all
./blockbuster
```

## Inspiration

* http://stackoverflow.com/a/3632065/2719221 - using make to generate c++ from moc
* http://stackoverflow.com/a/28573370/2719221 - overview of Qt for game development
* http://stackoverflow.com/a/2224305/2719221 - using QGlWidget and Qtimer
* http://stackoverflow.com/a/4711082/2719221 - fullscreen qt windows
* http://stackoverflow.com/a/9118745/2719221 - basic bullet physics example
* https://code.google.com/p/bullet/issues/detail?id=208 - Applying 2D-constraints to bullet
