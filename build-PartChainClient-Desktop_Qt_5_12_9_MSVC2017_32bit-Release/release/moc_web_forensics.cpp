/****************************************************************************
** Meta object code from reading C++ file 'web_forensics.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PartChainClient/WebForensics/web_forensics.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'web_forensics.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_web_forensics_t {
    QByteArrayData data[25];
    char stringdata0[299];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_web_forensics_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_web_forensics_t qt_meta_stringdata_web_forensics = {
    {
QT_MOC_LITERAL(0, 0, 13), // "web_forensics"
QT_MOC_LITERAL(1, 14, 18), // "SigSendMessageToJS"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 7), // "strMain"
QT_MOC_LITERAL(4, 42, 4), // "type"
QT_MOC_LITERAL(5, 47, 3), // "str"
QT_MOC_LITERAL(6, 51, 12), // "SendMsgClose"
QT_MOC_LITERAL(7, 64, 15), // "SendMsgCloseWnd"
QT_MOC_LITERAL(8, 80, 10), // "RecordType"
QT_MOC_LITERAL(9, 91, 11), // "LoadWebOver"
QT_MOC_LITERAL(10, 103, 3), // "tmp"
QT_MOC_LITERAL(11, 107, 7), // "JumpUrl"
QT_MOC_LITERAL(12, 115, 9), // "ReloadUrl"
QT_MOC_LITERAL(13, 125, 7), // "BackUrl"
QT_MOC_LITERAL(14, 133, 14), // "FullScreenSave"
QT_MOC_LITERAL(15, 148, 12), // "OnUrlChanged"
QT_MOC_LITERAL(16, 161, 3), // "url"
QT_MOC_LITERAL(17, 165, 13), // "replyFinished"
QT_MOC_LITERAL(18, 179, 14), // "QNetworkReply*"
QT_MOC_LITERAL(19, 194, 9), // "loadError"
QT_MOC_LITERAL(20, 204, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(21, 232, 18), // "DialogProgressTime"
QT_MOC_LITERAL(22, 251, 18), // "DisplayCurrentTime"
QT_MOC_LITERAL(23, 270, 12), // "RecvMsgClose"
QT_MOC_LITERAL(24, 283, 15) // "FullScreenShoot"

    },
    "web_forensics\0SigSendMessageToJS\0\0"
    "strMain\0type\0str\0SendMsgClose\0"
    "SendMsgCloseWnd\0RecordType\0LoadWebOver\0"
    "tmp\0JumpUrl\0ReloadUrl\0BackUrl\0"
    "FullScreenSave\0OnUrlChanged\0url\0"
    "replyFinished\0QNetworkReply*\0loadError\0"
    "QNetworkReply::NetworkError\0"
    "DialogProgressTime\0DisplayCurrentTime\0"
    "RecvMsgClose\0FullScreenShoot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_web_forensics[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   89,    2, 0x06 /* Public */,
       6,    0,   96,    2, 0x06 /* Public */,
       7,    1,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    1,  100,    2, 0x0a /* Public */,
      11,    0,  103,    2, 0x0a /* Public */,
      12,    0,  104,    2, 0x0a /* Public */,
      13,    0,  105,    2, 0x0a /* Public */,
      14,    0,  106,    2, 0x0a /* Public */,
      15,    1,  107,    2, 0x0a /* Public */,
      17,    1,  110,    2, 0x0a /* Public */,
      19,    1,  113,    2, 0x0a /* Public */,
      21,    0,  116,    2, 0x0a /* Public */,
      22,    0,  117,    2, 0x0a /* Public */,
      23,    0,  118,    2, 0x0a /* Public */,
      24,    0,  119,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QUrl,   16,
    QMetaType::Void, 0x80000000 | 18,    2,
    QMetaType::Void, 0x80000000 | 20,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void web_forensics::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<web_forensics *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SigSendMessageToJS((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->SendMsgClose(); break;
        case 2: _t->SendMsgCloseWnd((*reinterpret_cast< RecordType(*)>(_a[1]))); break;
        case 3: _t->LoadWebOver((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->JumpUrl(); break;
        case 5: _t->ReloadUrl(); break;
        case 6: _t->BackUrl(); break;
        case 7: _t->FullScreenSave(); break;
        case 8: _t->OnUrlChanged((*reinterpret_cast< QUrl(*)>(_a[1]))); break;
        case 9: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 10: _t->loadError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 11: _t->DialogProgressTime(); break;
        case 12: _t->DisplayCurrentTime(); break;
        case 13: _t->RecvMsgClose(); break;
        case 14: _t->FullScreenShoot(); break;
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
            using _t = void (web_forensics::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&web_forensics::SigSendMessageToJS)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (web_forensics::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&web_forensics::SendMsgClose)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (web_forensics::*)(RecordType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&web_forensics::SendMsgCloseWnd)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject web_forensics::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_web_forensics.data,
    qt_meta_data_web_forensics,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *web_forensics::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *web_forensics::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_web_forensics.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int web_forensics::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void web_forensics::SigSendMessageToJS(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void web_forensics::SendMsgClose()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void web_forensics::SendMsgCloseWnd(RecordType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
