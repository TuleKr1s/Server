#include <QApplication>

#include "udpclient.h"
#include "udpserver.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    UDPClient client("localhost", 2323);
    UDPServer server("localhost", 2323);

    server.show();
    client.show();

    return a.exec();
}
