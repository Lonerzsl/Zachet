#include "slothplayer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SlothPlayer player;
    player.show();

    return a.exec();
}
