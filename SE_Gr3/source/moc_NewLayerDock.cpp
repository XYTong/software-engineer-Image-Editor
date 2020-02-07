/****************************************************************************
** Meta object code from reading C++ file 'NewLayerDock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "NewLayerDock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'NewLayerDock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NewLayerDock_t {
    QByteArrayData data[20];
    char stringdata0[235];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NewLayerDock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NewLayerDock_t qt_meta_stringdata_NewLayerDock = {
    {
QT_MOC_LITERAL(0, 0, 12), // "NewLayerDock"
QT_MOC_LITERAL(1, 13, 14), // "updateHasLayer"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 1), // "b"
QT_MOC_LITERAL(4, 31, 6), // "update"
QT_MOC_LITERAL(5, 38, 15), // "setNewColorVect"
QT_MOC_LITERAL(6, 54, 13), // "QVector<QRgb>"
QT_MOC_LITERAL(7, 68, 9), // "colorVect"
QT_MOC_LITERAL(8, 78, 13), // "existingColor"
QT_MOC_LITERAL(9, 92, 8), // "newColor"
QT_MOC_LITERAL(10, 101, 15), // "actualColorVect"
QT_MOC_LITERAL(11, 117, 17), // "standartColorVect"
QT_MOC_LITERAL(12, 135, 14), // "smallColorVect"
QT_MOC_LITERAL(13, 150, 15), // "customColorVect"
QT_MOC_LITERAL(14, 166, 11), // "addNewLayer"
QT_MOC_LITERAL(15, 178, 11), // "setNewColor"
QT_MOC_LITERAL(16, 190, 12), // "setNewLayerX"
QT_MOC_LITERAL(17, 203, 1), // "w"
QT_MOC_LITERAL(18, 205, 12), // "setNewLayerY"
QT_MOC_LITERAL(19, 218, 16) // "setNewLayerColor"

    },
    "NewLayerDock\0updateHasLayer\0\0b\0update\0"
    "setNewColorVect\0QVector<QRgb>\0colorVect\0"
    "existingColor\0newColor\0actualColorVect\0"
    "standartColorVect\0smallColorVect\0"
    "customColorVect\0addNewLayer\0setNewColor\0"
    "setNewLayerX\0w\0setNewLayerY\0"
    "setNewLayerColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NewLayerDock[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       4,    0,   87,    2, 0x06 /* Public */,
       5,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   91,    2, 0x08 /* Private */,
       9,    0,   92,    2, 0x08 /* Private */,
      10,    0,   93,    2, 0x08 /* Private */,
      11,    0,   94,    2, 0x08 /* Private */,
      12,    0,   95,    2, 0x08 /* Private */,
      13,    0,   96,    2, 0x08 /* Private */,
      14,    0,   97,    2, 0x08 /* Private */,
      15,    0,   98,    2, 0x08 /* Private */,
      16,    1,   99,    2, 0x08 /* Private */,
      18,    1,  102,    2, 0x08 /* Private */,
      19,    0,  105,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,

       0        // eod
};

void NewLayerDock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NewLayerDock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateHasLayer((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->update(); break;
        case 2: _t->setNewColorVect((*reinterpret_cast< QVector<QRgb>(*)>(_a[1]))); break;
        case 3: _t->existingColor(); break;
        case 4: _t->newColor(); break;
        case 5: _t->actualColorVect(); break;
        case 6: _t->standartColorVect(); break;
        case 7: _t->smallColorVect(); break;
        case 8: _t->customColorVect(); break;
        case 9: _t->addNewLayer(); break;
        case 10: _t->setNewColor(); break;
        case 11: _t->setNewLayerX((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setNewLayerY((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->setNewLayerColor(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NewLayerDock::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NewLayerDock::updateHasLayer)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NewLayerDock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NewLayerDock::update)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NewLayerDock::*)(QVector<QRgb> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NewLayerDock::setNewColorVect)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NewLayerDock::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_NewLayerDock.data,
    qt_meta_data_NewLayerDock,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NewLayerDock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NewLayerDock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NewLayerDock.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NewLayerDock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void NewLayerDock::updateHasLayer(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NewLayerDock::update()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NewLayerDock::setNewColorVect(QVector<QRgb> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
