QT       += core gui multimedia multimediawidgets
QT       += script webenginewidgets webchannel
QT       += multimedia network
UI_DIR   = ./UI

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CameraForensics/audio.cpp \
    CameraForensics/camera.cpp \
    Common/common.cpp \
    Common/jscommunicate.cpp \
    Common/logrecord.cpp \
    Common/networkclean.cpp \
    Common/widget.cpp \
    RecordForensics/avilib.cpp \
    RecordForensics/head.cpp \
    RecordForensics/mywin.cpp \
    RecordForensics/recorddialog.cpp \
    RecordForensics/recordvideo.cpp \
    SM4/En_Decrypt.cpp \
    SM4/base64.cpp \
    SM4/sm4.cpp \
    ScreenShotForensics/bubbleltipbutton.cpp \
    ScreenShotForensics/previewwindow.cpp \
    ScreenShotForensics/screenshot.cpp \
    ScreenShotForensics/zoompreview.cpp \
    WebForensics/web_forensics.cpp \
    WebForensics/weburlrequestinterceptor.cpp \
    config.cpp \
    inspector.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    CameraForensics/audio.h \
    CameraForensics/camera.h \
    Common/common.h \
    Common/jscommunicate.h \
    Common/logrecord.h \
    Common/networkclean.h \
    Common/widget.h \
    RecordForensics/avilib.h \
    RecordForensics/head.h \
    RecordForensics/mywin.h \
    RecordForensics/recorddialog.h \
    RecordForensics/recordvideo.h \
    SM4/En_Decrypt.h \
    SM4/base64.h \
    SM4/sm4.h \
    ScreenShotForensics/bubbleltipbutton.h \
    ScreenShotForensics/previewwindow.h \
    ScreenShotForensics/screenshot.h \
    ScreenShotForensics/zoompreview.h \
    WebForensics/web_forensics.h \
    WebForensics/weburlrequestinterceptor.h \
    config.h \
    inspector.h \
    mainwindow.h

FORMS += \
    CameraForensics/camera.ui \
    Common/widget.ui \
    RecordForensics/recorddialog.ui \
    RecordForensics/recordvideo.ui \
    ScreenShotForensics/previewwindow.ui \
    ScreenShotForensics/screenshot.ui \
    ScreenShotForensics/zoompreview.ui \
    WebForensics/web_forensics.ui \
    inspector.ui \
    mainwindow.ui

INCLUDEPATH += D:\softwarePath\OpenCvPath\opencv\build_msvc\install\include \
            D:\softwarePath\OpenCvPath\opencv\build_msvc\install\include\opencv2 \
            D:\sotfwarePath\OpenCvPath\opencv\build\include

# LIBS += D:\sotfwarePath\OpenCvPath\opencv\build_msvc\install\x86\vc15\lib\opencv_img_hash453.lib \
#         D:\sotfwarePath\OpenCvPath\opencv\build_msvc\install\x86\vc15\lib\opencv_world453.lib
INCLUDEPATH += $$PWD/include
LIBS += -L$$PWD/lib -lquazip

LIBS += user32.lib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -LD:/sotfwarePath/OpenCvPath/opencv/build_msvc/install/x86/vc15/lib/ -lopencv_img_hash453
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/sotfwarePath/OpenCvPath/opencv/build_msvc/install/x86/vc15/lib/ -lopencv_img_hash453d
else:unix: LIBS += -LD:/sotfwarePath/OpenCvPath/opencv/build_msvc/install/x86/vc15/lib/ -lopencv_img_hash453

INCLUDEPATH += D:/sotfwarePath/OpenCvPath/opencv/build_msvc/install/x86/vc15
DEPENDPATH += D:/sotfwarePath/OpenCvPath/opencv/build_msvc/install/x86/vc15

win32:CONFIG(release, debug|release): LIBS += -LD:/sotfwarePath/OpenCvPath/opencv/build_msvc/install/x86/vc15/lib/ -lopencv_world453
else:win32:CONFIG(debug, debug|release): LIBS += -LD:/sotfwarePath/OpenCvPath/opencv/build_msvc/install/x86/vc15/lib/ -lopencv_world453d
else:unix: LIBS += -LD:/sotfwarePath/OpenCvPath/opencv/build_msvc/install/x86/vc15/lib/ -lopencv_world453

INCLUDEPATH += D:/sotfwarePath/OpenCvPath/opencv/build_msvc/install/x86/vc15
DEPENDPATH += D:/sotfwarePath/OpenCvPath/opencv/build_msvc/install/x86/vc15

RC_ICONS = $$PWD/Icon/Titleicon.ico

RESOURCES += \
    Icon.qrc

