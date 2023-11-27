//#include <QApplication>
//#include <QDebug>

#include <windows.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>


void captureScreen(cv::Mat& screen, POINT& cursorPos) {
    // Захват контекста экрана
    HDC hScreenDC = GetDC(0);
    HDC hMemoryDC = CreateCompatibleDC(hScreenDC);

    // Получение размеров экрана
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Создание битмапа в памяти
    HBITMAP hBitmap = CreateCompatibleBitmap(hScreenDC, screenWidth, screenHeight);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hMemoryDC, hBitmap);

    // Копирование экрана в битмап
    BitBlt(hMemoryDC, 0, 0, screenWidth, screenHeight, hScreenDC, 0, 0, SRCCOPY);

    // Получение позиции курсора
    GetCursorPos(&cursorPos);

    // Отрисовка курсора на битмапе
    CURSORINFO cursorInfo = { sizeof(CURSORINFO) };
    if (GetCursorInfo(&cursorInfo) && cursorInfo.flags == CURSOR_SHOWING) {
        DrawIcon(hMemoryDC, cursorPos.x, cursorPos.y, cursorInfo.hCursor);
    }

    // Конвертация битмапа в изображение OpenCV
    BITMAPINFOHEADER bi;
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = screenWidth;
    bi.biHeight = -screenHeight;  // минус, чтобы избежать инверсии изображения
    bi.biPlanes = 1;
    bi.biBitCount = 24;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;

    screen.create(screenHeight, screenWidth, CV_8UC3);
    GetDIBits(hMemoryDC, hBitmap, 0, screenHeight, screen.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    // Освобождение ресурсов
    SelectObject(hMemoryDC, hOldBitmap);
    DeleteObject(hBitmap);
    DeleteDC(hMemoryDC);
    ReleaseDC(0, hScreenDC);
}



int main() {
    cv::Mat frame;
    POINT cursorPos;

    while (true) {
        captureScreen(frame, cursorPos);



        cv::imshow("Screen Capture", frame);

        if (cv::waitKey(16) >= 0) {
            break;
        }
    }

    return 0;
}


//#include "server.h"
//#include "client.h"

//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);

//    Server server(2323);
//    Client client("localhost", 2323);

//    client.show();
//    server.show();

//    return a.exec();
//}
