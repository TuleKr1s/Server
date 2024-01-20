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
    QScreen* mainScreen = QGuiApplication::primaryScreen();

    QPoint cursorPos = QCursor::pos();
    QScreen* currentScreen = mainScreen;
    QList<QScreen*> screens = QGuiApplication::screens();
    for (QScreen* screen : screens) {
        if (screen->geometry().contains(cursorPos)) {
            currentScreen = screen;
            break;
        }
    }

    QPoint offset = currentScreen->geometry().topLeft() - mainScreen->geometry().topLeft();

    QPixmap screenshot = currentScreen->grabWindow();

    QPixmap cursorIcon("../AudioServer1/Icons/ArrowCursor.png");
    // Рисуем курсор
    QPainter painter(&screenshot);
    painter.drawPixmap(cursorPos - offset, \
                       cursorIcon.scaled(25,25,Qt::KeepAspectRatio));

    emit ScreenTaken(screenshot);
}
