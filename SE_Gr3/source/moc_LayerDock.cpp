/****************************************************************************
** Meta object code from reading C++ file 'LayerDock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "LayerDock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LayerDock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LayerDock_t {
    QByteArrayData data[10];
    char stringdata0[110];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LayerDock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LayerDock_t qt_meta_stringdata_LayerDock = {
    {
QT_MOC_LITERAL(0, 0, 9), // "LayerDock"
QT_MOC_LITERAL(1, 10, 15), // "updateLayerDock"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 8), // "newLayer"
QT_MOC_LITERAL(4, 36, 6), // "update"
QT_MOC_LITERAL(5, 43, 9), // "getParams"
QT_MOC_LITERAL(6, 53, 17), // "toolParameters_t*"
QT_MOC_LITERAL(7, 71, 5), // "param"
QT_MOC_LITERAL(8, 77, 18), // "changeCurrentLayer"
QT_MOC_LITERAL(9, 96, 13) // "updateVisible"

    },
    "LayerDock\0updateLayerDock\0\0newLayer\0"
    "update\0getParams\0toolParameters_t*\0"
    "param\0changeCurrentLayer\0updateVisible"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LayerDock[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   50,    2, 0x08 /* Private */,
       9,    0,   51,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void LayerDock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LayerDock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateLayerDock(); break;
        case 1: _t->newLayer(); break;
        case 2: _t->update(); break;
        case 3: _t->getParams((*reinterpret_cast< toolParameters_t*(*)>(_a[1]))); break;
        case 4: _t->changeCurrentLayer(); break;
        case 5: _t->updateVisible(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LayerDock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayerDock::updateLayerDock)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LayerDock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayerDock::newLayer)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LayerDock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayerDock::update)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LayerDock::*)(toolParameters_t * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LayerDock::getParams)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LayerDock::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_LayerDock.data,
    qt_meta_data_LayerDock,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LayerDock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LayerDock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LayerDock.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int LayerDock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void LayerDock::updateLayerDock()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LayerDock::newLayer()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LayerDock::update()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LayerDock::getParams(toolParameters_t * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
