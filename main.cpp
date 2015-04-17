#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "GameScene.hpp"
#include "GameView.hpp"

int main(int argc, char *argv[])
{
    QApplication application{argc, argv};
    GameScene scene;
    GameView view{&scene};

    view.showNormal();

    return application.exec();
}
