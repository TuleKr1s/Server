#include "udpclient.h"

UDPClient::UDPClient(QString host, int port, QWidget *parent)
    : QWidget{parent}, m_host(host), m_port(port)
{
    setWindowTitle("UdpClient");
    m_socket = new QUdpSocket(this);
    m_socket->bind(m_port);
    m_socket->setSocketOption(QAbstractSocket::ReceiveBufferSizeSocketOption, 1000000);

    connect(m_socket, SIGNAL(readyRead()), SLOT(slotProcessDatagrams()));

    m_label = new QLabel;

    QVBoxLayout* box = new QVBoxLayout;
    box->addWidget(m_label);
    setLayout(box);
}

void UDPClient::slotProcessDatagrams() {

    QByteArray datagram;
    QPixmap frame;

    while (m_socket->hasPendingDatagrams()) {
        QByteArray receivedData;
        receivedData.resize(m_socket->pendingDatagramSize());
        m_socket->readDatagram(receivedData.data(), receivedData.size());
        datagram.append(receivedData);
    }

    if (frame.loadFromData(datagram, "JPEG")) {
        //frame = frame.scaled(frame.size()*1.1, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        m_label->setPixmap(frame);
    } else {
        qDebug() << "Failed to read frame";
    }
}
