/****************************************************************************
** Meta object code from reading C++ file 'phonethread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "phonethread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'phonethread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PhoneThread_t {
    QByteArrayData data[13];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PhoneThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PhoneThread_t qt_meta_stringdata_PhoneThread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "PhoneThread"
QT_MOC_LITERAL(1, 12, 7), // "sendnum"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 3), // "num"
QT_MOC_LITERAL(4, 25, 10), // "sendanswer"
QT_MOC_LITERAL(5, 36, 8), // "behundup"
QT_MOC_LITERAL(6, 45, 13), // "sendmodellost"
QT_MOC_LITERAL(7, 59, 7), // "senlost"
QT_MOC_LITERAL(8, 67, 4), // "send"
QT_MOC_LITERAL(9, 72, 10), // "sendAnswer"
QT_MOC_LITERAL(10, 83, 9), // "noCarrier"
QT_MOC_LITERAL(11, 93, 13), // "SendModelLost"
QT_MOC_LITERAL(12, 107, 11) // "SendSimLost"

    },
    "PhoneThread\0sendnum\0\0num\0sendanswer\0"
    "behundup\0sendmodellost\0senlost\0send\0"
    "sendAnswer\0noCarrier\0SendModelLost\0"
    "SendSimLost"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PhoneThread[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   79, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    0,   67,    2, 0x06 /* Public */,
       5,    0,   68,    2, 0x06 /* Public */,
       6,    0,   69,    2, 0x06 /* Public */,
       7,    0,   70,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       8,    1,   71,    2, 0x02 /* Public */,
       9,    0,   74,    2, 0x02 /* Public */,
      10,    0,   75,    2, 0x02 /* Public */,
      11,    0,   76,    2, 0x02 /* Public */,
      12,    0,   77,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // constructors: parameters
    0x80000000 | 2,

 // constructors: name, argc, parameters, tag, flags
       0,    0,   78,    2, 0x0e /* Public */,

       0        // eod
};

void PhoneThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { PhoneThread *_r = new PhoneThread();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        PhoneThread *_t = static_cast<PhoneThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendnum((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->sendanswer(); break;
        case 2: _t->behundup(); break;
        case 3: _t->sendmodellost(); break;
        case 4: _t->senlost(); break;
        case 5: _t->send((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->sendAnswer(); break;
        case 7: _t->noCarrier(); break;
        case 8: _t->SendModelLost(); break;
        case 9: _t->SendSimLost(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PhoneThread::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PhoneThread::sendnum)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PhoneThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PhoneThread::sendanswer)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PhoneThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PhoneThread::behundup)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PhoneThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PhoneThread::sendmodellost)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PhoneThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PhoneThread::senlost)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PhoneThread::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_PhoneThread.data,
      qt_meta_data_PhoneThread,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PhoneThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PhoneThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PhoneThread.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int PhoneThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void PhoneThread::sendnum(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PhoneThread::sendanswer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void PhoneThread::behundup()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PhoneThread::sendmodellost()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void PhoneThread::senlost()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
