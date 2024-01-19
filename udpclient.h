#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QWidget>
#include <QTextEdit>
#include <QUdpSocket>
#include <QDateTime>
#include <QLabel>
#include <QBoxLayout>
#include <QBuffer>
#include <QFile>
#include <QtConcurrent/QtConcurrent>



class UDPClient : public QWidget
{
    Q_OBJECT

    QUdpSocket* m_socket;
    QString m_host;
    int m_port;

    QLabel* m_label;
public:
    explicit UDPClient(QString host, int port, QWidget *parent = nullptr);

private slots:
    void slotProcessDatagrams();
};

#endif // UDPCLIENT_H
