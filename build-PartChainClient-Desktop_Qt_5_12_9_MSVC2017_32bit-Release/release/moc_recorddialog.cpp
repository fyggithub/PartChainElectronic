/****************************************************************************
** Meta object code from reading C++ file 'recorddialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.9)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PartChainClient/RecordForensics/recorddialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'recorddialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.9. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_RecordDialog_t {
    QByteArrayData data[24];
    char stringdata0[330];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_RecordDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_RecordDialog_t qt_meta_stringdata_RecordDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "RecordDialog"
QT_MOC_LITERAL(1, 13, 14), // "StopTimeSignal"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "SigSendMessageToJS"
QT_MOC_LITERAL(4, 48, 7), // "strMain"
QT_MOC_LITERAL(5, 56, 4), // "type"
QT_MOC_LITERAL(6, 61, 3), // "str"
QT_MOC_LITERAL(7, 65, 15), // "SendMsgCloseWnd"
QT_MOC_LITERAL(8, 81, 10), // "RecordType"
QT_MOC_LITERAL(9, 92, 18), // "StartButtonClicked"
QT_MOC_LITERAL(10, 111, 17), // "StopButtonClicked"
QT_MOC_LITERAL(11, 129, 10), // "RecordTime"
QT_MOC_LITERAL(12, 140, 10), // "FileUpload"
QT_MOC_LITERAL(13, 151, 13), // "replyFinished"
QT_MOC_LITERAL(14, 165, 14), // "QNetworkReply*"
QT_MOC_LITERAL(15, 180, 9), // "loadError"
QT_MOC_LITERAL(16, 190, 27), // "QNetworkReply::NetworkError"
QT_MOC_LITERAL(17, 218, 18), // "DialogProgressTime"
QT_MOC_LITERAL(18, 237, 23), // "MplayerCompressFinished"
QT_MOC_LITERAL(19, 261, 8), // "exitCode"
QT_MOC_LITERAL(20, 270, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(21, 291, 10), // "exitStatus"
QT_MOC_LITERAL(22, 302, 12), // "onMinClicked"
QT_MOC_LITERAL(23, 315, 14) // "onCloseClicked"

    },
    "RecordDialog\0StopTimeSignal\0\0"
    "SigSendMessageToJS\0strMain\0type\0str\0"
    "SendMsgCloseWnd\0RecordType\0"
    "StartButtonClicked\0StopButtonClicked\0"
    "RecordTime\0FileUpload\0replyFinished\0"
    "QNetworkReply*\0loadError\0"
    "QNetworkReply::NetworkError\0"
    "DialogProgressTime\0MplayerCompressFinished\0"
    "exitCode\0QProcess::ExitStatus\0exitStatus\0"
    "onMinClicked\0onCloseClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_RecordDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    3,   80,    2, 0x06 /* Public */,
       7,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   90,    2, 0x08 /* Private */,
      10,    0,   91,    2, 0x08 /* Private */,
      11,    0,   92,    2, 0x08 /* Private */,
      12,    0,   93,    2, 0x08 /* Private */,
      13,    1,   94,    2, 0x08 /* Private */,
      15,    1,   97,    2, 0x08 /* Private */,
      17,    0,  100,    2, 0x08 /* Private */,
      18,    2,  101,    2, 0x08 /* Private */,
      22,    0,  106,    2, 0x08 /* Private */,
      23,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 20,   19,   21,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void RecordDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<RecordDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->StopTimeSignal(); break;
        case 1: _t->SigSendMessageToJS((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->SendMsgCloseWnd((*reinterpret_cast< RecordType(*)>(_a[1]))); break;
        case 3: _t->StartButtonClicked(); break;
        case 4: _t->StopButtonClicked(); break;
        case 5: _t->RecordTime(); break;
        case 6: _t->FileUpload(); break;
        case 7: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 8: _t->loadError((*reinterpret_cast< QNetworkReply::NetworkError(*)>(_a[1]))); break;
        case 9: _t->DialogProgressTime(); break;
        case 10: _t->MplayerCompressFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 11: _t->onMinClicked(); break;
        case 12: _t->onCloseClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 8:
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
            using _t = void (RecordDialog::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordDialog::StopTimeSignal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (RecordDialog::*)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordDialog::SigSendMessageToJS)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (RecordDialog::*)(RecordType );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&RecordDialog::SendMsgCloseWnd)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject RecordDialog::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_RecordDialog.data,
    qt_meta_data_RecordDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *RecordDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *RecordDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_RecordDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int RecordDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
void RecordDialog::StopTimeSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void RecordDialog::SigSendMessageToJS(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void RecordDialog::SendMsgCloseWnd(RecordType _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
