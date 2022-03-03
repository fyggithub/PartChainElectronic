/****************************************************************************
** Meta object code from reading C++ file 'screenshot.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PartChainClient/ScreenShotForensics/screenshot.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screenshot.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScreenShot_t {
    QByteArrayData data[22];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScreenShot_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScreenShot_t qt_meta_stringdata_ScreenShot = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ScreenShot"
QT_MOC_LITERAL(1, 11, 18), // "SigSendMessageToJS"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "strMain"
QT_MOC_LITERAL(4, 39, 4), // "type"
QT_MOC_LITERAL(5, 44, 3), // "str"
QT_MOC_LITERAL(6, 48, 15), // "SendMsgCloseWnd"
QT_MOC_LITERAL(7, 64, 10), // "RecordType"
QT_MOC_LITERAL(8, 75, 7), // "JumpUrl"
QT_MOC_LITERAL(9, 83, 9), // "ReloadUrl"
QT_MOC_LITERAL(10, 93, 7), // "BackUrl"
QT_MOC_LITERAL(11, 101, 14), // "GrabFullScreen"
QT_MOC_LITERAL(12, 116, 10), // "FileUpload"
QT_MOC_LITERAL(13, 127, 11), // "OpenPreview"
QT_MOC_LITERAL(14, 139, 12), // "OnUrlChanged"
QT_MOC_LITERAL(15, 152, 3), // "url"
QT_MOC_LITERAL(16, 156, 13), // "replyFinished"
QT_MOC_LITERAL(17, 170, 14), // "QNetworkReply*"
QT_MOC_LITERAL(18, 185, 9), // "loadError"
QT_MOC_LITERAL(19, 195, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(20, 223, 18), // "DialogProgressTime"
QT_MOC_LITERAL(21, 242, 18) // "DisplayCurrentTime"

    },
    "ScreenShot\0SigSendMessageToJS\0\0strMain\0"
    "type\0str\0SendMsgCloseWnd\0RecordType\0"
    "JumpUrl\0ReloadUrl\0BackUrl\0GrabFullScreen\0"
    "FileUpload\0OpenPreview\0OnUrlChanged\0"
    "url\0replyFinished\0QNetworkReply*\0"
    "loadError\0QNetworkReply::NetworkError\0"
    "DialogProgressTime\0DisplayCurrentTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScreenShot[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   79,    2, 0x06 /* Public */,
       6,    1,   86,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   89,    2, 0x0a /* Public */,
       9,    0,   90,    2, 0x0a /* Public */,
      10,    0,   91,    2, 0x0a /* Public */,
      11,    0,   92,    2, 0x0a /* Public */,
      12,    0,   93,    2, 0x0a /* Public */,
      13,    0,   94,    2, 0x0a /* Public */,
      14,    1,   95,    2, 0x0a /* Public */,
      16,    1,   98,    2, 0x0a /* Public */,
      18,    1,  101,    2, 0x0a /* Public */,
      20,    0,  104,    2, 0x0a /* Public */,
      21,    0,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void, 0x80000000 | 7,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QUrl,   15,
    QMetaType::Void, 0x80000000 | 17,    2,
    QMetaType::Void, 0x80000000 | 19,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ScreenShot::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScreenShot *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigSendMessageToJS((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->SendMsgCloseWnd((*reinterpret_cast< RecordType(*)>(_a[1]))); break;
        case 2: _t->JumpUrl(); break;
        case 3: _t->ReloadUrl(); break;
        case 4: _t->BackUrl(); break;
        case 5: _t->GrabFullScreen(); break;
        case 6: _t->FileUpload(); break;
        case 7: _t->OpenPreview(); break;
        case 8: _t->OnUrlChanged((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 9: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 10: _t->loadError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 11: _t->DialogProgressTime(); break;
        case 12: _t->DisplayCurrentTime(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 9:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 10:
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
            using _t = void (ScreenShot::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScreenShot::SigSendMessageToJS)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ScreenShot::*)(RecordType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ScreenShot::SendMsgCloseWnd)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ScreenShot::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_ScreenShot.data,
    qt_meta_data_ScreenShot,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ScreenShot::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScreenShot::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenShot.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ScreenShot::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ScreenShot::SigSendMessageToJS(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScreenShot::SendMsgCloseWnd(RecordType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
