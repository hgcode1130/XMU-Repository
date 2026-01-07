/****************************************************************************
** Meta object code from reading C++ file 'lis3dhdevice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lis3dhdevice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lis3dhdevice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Lis3dhDevice_t {
    QByteArrayData data[5];
    char stringdata0[43];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Lis3dhDevice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Lis3dhDevice_t qt_meta_stringdata_Lis3dhDevice = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Lis3dhDevice"
QT_MOC_LITERAL(1, 13, 9), // "change180"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 7), // "change0"
QT_MOC_LITERAL(4, 32, 10) // "stopthread"

    },
    "Lis3dhDevice\0change180\0\0change0\0"
    "stopthread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Lis3dhDevice[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    0,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Lis3dhDevice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Lis3dhDevice *_t = static_cast<Lis3dhDevice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->change180(); break;
        case 1: _t->change0(); break;
        case 2: _t->stopthread(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Lis3dhDevice::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Lis3dhDevice::change180)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Lis3dhDevice::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Lis3dhDevice::change0)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (Lis3dhDevice::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Lis3dhDevice::stopthread)) {
                *result = 2;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Lis3dhDevice::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Lis3dhDevice.data,
      qt_meta_data_Lis3dhDevice,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Lis3dhDevice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Lis3dhDevice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Lis3dhDevice.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Lis3dhDevice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void Lis3dhDevice::change180()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Lis3dhDevice::change0()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void Lis3dhDevice::stopthread()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
