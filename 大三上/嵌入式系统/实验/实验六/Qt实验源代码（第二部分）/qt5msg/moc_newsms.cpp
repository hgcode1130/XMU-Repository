/****************************************************************************
** Meta object code from reading C++ file 'newsms.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "newsms.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'newsms.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_newsms_t {
    QByteArrayData data[13];
    char stringdata0[201];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_newsms_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_newsms_t qt_meta_stringdata_newsms = {
    {
QT_MOC_LITERAL(0, 0, 6), // "newsms"
QT_MOC_LITERAL(1, 7, 10), // "sendnewsms"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "contact"
QT_MOC_LITERAL(4, 27, 7), // "message"
QT_MOC_LITERAL(5, 35, 23), // "newsmsbackButtonClicked"
QT_MOC_LITERAL(6, 59, 17), // "sendButtonClicked"
QT_MOC_LITERAL(7, 77, 28), // "keyboardshow_sendphonenumber"
QT_MOC_LITERAL(8, 106, 4), // "data"
QT_MOC_LITERAL(9, 111, 29), // "confirmString_sendphonenumber"
QT_MOC_LITERAL(10, 141, 8), // "gemfield"
QT_MOC_LITERAL(11, 150, 24), // "keyboardshow_sendmessage"
QT_MOC_LITERAL(12, 175, 25) // "confirmString_sendmessage"

    },
    "newsms\0sendnewsms\0\0contact\0message\0"
    "newsmsbackButtonClicked\0sendButtonClicked\0"
    "keyboardshow_sendphonenumber\0data\0"
    "confirmString_sendphonenumber\0gemfield\0"
    "keyboardshow_sendmessage\0"
    "confirmString_sendmessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_newsms[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   54,    2, 0x08 /* Private */,
       6,    0,   55,    2, 0x08 /* Private */,
       7,    1,   56,    2, 0x08 /* Private */,
       9,    1,   59,    2, 0x08 /* Private */,
      11,    1,   62,    2, 0x08 /* Private */,
      12,    1,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void newsms::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        newsms *_t = static_cast<newsms *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendnewsms((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->newsmsbackButtonClicked(); break;
        case 2: _t->sendButtonClicked(); break;
        case 3: _t->keyboardshow_sendphonenumber((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->confirmString_sendphonenumber((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->keyboardshow_sendmessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->confirmString_sendmessage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (newsms::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&newsms::sendnewsms)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject newsms::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_newsms.data,
      qt_meta_data_newsms,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *newsms::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *newsms::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_newsms.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int newsms::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void newsms::sendnewsms(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_NewSmsCustomWidget_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NewSmsCustomWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NewSmsCustomWidget_t qt_meta_stringdata_NewSmsCustomWidget = {
    {
QT_MOC_LITERAL(0, 0, 18) // "NewSmsCustomWidget"

    },
    "NewSmsCustomWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewSmsCustomWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void NewSmsCustomWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject NewSmsCustomWidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_NewSmsCustomWidget.data,
      qt_meta_data_NewSmsCustomWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NewSmsCustomWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewSmsCustomWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NewSmsCustomWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int NewSmsCustomWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
