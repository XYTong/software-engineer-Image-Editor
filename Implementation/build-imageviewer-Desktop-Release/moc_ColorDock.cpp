/****************************************************************************
** Meta object code from reading C++ file 'ColorDock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../GUI/ColorDock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ColorDock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ColorDock_t {
    QByteArrayData data[8];
    char stringdata0[90];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ColorDock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ColorDock_t qt_meta_stringdata_ColorDock = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ColorDock"
QT_MOC_LITERAL(1, 10, 13), // "updateVisible"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 12), // "updateLayers"
QT_MOC_LITERAL(4, 38, 15), // "updateColorVect"
QT_MOC_LITERAL(5, 54, 13), // "QVector<QRgb>"
QT_MOC_LITERAL(6, 68, 9), // "colorVect"
QT_MOC_LITERAL(7, 78, 11) // "changeColor"

    },
    "ColorDock\0updateVisible\0\0updateLayers\0"
    "updateColorVect\0QVector<QRgb>\0colorVect\0"
    "changeColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ColorDock[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,
       3,    0,   35,    2, 0x06 /* Public */,
       4,    1,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   39,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ColorDock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ColorDock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateVisible(); break;
        case 1: _t->updateLayers(); break;
        case 2: _t->updateColorVect((*reinterpret_cast< QVector<QRgb>(*)>(_a[1]))); break;
        case 3: _t->changeColor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ColorDock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColorDock::updateVisible)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ColorDock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColorDock::updateLayers)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ColorDock::*)(QVector<QRgb> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ColorDock::updateColorVect)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ColorDock::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ColorDock.data,
    qt_meta_data_ColorDock,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ColorDock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ColorDock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ColorDock.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ColorDock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ColorDock::updateVisible()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ColorDock::updateLayers()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ColorDock::updateColorVect(QVector<QRgb> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
