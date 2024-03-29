QT       += core gui network concurrent
#QT =
#CONFIG =

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

#TARGET = opencvtest
#TEMPLATE = app


# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    screenshot.cpp \
    udpclient.cpp \
    udpserver.cpp

HEADERS += \
    screenshot.h \
    udpclient.h \
    udpserver.h

#INCLUDEPATH += F:\Programming\OpenCV\opencv\build\include

#LIBS += F:\Programming\OpenCV\opencv\opencv-build\bin\libopencv_core480.dll
#LIBS += F:\Programming\OpenCV\opencv\opencv-build\bin\libopencv_highgui480.dll
#LIBS += F:\Programming\OpenCV\opencv\opencv-build\bin\libopencv_videoio480.dll
#LIBS += F:\Programming\OpenCV\opencv\opencv-build\bin\libopencv_imgcodecs480.dll
#LIBS += F:\Programming\OpenCV\opencv\opencv-build\bin\libopencv_features2d480.dll
#LIBS += F:\Programming\OpenCV\opencv\opencv-build\bin\libopencv_calib3d480.dll

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
