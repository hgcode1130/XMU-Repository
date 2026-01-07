/****************************************************************************
** Meta object code from reading C++ file 'lis3dhthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "lis3dhthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lis3dhthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Lis3dhThread_t {
    QByteArrayData data[8];
    char stringdata0[76];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Lis3dhThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Lis3dhThread_t qt_meta_stringdata_Lis3dhThread = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Lis3dhThread"
QT_MOC_LITERAL(1, 13, 7), // "turn180"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 5), // "turn0"
QT_MOC_LITERAL(4, 28, 11), // "rotation180"
QT_MOC_LITERAL(5, 40, 9), // "rotation0"
QT_MOC_LITERAL(6, 50, 10), // "stopThread"
QT_MOC_LITERAL(7, 61, 14) // "continueThread"

    },
    "Lis3dhThread\0turn180\0\0turn0\0rotation180\0"
    "rotation0\0stopThread\0continueThread"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Lis3dhThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   46,    2, 0x0a /* Public */,
       5,    0,   47,    2, 0x0a /* Public */,
       6,    0,   48,    2, 0x0a /* Public */,
       7,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Lis3dhThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Lis3dhThread *_t = static_cast<Lis3dhThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->turn180(); break;
        case 1: _t->turn0(); break;
        case 2: _t->rotation180(); break;
        case 3: _t->rotation0(); break;
        case 4: _t->stopThread(); break;
        case 5: _t->continueThread(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Lis3dhThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Lis3dhThread::turn180)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Lis3dhThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Lis3dhThread::turn0)) {
                *result = 1;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Lis3dhThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Lis3dhThread.data,
      qt_meta_data_Lis3dhThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Lis3dhThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Lis3dhThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Lis3dhThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Lis3dhThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Lis3dhThread::turn180()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void Lis3dhThread::turn0()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
