#include <QApplication>

#include "screenshot.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Screenshot screenshot;
    screenshot.show();

    return a.exec();
}
