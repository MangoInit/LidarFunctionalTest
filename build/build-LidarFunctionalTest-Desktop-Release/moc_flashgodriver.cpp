/****************************************************************************
** Meta object code from reading C++ file 'flashgodriver.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../flashgodriver.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'flashgodriver.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_FlashgoDriver_t {
    QByteArrayData data[17];
    char stringdata0[223];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FlashgoDriver_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FlashgoDriver_t qt_meta_stringdata_FlashgoDriver = {
    {
QT_MOC_LITERAL(0, 0, 13), // "FlashgoDriver"
QT_MOC_LITERAL(1, 14, 13), // "sg_result_dis"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 18), // "LidarResultDisplay"
QT_MOC_LITERAL(4, 48, 11), // "sg_uart_dis"
QT_MOC_LITERAL(5, 60, 11), // "sg_loop_end"
QT_MOC_LITERAL(6, 72, 14), // "Lidar_Set_Mode"
QT_MOC_LITERAL(7, 87, 10), // "LIDAR_MODE"
QT_MOC_LITERAL(8, 98, 10), // "lidar_mode"
QT_MOC_LITERAL(9, 109, 15), // "driver_openUart"
QT_MOC_LITERAL(10, 125, 17), // "driver_getDevInfo"
QT_MOC_LITERAL(11, 143, 11), // "std::string"
QT_MOC_LITERAL(12, 155, 10), // "lidar_port"
QT_MOC_LITERAL(13, 166, 22), // "driver_getDeviceHealth"
QT_MOC_LITERAL(14, 189, 15), // "driver_stopScan"
QT_MOC_LITERAL(15, 205, 14), // "driver_MoterEn"
QT_MOC_LITERAL(16, 220, 2) // "en"

    },
    "FlashgoDriver\0sg_result_dis\0\0"
    "LidarResultDisplay\0sg_uart_dis\0"
    "sg_loop_end\0Lidar_Set_Mode\0LIDAR_MODE\0"
    "lidar_mode\0driver_openUart\0driver_getDevInfo\0"
    "std::string\0lidar_port\0driver_getDeviceHealth\0"
    "driver_stopScan\0driver_MoterEn\0en"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FlashgoDriver[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    1,   62,    2, 0x06 /* Public */,
       5,    0,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   66,    2, 0x0a /* Public */,
       9,    0,   69,    2, 0x0a /* Public */,
      10,    1,   70,    2, 0x0a /* Public */,
      13,    0,   73,    2, 0x0a /* Public */,
      14,    0,   74,    2, 0x0a /* Public */,
      15,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Bool, 0x80000000 | 7,    8,
    QMetaType::Bool,
    QMetaType::Bool, 0x80000000 | 11,   12,
    QMetaType::Bool,
    QMetaType::Bool,
    QMetaType::Bool, QMetaType::Bool,   16,

       0        // eod
};

void FlashgoDriver::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        FlashgoDriver *_t = static_cast<FlashgoDriver *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sg_result_dis((*reinterpret_cast< LidarResultDisplay(*)>(_a[1]))); break;
        case 1: _t->sg_uart_dis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->sg_loop_end(); break;
        case 3: { bool _r = _t->Lidar_Set_Mode((*reinterpret_cast< LIDAR_MODE(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->driver_openUart();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: { bool _r = _t->driver_getDevInfo((*reinterpret_cast< std::string(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 6: { bool _r = _t->driver_getDeviceHealth();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 7: { bool _r = _t->driver_stopScan();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 8: { bool _r = _t->driver_MoterEn((*reinterpret_cast< bool(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (FlashgoDriver::*_t)(LidarResultDisplay );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlashgoDriver::sg_result_dis)) {
                *result = 0;
            }
        }
        {
            typedef void (FlashgoDriver::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlashgoDriver::sg_uart_dis)) {
                *result = 1;
            }
        }
        {
            typedef void (FlashgoDriver::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&FlashgoDriver::sg_loop_end)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject FlashgoDriver::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_FlashgoDriver.data,
      qt_meta_data_FlashgoDriver,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *FlashgoDriver::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FlashgoDriver::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_FlashgoDriver.stringdata0))
        return static_cast<void*>(const_cast< FlashgoDriver*>(this));
    return QObject::qt_metacast(_clname);
}

int FlashgoDriver::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void FlashgoDriver::sg_result_dis(LidarResultDisplay _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FlashgoDriver::sg_uart_dis(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FlashgoDriver::sg_loop_end()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
