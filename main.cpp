#include <btBulletDynamicsCommon.h>

#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>

#include <QtWidgets/QGraphicsView>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QMainWindow window;

    QGraphicsView widget{&window};
    widget.setMinimumSize(800, 600); // width, height
    widget.setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding); // Expand to fill parent container

    window.setMinimumSize(widget.minimumSize());
    window.showMaximized();

    return application.exec();
}
