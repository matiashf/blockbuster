#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCore/QCommandLineParser>

#include "GameScene.hpp"
#include "GameView.hpp"
#include "Map.hpp"

int main(int argc, char *argv[])
{
    QApplication application{argc, argv};
    application.setApplicationName("blockbuster");

    // Parse the command line
    QCommandLineParser parser;
    parser.setApplicationDescription("A 2D physics game all about breaking blocks");
    parser.addHelpOption();
    parser.addPositionalArgument("mapfile", "Load the given map file");
    parser.process(application);
    const QStringList args = parser.positionalArguments();

    QString map_url;
    if (args.size() > 1 ) {
      parser.showHelp(1); // Exits the process with exit code 1 (indicating error)
    } else if (args.size() == 1) {
      map_url = args.first();
    } else {
      do map_url = Map::random();
      while (map_url == ":/maps/blank.txt");
    }

    GameScene scene;
    GameView view{&scene};
    Map{map_url}.loadInto(&scene);
    scene.start();

    view.showNormal();

    return application.exec();
}
