#include "screenshot.h"

Screenshot::Screenshot(QWidget *parent)
    : QWidget(parent)
{
    screenshotLabel = new QLabel();

    timer = new QTimer();
    timer->setTimerType(Qt::PreciseTimer);
    connect(timer, SIGNAL(timeout()), SLOT(captureScreenshot()));
    connect(timer, SIGNAL(timeout()), SLOT(handleTimer()));

    startCapturing();
}

void Screenshot::startCapturing() {
    if (timer->isActive()) {
        timer->stop();
    } else {
        timer->start(0);
    }
}

void Screenshot::handleTimer() {
    qint64 elapsed = elapsedTimer.elapsed();
    elapsedTimer.restart();

    double frequency = 1000.0 / elapsed; // Вычисляем частоту

    qDebug() << "Timer frequency:" << frequency << "fps";
}

void Screenshot::captureScreenshot() {
    // Получаем скриншот текущего экрана
    QScreen* screen = QGuiApplication::primaryScreen();
    QPixmap screenshot = screen->grabWindow(0); // Сделать учет нескольких мониторов

    QPixmap cursorIcon("../AudioServer1/Icons/ArrowCursor.png");

    // Рисуем курсор
    QPainter painter(&screenshot);
    painter.drawPixmap(QCursor::pos().x(), QCursor::pos().y(), \
                       cursorIcon.scaled(25,25,Qt::KeepAspectRatio));

    emit ScreenTaken(screenshot);
}
