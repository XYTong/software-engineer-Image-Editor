/****************************************************************************
** Meta object code from reading C++ file 'DrawDock.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.13.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "DrawDock.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DrawDock.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.13.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DrawDock_t {
    QByteArrayData data[16];
    char stringdata0[141];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DrawDock_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DrawDock_t qt_meta_stringdata_DrawDock = {
    {
QT_MOC_LITERAL(0, 0, 8), // "DrawDock"
QT_MOC_LITERAL(1, 9, 11), // "updateLayer"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 13), // "updateVisible"
QT_MOC_LITERAL(4, 36, 9), // "drawShowI"
QT_MOC_LITERAL(5, 46, 5), // "para1"
QT_MOC_LITERAL(6, 52, 10), // "drawShowII"
QT_MOC_LITERAL(7, 63, 5), // "para2"
QT_MOC_LITERAL(8, 69, 6), // "pencil"
QT_MOC_LITERAL(9, 76, 9), // "startDraw"
QT_MOC_LITERAL(10, 86, 5), // "lines"
QT_MOC_LITERAL(11, 92, 13), // "notFilledRect"
QT_MOC_LITERAL(12, 106, 10), // "filledRect"
QT_MOC_LITERAL(13, 117, 12), // "setDrawColor"
QT_MOC_LITERAL(14, 130, 8), // "setWidth"
QT_MOC_LITERAL(15, 139, 1) // "w"

    },
    "DrawDock\0updateLayer\0\0updateVisible\0"
    "drawShowI\0para1\0drawShowII\0para2\0"
    "pencil\0startDraw\0lines\0notFilledRect\0"
    "filledRect\0setDrawColor\0setWidth\0w"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DrawDock[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    0,   70,    2, 0x06 /* Public */,
       4,    1,   71,    2, 0x06 /* Public */,
       6,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   77,    2, 0x08 /* Private */,
       9,    0,   78,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    0,   80,    2, 0x08 /* Private */,
      12,    0,   81,    2, 0x08 /* Private */,
      13,    0,   82,    2, 0x08 /* Private */,
      14,    1,   83,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   15,

       0        // eod
};

void DrawDock::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DrawDock *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateLayer(); break;
        case 1: _t->updateVisible(); break;
        case 2: _t->drawShowI((*reinterpret_cast< para1(*)>(_a[1]))); break;
        case 3: _t->drawShowII((*reinterpret_cast< para2(*)>(_a[1]))); break;
        case 4: _t->pencil(); break;
        case 5: _t->startDraw(); break;
        case 6: _t->lines(); break;
        case 7: _t->notFilledRect(); break;
        case 8: _t->filledRect(); break;
        case 9: _t->setDrawColor(); break;
        case 10: _t->setWidth((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DrawDock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawDock::updateLayer)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DrawDock::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawDock::updateVisible)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DrawDock::*)(para1 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawDock::drawShowI)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DrawDock::*)(para2 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DrawDock::drawShowII)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DrawDock::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_DrawDock.data,
    qt_meta_data_DrawDock,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DrawDock::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DrawDock::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DrawDock.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DrawDock::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DrawDock::updateLayer()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void DrawDock::updateVisible()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void DrawDock::drawShowI(para1 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DrawDock::drawShowII(para2 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
