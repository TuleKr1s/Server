// main.cpp
#include <QApplication>
#include <QDebug>

#include "server.h"
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Server server(2323);
    Client client("localhost", 2323);

    client.show();
    server.show();

    return a.exec();
}
