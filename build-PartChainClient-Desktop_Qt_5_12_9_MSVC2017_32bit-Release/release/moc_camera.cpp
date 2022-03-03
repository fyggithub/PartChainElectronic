/****************************************************************************
** Meta object code from reading C++ file 'camera.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PartChainClient/CameraForensics/camera.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camera.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Camera_t {
    QByteArrayData data[28];
    char stringdata0[402];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Camera_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Camera_t qt_meta_stringdata_Camera = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Camera"
QT_MOC_LITERAL(1, 7, 21), // "StopRecordVideoSignal"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "SigSendMessageToJS"
QT_MOC_LITERAL(4, 49, 7), // "strMain"
QT_MOC_LITERAL(5, 57, 4), // "type"
QT_MOC_LITERAL(6, 62, 3), // "str"
QT_MOC_LITERAL(7, 66, 15), // "SendMsgCloseWnd"
QT_MOC_LITERAL(8, 82, 10), // "RecordType"
QT_MOC_LITERAL(9, 93, 17), // "StartRecordVideo1"
QT_MOC_LITERAL(10, 111, 16), // "StopRecordVideo1"
QT_MOC_LITERAL(11, 128, 11), // "RecordTime1"
QT_MOC_LITERAL(12, 140, 16), // "StartRecordVideo"
QT_MOC_LITERAL(13, 157, 15), // "StopRecordVideo"
QT_MOC_LITERAL(14, 173, 17), // "ReloadRecordVideo"
QT_MOC_LITERAL(15, 191, 17), // "UploadRecordVideo"
QT_MOC_LITERAL(16, 209, 10), // "RecordTime"
QT_MOC_LITERAL(17, 220, 11), // "DisplayTime"
QT_MOC_LITERAL(18, 232, 13), // "replyFinished"
QT_MOC_LITERAL(19, 246, 14), // "QNetworkReply*"
QT_MOC_LITERAL(20, 261, 9), // "loadError"
QT_MOC_LITERAL(21, 271, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(22, 299, 18), // "DialogProgressTime"
QT_MOC_LITERAL(23, 318, 18), // "DisplayCurrentTime"
QT_MOC_LITERAL(24, 337, 23), // "MplayerCompressFinished"
QT_MOC_LITERAL(25, 361, 8), // "exitCode"
QT_MOC_LITERAL(26, 370, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(27, 391, 10) // "exitStatus"

    },
    "Camera\0StopRecordVideoSignal\0\0"
    "SigSendMessageToJS\0strMain\0type\0str\0"
    "SendMsgCloseWnd\0RecordType\0StartRecordVideo1\0"
    "StopRecordVideo1\0RecordTime1\0"
    "StartRecordVideo\0StopRecordVideo\0"
    "ReloadRecordVideo\0UploadRecordVideo\0"
    "RecordTime\0DisplayTime\0replyFinished\0"
    "QNetworkReply*\0loadError\0"
    "QNetworkReply::NetworkError\0"
    "DialogProgressTime\0DisplayCurrentTime\0"
    "MplayerCompressFinished\0exitCode\0"
    "QProcess::ExitStatus\0exitStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Camera[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    3,  100,    2, 0x06 /* Public */,
       7,    1,  107,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,  110,    2, 0x08 /* Private */,
      10,    0,  111,    2, 0x08 /* Private */,
      11,    0,  112,    2, 0x08 /* Private */,
      12,    0,  113,    2, 0x08 /* Private */,
      13,    0,  114,    2, 0x08 /* Private */,
      14,    0,  115,    2, 0x08 /* Private */,
      15,    0,  116,    2, 0x08 /* Private */,
      16,    0,  117,    2, 0x08 /* Private */,
      17,    0,  118,    2, 0x08 /* Private */,
      18,    1,  119,    2, 0x08 /* Private */,
      20,    1,  122,    2, 0x08 /* Private */,
      22,    0,  125,    2, 0x08 /* Private */,
      23,    0,  126,    2, 0x08 /* Private */,
      24,    2,  127,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 19,    2,
    QMetaType::Void, 0x80000000 | 21,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 26,   25,   27,

       0        // eod
};

void Camera::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Camera *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->StopRecordVideoSignal(); break;
        case 1: _t->SigSendMessageToJS((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->SendMsgCloseWnd((*reinterpret_cast< RecordType(*)>(_a[1]))); break;
        case 3: _t->StartRecordVideo1(); break;
        case 4: _t->StopRecordVideo1(); break;
        case 5: _t->RecordTime1(); break;
        case 6: _t->StartRecordVideo(); break;
        case 7: _t->StopRecordVideo(); break;
        case 8: _t->ReloadRecordVideo(); break;
        case 9: _t->UploadRecordVideo(); break;
        case 10: _t->RecordTime(); break;
        case 11: _t->DisplayTime(); break;
        case 12: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 13: _t->loadError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 14: _t->DialogProgressTime(); break;
        case 15: _t->DisplayCurrentTime(); break;
        case 16: _t->MplayerCompressFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply::NetworkError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Camera::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Camera::StopRecordVideoSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Camera::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Camera::SigSendMessageToJS)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Camera::*)(RecordType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Camera::SendMsgCloseWnd)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Camera::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_Camera.data,
    qt_meta_data_Camera,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Camera::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Camera::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Camera.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Camera::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void Camera::StopRecordVideoSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Camera::SigSendMessageToJS(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void Camera::SendMsgCloseWnd(RecordType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
