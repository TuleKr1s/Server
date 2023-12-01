#include "screenshot.h"

Screenshot::Screenshot(QWidget *parent)
    : QWidget(parent)
{
    screenshotLabel = new QLabel();

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), SLOT(captureScreenshot()));

    QVBoxLayout* box = new QVBoxLayout(this);
    box->addWidget(screenshotLabel);

    startCapturing();
}

void Screenshot::startCapturing() {
    if (timer->isActive()) {
        timer->stop();
    } else {
        timer->start(16); // Захватывать картинку каждые 16 миллисекунд (60 кадров в секунду)
    }
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
    // Отображаем скриншот в QLabel
    screenshotLabel->setPixmap(screenshot);
}
