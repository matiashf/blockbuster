#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include "GameWidget.hpp"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    QMainWindow window;
    GameWidget widget{&window};

    window.setMinimumSize(widget.minimumSize());
    window.showMaximized();

    return application.exec();
}
