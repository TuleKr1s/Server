#include "udpserver.h"

UDPServer::UDPServer(QString host, int port, QWidget *parent)
    : QWidget(parent), m_host(host), m_port(port)
{

    setWindowTitle("UdpServer");

    m_socket = new QUdpSocket(this);
    m_socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1000000);


    scr = new Screenshot(this);

    connect(scr, SIGNAL(ScreenTaken(QPixmap)), SLOT(slotSendDatagram(QPixmap)));

    m_label = new QLabel;

    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(m_label);
    setLayout(box);
}

const int UDP_DATAGRAM_SIZE = 50000;

void UDPServer::slotSendDatagram(QPixmap frame) {
    // Асинхронное сохранение и отправка
    (void)QtConcurrent::run([this, frame]() {
        QByteArray arrayBuffer;
        QBuffer buffer(&arrayBuffer);
        buffer.open(QIODevice::WriteOnly);
        frame.save(&buffer, "JPEG");

        int offset = 0;
        while (offset < arrayBuffer.size()) {
            QByteArray datagram = arrayBuffer.mid(offset, UDP_DATAGRAM_SIZE);
            m_socket->writeDatagram(datagram, QHostAddress::LocalHost, m_port);
            offset += UDP_DATAGRAM_SIZE;
        }
    });
}


