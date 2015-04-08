#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "GameScene.hpp"
#include "GameWidget.hpp"

int main(int argc, char *argv[])
{
    QApplication application{argc, argv};
    GameScene scene;
    GameWidget widget{&scene};

    widget.showMaximized();

    return application.exec();
}
