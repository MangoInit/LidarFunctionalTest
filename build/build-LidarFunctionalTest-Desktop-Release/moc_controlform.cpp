/****************************************************************************
** Meta object code from reading C++ file 'controlform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../controlform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ControlForm_t {
    QByteArrayData data[9];
    char stringdata0[159];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlForm_t qt_meta_stringdata_ControlForm = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ControlForm"
QT_MOC_LITERAL(1, 12, 16), // "sg_control_start"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 4), // "nums"
QT_MOC_LITERAL(4, 35, 15), // "sg_control_stop"
QT_MOC_LITERAL(5, 51, 16), // "sg_control_reset"
QT_MOC_LITERAL(6, 68, 31), // "on_pushButton_loopStart_clicked"
QT_MOC_LITERAL(7, 100, 27), // "on_pushButton_reset_clicked"
QT_MOC_LITERAL(8, 128, 30) // "on_pushButton_loopStop_clicked"

    },
    "ControlForm\0sg_control_start\0\0nums\0"
    "sg_control_stop\0sg_control_reset\0"
    "on_pushButton_loopStart_clicked\0"
    "on_pushButton_reset_clicked\0"
    "on_pushButton_loopStop_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ControlForm::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ControlForm *_t = static_cast<ControlForm *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sg_control_start((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->sg_control_stop((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->sg_control_reset((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_pushButton_loopStart_clicked(); break;
        case 4: _t->on_pushButton_reset_clicked(); break;
        case 5: _t->on_pushButton_loopStop_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ControlForm::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlForm::sg_control_start)) {
                *result = 0;
            }
        }
        {
            typedef void (ControlForm::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlForm::sg_control_stop)) {
                *result = 1;
            }
        }
        {
            typedef void (ControlForm::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ControlForm::sg_control_reset)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject ControlForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlForm.data,
      qt_meta_data_ControlForm,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ControlForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlForm::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ControlForm.stringdata0))
        return static_cast<void*>(const_cast< ControlForm*>(this));
    return QWidget::qt_metacast(_clname);
}

int ControlForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void ControlForm::sg_control_start(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControlForm::sg_control_stop(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ControlForm::sg_control_reset(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
