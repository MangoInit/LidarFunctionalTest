/****************************************************************************
** Meta object code from reading C++ file 'uart.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../LidarFunctionalTest/uart.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uart.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_UART_t {
    QByteArrayData data[8];
    char stringdata0[91];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_UART_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_UART_t qt_meta_stringdata_UART = {
    {
QT_MOC_LITERAL(0, 0, 4), // "UART"
QT_MOC_LITERAL(1, 5, 15), // "uart_disconnect"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(4, 51, 5), // "error"
QT_MOC_LITERAL(5, 57, 9), // "uart_open"
QT_MOC_LITERAL(6, 67, 12), // "uart_receive"
QT_MOC_LITERAL(7, 80, 10) // "uart_write"

    },
    "UART\0uart_disconnect\0\0"
    "QSerialPort::SerialPortError\0error\0"
    "uart_open\0uart_receive\0uart_write"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_UART[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x0a /* Public */,
       5,    0,   37,    2, 0x0a /* Public */,
       6,    0,   38,    2, 0x0a /* Public */,
       7,    0,   39,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void UART::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        UART *_t = static_cast<UART *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->uart_disconnect((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 1: { bool _r = _t->uart_open();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 2: _t->uart_receive(); break;
        case 3: _t->uart_write(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject UART::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_UART.data,
      qt_meta_data_UART,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *UART::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UART::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_UART.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int UART::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE