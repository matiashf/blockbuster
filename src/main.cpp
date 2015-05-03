#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "GameScene.hpp"
#include "GameView.hpp"

int main(int argc, char *argv[])
{
    QApplication application{argc, argv};
    GameScene scene;
    GameView view{&scene};
    scene.load(Map{":/maps/stacks.txt"});
    scene.start();

    view.showNormal();

    return application.exec();
}
