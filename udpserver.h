#ifndef UDPSERVER_H
#define UDPSERVER_H

#include <QWidget>
#include <QTextEdit>
#include <QUdpSocket>
#include <QTimer>
#include <QDateTime>
#include <QBoxLayout>
#include <QLabel>
#include <QBuffer>
#include <QFile>
#include <QtConcurrent/QtConcurrent>

#include "screenshot.h"

class UDPServer : public QWidget
{
    Q_OBJECT

    QUdpSocket* m_socket;
    QString m_host;
    int m_port;

    QLabel* m_label;
    Screenshot* scr;

public:
    explicit UDPServer(QString host, int port, QWidget *parent = nullptr);

private slots:
    void slotSendDatagram(QPixmap);

};

#endif // UDPSERVER_H
