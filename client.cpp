//#include "client.h"

//Client::Client(const QString& strHost, int port, QWidget *parent)
//    : QWidget(parent), m_nextBlockSize(0)
//{
//    m_socket = new QTcpSocket(this);

//    m_socket->connectToHost(strHost, port);
//    connect(m_socket, SIGNAL(connected()),\
//            SLOT(slotConnected()));
//    connect(m_socket, SIGNAL(readyRead()),\
//            SLOT(slotReadyRead()));
//    connect(m_socket, SIGNAL(errorOccurred(QAbstractSocket::SocketError)),\
//            this, SLOT(slotError(QAbstractSocket::SocketError)));

//    m_txtInfo = new QTextEdit;
//    m_txtInput = new QLineEdit;

//    m_txtInfo->setReadOnly(true);

//    QPushButton* btn = new QPushButton("Send");
//    connect(btn, SIGNAL(clicked()), SLOT(slotSendToServer()));
//    connect(m_txtInput, SIGNAL(returnPressed()), SLOT(slotSendToServer()));

//    QVBoxLayout* box = new QVBoxLayout;
//    box->addWidget(new QLabel("<H1>Client</H1>"));
//    box->addWidget(m_txtInfo);
//    box->addWidget(m_txtInput);
//    box->addWidget(btn);
//    setLayout(box);
//}

//void Client::slotReadyRead() {
//    QDataStream in(m_socket);
//    in.setVersion(QDataStream::Qt_5_3);
//    for (;;) {
//        if (!m_nextBlockSize) {
//            if (m_socket->bytesAvailable() < sizeof(quint16)) {
//                break;
//            }
//            in >> m_nextBlockSize;
//        }
//        if (m_socket->bytesAvailable() < m_nextBlockSize) {
//            break;
//        }
//        QTime time;
//        QString str;
//        in >> time >> str;

//        m_txtInfo->append(time.toString(QString("hh.mm.ss")) + " " + str);
//        m_nextBlockSize = 0;
//    }
//}

//void Client::slotError(QAbstractSocket::SocketError err) {
//    QString strError = "Error: " + \
//                       (err == QAbstractSocket::HostNotFoundError ?\
//                            "The host not found." :\
//                                err == QAbstractSocket::RemoteHostClosedError ?\
//                            "The remote host is closed." :\
//                                err == QAbstractSocket::ConnectionRefusedError ?\
//                            "The connection was refused." :\
//                            QString(m_socket->errorString()));
//    m_txtInfo->append(strError);
//}


//void Client::slotSendToServer() {
//    QByteArray arrBlock;
//    QDataStream out(&arrBlock, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_5_3);
//    out << quint16(0) << QTime::currentTime() << m_txtInput->text();

//    out.device()->seek(0);
//    out << quint16(arrBlock.size() - sizeof(quint16));

//    m_socket->write(arrBlock);
//    m_txtInput->setText("");
//}

//void Client::slotConnected() {
//    m_txtInfo->append("Received the connected() signal");
//}
