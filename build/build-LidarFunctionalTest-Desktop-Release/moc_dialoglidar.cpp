/****************************************************************************
** Meta object code from reading C++ file 'dialoglidar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../dialoglidar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dialoglidar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DialogLidar_t {
    QByteArrayData data[23];
    char stringdata0[436];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DialogLidar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DialogLidar_t qt_meta_stringdata_DialogLidar = {
    {
QT_MOC_LITERAL(0, 0, 11), // "DialogLidar"
QT_MOC_LITERAL(1, 12, 13), // "grab_ScanData"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 4), // "loop"
QT_MOC_LITERAL(4, 32, 11), // "Ass_num_dev"
QT_MOC_LITERAL(5, 44, 3), // "num"
QT_MOC_LITERAL(6, 48, 10), // "lidar_port"
QT_MOC_LITERAL(7, 59, 8), // "mcu_port"
QT_MOC_LITERAL(8, 68, 26), // "on_pushButton_open_clicked"
QT_MOC_LITERAL(9, 95, 29), // "on_pushButton_getInfo_clicked"
QT_MOC_LITERAL(10, 125, 31), // "on_pushButton_getHealth_clicked"
QT_MOC_LITERAL(11, 157, 30), // "on_pushButton_stopScan_clicked"
QT_MOC_LITERAL(12, 188, 29), // "on_pushButton_MoterEn_clicked"
QT_MOC_LITERAL(13, 218, 7), // "checked"
QT_MOC_LITERAL(14, 226, 33), // "on_pushButton_IntensityON_cli..."
QT_MOC_LITERAL(15, 260, 34), // "on_pushButton_IntensityOFF_cl..."
QT_MOC_LITERAL(16, 295, 30), // "on_pushButton_loopTest_clicked"
QT_MOC_LITERAL(17, 326, 30), // "on_pushButton_loopStop_clicked"
QT_MOC_LITERAL(18, 357, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(19, 379, 11), // "sl_loop_end"
QT_MOC_LITERAL(20, 391, 11), // "sl_uart_dis"
QT_MOC_LITERAL(21, 403, 13), // "sl_result_dis"
QT_MOC_LITERAL(22, 417, 18) // "LidarResultDisplay"

    },
    "DialogLidar\0grab_ScanData\0\0loop\0"
    "Ass_num_dev\0num\0lidar_port\0mcu_port\0"
    "on_pushButton_open_clicked\0"
    "on_pushButton_getInfo_clicked\0"
    "on_pushButton_getHealth_clicked\0"
    "on_pushButton_stopScan_clicked\0"
    "on_pushButton_MoterEn_clicked\0checked\0"
    "on_pushButton_IntensityON_clicked\0"
    "on_pushButton_IntensityOFF_clicked\0"
    "on_pushButton_loopTest_clicked\0"
    "on_pushButton_loopStop_clicked\0"
    "on_pushButton_clicked\0sl_loop_end\0"
    "sl_uart_dis\0sl_result_dis\0LidarResultDisplay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DialogLidar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    0,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    3,   96,    2, 0x0a /* Public */,
       8,    0,  103,    2, 0x0a /* Public */,
       9,    0,  104,    2, 0x0a /* Public */,
      10,    0,  105,    2, 0x0a /* Public */,
      11,    0,  106,    2, 0x0a /* Public */,
      12,    1,  107,    2, 0x0a /* Public */,
      14,    0,  110,    2, 0x0a /* Public */,
      15,    0,  111,    2, 0x0a /* Public */,
      16,    0,  112,    2, 0x0a /* Public */,
      17,    0,  113,    2, 0x0a /* Public */,
      18,    0,  114,    2, 0x0a /* Public */,
      19,    0,  115,    2, 0x08 /* Private */,
      20,    1,  116,    2, 0x08 /* Private */,
      21,    1,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    5,    6,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, 0x80000000 | 22,    2,

       0        // eod
};

void DialogLidar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DialogLidar *_t = static_cast<DialogLidar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->grab_ScanData(); break;
        case 1: _t->loop(); break;
        case 2: _t->Ass_num_dev((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->on_pushButton_open_clicked(); break;
        case 4: _t->on_pushButton_getInfo_clicked(); break;
        case 5: _t->on_pushButton_getHealth_clicked(); break;
        case 6: _t->on_pushButton_stopScan_clicked(); break;
        case 7: _t->on_pushButton_MoterEn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_pushButton_IntensityON_clicked(); break;
        case 9: _t->on_pushButton_IntensityOFF_clicked(); break;
        case 10: _t->on_pushButton_loopTest_clicked(); break;
        case 11: _t->on_pushButton_loopStop_clicked(); break;
        case 12: _t->on_pushButton_clicked(); break;
        case 13: _t->sl_loop_end(); break;
        case 14: _t->sl_uart_dis((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->sl_result_dis((*reinterpret_cast< LidarResultDisplay(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (DialogLidar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogLidar::grab_ScanData)) {
                *result = 0;
            }
        }
        {
            typedef void (DialogLidar::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&DialogLidar::loop)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject DialogLidar::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_DialogLidar.data,
      qt_meta_data_DialogLidar,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DialogLidar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DialogLidar::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DialogLidar.stringdata0))
        return static_cast<void*>(const_cast< DialogLidar*>(this));
    return QDialog::qt_metacast(_clname);
}

int DialogLidar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void DialogLidar::grab_ScanData()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void DialogLidar::loop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
