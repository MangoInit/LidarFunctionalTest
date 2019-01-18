/****************************************************************************
** Meta object code from reading C++ file 'controlform.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LidarFunctionalTest/controlform.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controlform.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControlForm_t {
    QByteArrayData data[20];
    char stringdata0[362];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControlForm_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControlForm_t qt_meta_stringdata_ControlForm = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ControlForm"
QT_MOC_LITERAL(1, 12, 23), // "sg_driver_OpenChoseUART"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 17), // "sg_driver_MoterEn"
QT_MOC_LITERAL(4, 55, 2), // "en"
QT_MOC_LITERAL(5, 58, 24), // "sg_driver_Lidar_Set_Mode"
QT_MOC_LITERAL(6, 83, 10), // "LIDAR_MODE"
QT_MOC_LITERAL(7, 94, 10), // "lidar_mode"
QT_MOC_LITERAL(8, 105, 14), // "Lidar_Set_Mode"
QT_MOC_LITERAL(9, 120, 20), // "sg_driver_getDevInfo"
QT_MOC_LITERAL(10, 141, 11), // "std::string"
QT_MOC_LITERAL(11, 153, 10), // "lidar_port"
QT_MOC_LITERAL(12, 164, 25), // "sg_driver_getDeviceHealth"
QT_MOC_LITERAL(13, 190, 18), // "sg_driver_stopScan"
QT_MOC_LITERAL(14, 209, 24), // "on_OpenChoseUART_clicked"
QT_MOC_LITERAL(15, 234, 29), // "on_pushButton_MoterEn_clicked"
QT_MOC_LITERAL(16, 264, 7), // "checked"
QT_MOC_LITERAL(17, 272, 29), // "on_pushButton_ModeOFF_clicked"
QT_MOC_LITERAL(18, 302, 30), // "on_pushButton_StopScan_clicked"
QT_MOC_LITERAL(19, 333, 28) // "on_pushButton_ModeON_clicked"

    },
    "ControlForm\0sg_driver_OpenChoseUART\0"
    "\0sg_driver_MoterEn\0en\0sg_driver_Lidar_Set_Mode\0"
    "LIDAR_MODE\0lidar_mode\0Lidar_Set_Mode\0"
    "sg_driver_getDevInfo\0std::string\0"
    "lidar_port\0sg_driver_getDeviceHealth\0"
    "sg_driver_stopScan\0on_OpenChoseUART_clicked\0"
    "on_pushButton_MoterEn_clicked\0checked\0"
    "on_pushButton_ModeOFF_clicked\0"
    "on_pushButton_StopScan_clicked\0"
    "on_pushButton_ModeON_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControlForm[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x06 /* Public */,
       3,    1,   75,    2, 0x06 /* Public */,
       5,    1,   78,    2, 0x06 /* Public */,
       8,    1,   81,    2, 0x06 /* Public */,
       9,    1,   84,    2, 0x06 /* Public */,
      12,    0,   87,    2, 0x06 /* Public */,
      13,    0,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,   89,    2, 0x08 /* Private */,
      15,    1,   90,    2, 0x08 /* Private */,
      17,    0,   93,    2, 0x08 /* Private */,
      18,    0,   94,    2, 0x08 /* Private */,
      19,    0,   95,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
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
        case 0: _t->sg_driver_OpenChoseUART(); break;
        case 1: _t->sg_driver_MoterEn((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->sg_driver_Lidar_Set_Mode((*reinterpret_cast< LIDAR_MODE(*)>(_a[1]))); break;
        case 3: _t->Lidar_Set_Mode((*reinterpret_cast< LIDAR_MODE(*)>(_a[1]))); break;
        case 4: _t->sg_driver_getDevInfo((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 5: _t->sg_driver_getDeviceHealth(); break;
        case 6: _t->sg_driver_stopScan(); break;
        case 7: _t->on_OpenChoseUART_clicked(); break;
        case 8: _t->on_pushButton_MoterEn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: _t->on_pushButton_ModeOFF_clicked(); break;
        case 10: _t->on_pushButton_StopScan_clicked(); break;
        case 11: _t->on_pushButton_ModeON_clicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ControlForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlForm::sg_driver_OpenChoseUART)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ControlForm::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlForm::sg_driver_MoterEn)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ControlForm::*)(LIDAR_MODE );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlForm::sg_driver_Lidar_Set_Mode)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ControlForm::*)(LIDAR_MODE );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlForm::Lidar_Set_Mode)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ControlForm::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlForm::sg_driver_getDevInfo)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ControlForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlForm::sg_driver_getDeviceHealth)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ControlForm::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControlForm::sg_driver_stopScan)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ControlForm::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ControlForm.data,
      qt_meta_data_ControlForm,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ControlForm::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControlForm::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControlForm.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ControlForm::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ControlForm::sg_driver_OpenChoseUART()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ControlForm::sg_driver_MoterEn(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ControlForm::sg_driver_Lidar_Set_Mode(LIDAR_MODE _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ControlForm::Lidar_Set_Mode(LIDAR_MODE _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ControlForm::sg_driver_getDevInfo(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ControlForm::sg_driver_getDeviceHealth()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ControlForm::sg_driver_stopScan()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
