/****************************************************************************
** Meta object code from reading C++ file 'ec20.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ec20.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ec20.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_EC20_t {
    QByteArrayData data[10];
    char stringdata0[71];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EC20_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EC20_t qt_meta_stringdata_EC20 = {
    {
QT_MOC_LITERAL(0, 0, 4), // "EC20"
QT_MOC_LITERAL(1, 5, 9), // "modelLost"
QT_MOC_LITERAL(2, 15, 0), // ""
QT_MOC_LITERAL(3, 16, 4), // "Call"
QT_MOC_LITERAL(4, 21, 5), // "char*"
QT_MOC_LITERAL(5, 27, 9), // "phone_num"
QT_MOC_LITERAL(6, 37, 10), // "answerCall"
QT_MOC_LITERAL(7, 48, 7), // "getcall"
QT_MOC_LITERAL(8, 56, 6), // "handUp"
QT_MOC_LITERAL(9, 63, 7) // "getImei"

    },
    "EC20\0modelLost\0\0Call\0char*\0phone_num\0"
    "answerCall\0getcall\0handUp\0getImei"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EC20[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       3,    1,   45,    2, 0x02 /* Public */,
       6,    0,   48,    2, 0x02 /* Public */,
       7,    0,   49,    2, 0x02 /* Public */,
       8,    0,   50,    2, 0x02 /* Public */,
       9,    0,   51,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,

 // methods: parameters
    QMetaType::Int, 0x80000000 | 4,    5,
    QMetaType::Int,
    0x80000000 | 4,
    QMetaType::Int,
    QMetaType::QString,

       0        // eod
};

void EC20::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EC20 *_t = static_cast<EC20 *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->modelLost(); break;
        case 1: { int _r = _t->Call((*reinterpret_cast< char*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 2: { int _r = _t->answerCall();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 3: { char* _r = _t->getcall();
            if (_a[0]) *reinterpret_cast< char**>(_a[0]) = std::move(_r); }  break;
        case 4: { int _r = _t->handUp();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 5: { QString _r = _t->getImei();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EC20::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EC20::modelLost)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EC20::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_EC20.data,
      qt_meta_data_EC20,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *EC20::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EC20::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EC20.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int EC20::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void EC20::modelLost()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_MyBackend_t {
    QByteArrayData data[10];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MyBackend_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MyBackend_t qt_meta_stringdata_MyBackend = {
    {
QT_MOC_LITERAL(0, 0, 9), // "MyBackend"
QT_MOC_LITERAL(1, 10, 11), // "AnwerCalled"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "NoCarrier"
QT_MOC_LITERAL(4, 33, 15), // "callnumReceived"
QT_MOC_LITERAL(5, 49, 3), // "num"
QT_MOC_LITERAL(6, 53, 9), // "ModelLost"
QT_MOC_LITERAL(7, 63, 7), // "SimLost"
QT_MOC_LITERAL(8, 71, 7), // "getCall"
QT_MOC_LITERAL(9, 79, 13) // "sendModelLost"

    },
    "MyBackend\0AnwerCalled\0\0NoCarrier\0"
    "callnumReceived\0num\0ModelLost\0SimLost\0"
    "getCall\0sendModelLost"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MyBackend[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       1,   59, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    1,   51,    2, 0x06 /* Public */,
       6,    0,   54,    2, 0x06 /* Public */,
       7,    0,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   56,    2, 0x0a /* Public */,
       9,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // constructors: parameters
    0x80000000 | 2,

 // constructors: name, argc, parameters, tag, flags
       0,    0,   58,    2, 0x0e /* Public */,

       0        // eod
};

void MyBackend::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { MyBackend *_r = new MyBackend();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        MyBackend *_t = static_cast<MyBackend *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->AnwerCalled(); break;
        case 1: _t->NoCarrier(); break;
        case 2: _t->callnumReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->ModelLost(); break;
        case 4: _t->SimLost(); break;
        case 5: _t->getCall(); break;
        case 6: _t->sendModelLost(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MyBackend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyBackend::AnwerCalled)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MyBackend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyBackend::NoCarrier)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MyBackend::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyBackend::callnumReceived)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MyBackend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyBackend::ModelLost)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MyBackend::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MyBackend::SimLost)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MyBackend::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_MyBackend.data,
      qt_meta_data_MyBackend,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MyBackend::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MyBackend::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MyBackend.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MyBackend::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void MyBackend::AnwerCalled()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MyBackend::NoCarrier()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void MyBackend::callnumReceived(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MyBackend::ModelLost()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MyBackend::SimLost()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
