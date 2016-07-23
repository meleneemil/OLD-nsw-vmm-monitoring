/****************************************************************************
** Meta object code from reading C++ file 'DisplayDrawer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DisplayDrawer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DisplayDrawer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_DisplayDrawer_t {
    QByteArrayData data[26];
    char stringdata[340];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DisplayDrawer_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DisplayDrawer_t qt_meta_stringdata_DisplayDrawer = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DisplayDrawer"
QT_MOC_LITERAL(1, 14, 10), // "NotifyFill"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(4, 51, 9), // "stripData"
QT_MOC_LITERAL(5, 61, 11), // "eventNumber"
QT_MOC_LITERAL(6, 73, 10), // "NotifyDraw"
QT_MOC_LITERAL(7, 84, 14), // "drawSharedData"
QT_MOC_LITERAL(8, 99, 18), // "readoutHistoFiller"
QT_MOC_LITERAL(9, 118, 19), // "handleBufferedEvent"
QT_MOC_LITERAL(10, 138, 9), // "line_qstr"
QT_MOC_LITERAL(11, 148, 17), // "fillReadoutHistos"
QT_MOC_LITERAL(12, 166, 11), // "std::string"
QT_MOC_LITERAL(13, 178, 11), // "chamberName"
QT_MOC_LITERAL(14, 190, 11), // "readoutName"
QT_MOC_LITERAL(15, 202, 5), // "strip"
QT_MOC_LITERAL(16, 208, 6), // "charge"
QT_MOC_LITERAL(17, 215, 4), // "time"
QT_MOC_LITERAL(18, 220, 3), // "pdo"
QT_MOC_LITERAL(19, 224, 3), // "tdo"
QT_MOC_LITERAL(20, 228, 14), // "drawHistograms"
QT_MOC_LITERAL(21, 243, 20), // "drawStatisticsHistos"
QT_MOC_LITERAL(22, 264, 15), // "drawEventHistos"
QT_MOC_LITERAL(23, 280, 10), // "reset_slot"
QT_MOC_LITERAL(24, 291, 26), // "resetStatisticsHistos_slot"
QT_MOC_LITERAL(25, 318, 21) // "resetEventHistos_slot"

    },
    "DisplayDrawer\0NotifyFill\0\0"
    "std::vector<std::string>\0stripData\0"
    "eventNumber\0NotifyDraw\0drawSharedData\0"
    "readoutHistoFiller\0handleBufferedEvent\0"
    "line_qstr\0fillReadoutHistos\0std::string\0"
    "chamberName\0readoutName\0strip\0charge\0"
    "time\0pdo\0tdo\0drawHistograms\0"
    "drawStatisticsHistos\0drawEventHistos\0"
    "reset_slot\0resetStatisticsHistos_slot\0"
    "resetEventHistos_slot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DisplayDrawer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x0a /* Public */,
       6,    0,   79,    2, 0x0a /* Public */,
       7,    0,   80,    2, 0x0a /* Public */,
       8,    0,   81,    2, 0x0a /* Public */,
       9,    1,   82,    2, 0x0a /* Public */,
      11,    7,   85,    2, 0x0a /* Public */,
      20,    0,  100,    2, 0x0a /* Public */,
      21,    0,  101,    2, 0x0a /* Public */,
      22,    0,  102,    2, 0x0a /* Public */,
      23,    0,  103,    2, 0x0a /* Public */,
      24,    0,  104,    2, 0x0a /* Public */,
      25,    0,  105,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QString,   10,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 12, QMetaType::Int, QMetaType::Float, QMetaType::Float, QMetaType::Int, QMetaType::Int,   13,   14,   15,   16,   17,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DisplayDrawer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DisplayDrawer *_t = static_cast<DisplayDrawer *>(_o);
        switch (_id) {
        case 0: _t->NotifyFill((*reinterpret_cast< std::vector<std::string>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->NotifyDraw(); break;
        case 2: _t->drawSharedData(); break;
        case 3: _t->readoutHistoFiller(); break;
        case 4: { int _r = _t->handleBufferedEvent((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: _t->fillReadoutHistos((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< float(*)>(_a[4])),(*reinterpret_cast< float(*)>(_a[5])),(*reinterpret_cast< int(*)>(_a[6])),(*reinterpret_cast< int(*)>(_a[7]))); break;
        case 6: _t->drawHistograms(); break;
        case 7: _t->drawStatisticsHistos(); break;
        case 8: _t->drawEventHistos(); break;
        case 9: _t->reset_slot(); break;
        case 10: _t->resetStatisticsHistos_slot(); break;
        case 11: _t->resetEventHistos_slot(); break;
        default: ;
        }
    }
}

const QMetaObject DisplayDrawer::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_DisplayDrawer.data,
      qt_meta_data_DisplayDrawer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *DisplayDrawer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DisplayDrawer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_DisplayDrawer.stringdata))
        return static_cast<void*>(const_cast< DisplayDrawer*>(this));
    return QObject::qt_metacast(_clname);
}

int DisplayDrawer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
