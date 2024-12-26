/****************************************************************************
** Meta object code from reading C++ file 'scribblearea.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../scribblearea.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'scribblearea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSScribbleAreaENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSScribbleAreaENDCLASS = QtMocHelpers::stringData(
    "ScribbleArea",
    "onTaskBoxContextMenuEvent",
    "",
    "clearImage",
    "print"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSScribbleAreaENDCLASS_t {
    uint offsetsAndSizes[10];
    char stringdata0[13];
    char stringdata1[26];
    char stringdata2[1];
    char stringdata3[11];
    char stringdata4[6];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSScribbleAreaENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSScribbleAreaENDCLASS_t qt_meta_stringdata_CLASSScribbleAreaENDCLASS = {
    {
        QT_MOC_LITERAL(0, 12),  // "ScribbleArea"
        QT_MOC_LITERAL(13, 25),  // "onTaskBoxContextMenuEvent"
        QT_MOC_LITERAL(39, 0),  // ""
        QT_MOC_LITERAL(40, 10),  // "clearImage"
        QT_MOC_LITERAL(51, 5)   // "print"
    },
    "ScribbleArea",
    "onTaskBoxContextMenuEvent",
    "",
    "clearImage",
    "print"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSScribbleAreaENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   32,    2, 0x0a,    1 /* Public */,
       3,    0,   33,    2, 0x0a,    2 /* Public */,
       4,    0,   34,    2, 0x0a,    3 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ScribbleArea::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSScribbleAreaENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSScribbleAreaENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSScribbleAreaENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ScribbleArea, std::true_type>,
        // method 'onTaskBoxContextMenuEvent'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'clearImage'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'print'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ScribbleArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ScribbleArea *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onTaskBoxContextMenuEvent(); break;
        case 1: _t->clearImage(); break;
        case 2: _t->print(); break;
        default: ;
        }
    }
    (void)_a;
}

const QMetaObject *ScribbleArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScribbleArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSScribbleAreaENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ScribbleArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
