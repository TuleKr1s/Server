#include "server.h"

#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QTextEdit>
#include <QtWidgets>

Server::Server(int port, QWidget* wgt)
    : QWidget(wgt), m_nextBlockSize(0)
{
    m_tcpServer = new QTcpServer(this);
    if (!m_tcpServer->listen(QHostAddress::Any, port)) {
        QMessageBox::critical(0, "Server Error", "Unable to start the server:"+m_tcpServer->errorString());
        m_tcpServer->close();
        return;
    }
    connect(m_tcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));
    m_txt = new QTextEdit;
    m_txt->setReadOnly(true);

    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(new QLabel("<H1>Server</H1>"));
    box->addWidget(m_txt);
    setLayout(box);
}

void Server::slotNewConnection() {
    QTcpSocket* clientSocket = m_tcpServer->nextPendingConnection();
    connect(clientSocket,SIGNAL(disconnected()),clientSocket,SLOT(deleteLater()));
    connect(clientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()));

    sendToClient(clientSocket, "Server Response: Connected!");
}

void Server::slotReadClient() {
    QTcpSocket* clientSocket = (QTcpSocket*)sender();
    QDataStream in(clientSocket);
    in.setVersion(QDataStream::Qt_5_10);
    for (;;) {
        if (!m_nextBlockSize) {
            if (clientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nextBlockSize;
        }
        if (clientSocket->bytesAvailable() < m_nextBlockSize)
            break;

        QTime time;
        QString str;
        in >> time >> str;

        QString strMessage = time.toString() + " " + "Client has sent - " + str;
        m_txt->append(strMessage);

        m_nextBlockSize = 0;

        sendToClient(clientSocket, "Server Response: Received \"" + str + "\"");
    }
}
void Server::sendToClient(QTcpSocket* socket, const QString& str) {
    QByteArray arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_10);
    out << quint16(0) << QTime::currentTime() << str;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    socket->write(arrBlock);
}
