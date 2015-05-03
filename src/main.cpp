#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "GameScene.hpp"
#include "GameView.hpp"
#include "Map.hpp"

int main(int argc, char *argv[])
{
    QApplication application{argc, argv};
    GameScene scene;
    GameView view{&scene};
    Map{":/maps/stacks.txt"}.loadInto(scene);
    scene.start();

    view.showNormal();

    return application.exec();
}
