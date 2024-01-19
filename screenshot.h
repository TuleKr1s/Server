#include <QTimer>
#include <QWidget>
#include <QScreen>
#include <QBoxLayout>
#include <QLabel>
#include <QGuiApplication>
#include <QCursor>
#include <QPainter>
#include <QIcon>
#include <QPixmap>
#include <QElapsedTimer>

class Screenshot : public QWidget {
    Q_OBJECT

private:
    QLabel* screenshotLabel;
    QTimer* timer;
    QElapsedTimer elapsedTimer;

public:
    Screenshot(QWidget *parent = nullptr);

    void startCapturing();

public slots:
    void captureScreenshot();
    void handleTimer();

signals:
    void ScreenTaken(QPixmap);

};
