#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "GameScene.hpp"
#include "GameWidget.hpp"

int main(int argc, char *argv[])
{
    QApplication application{argc, argv};
    QMainWindow window;
    GameScene scene;
    GameWidget widget{&scene, &window};

    window.setMinimumSize(widget.minimumSize());
    window.showMaximized();

    return application.exec();
}
