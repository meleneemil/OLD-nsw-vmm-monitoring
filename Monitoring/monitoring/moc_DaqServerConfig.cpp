/****************************************************************************
** Meta object code from reading C++ file 'DaqServerConfig.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "DaqServerConfig.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DaqServerConfig.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_online__display__CDaqServerConfig_t {
    QByteArrayData data[23];
    char stringdata[394];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_online__display__CDaqServerConfig_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_online__display__CDaqServerConfig_t qt_meta_stringdata_online__display__CDaqServerConfig = {
    {
QT_MOC_LITERAL(0, 0, 33), // "online::display::CDaqServerCo..."
QT_MOC_LITERAL(1, 34, 12), // "sendStartDaq"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 11), // "std::string"
QT_MOC_LITERAL(4, 60, 7), // "command"
QT_MOC_LITERAL(5, 68, 11), // "sendStopDaq"
QT_MOC_LITERAL(6, 80, 13), // "sendConfigDaq"
QT_MOC_LITERAL(7, 94, 14), // "configWithFile"
QT_MOC_LITERAL(8, 109, 17), // "setConfigFilePath"
QT_MOC_LITERAL(9, 127, 15), // "config_filePath"
QT_MOC_LITERAL(10, 143, 17), // "setConfigFileName"
QT_MOC_LITERAL(11, 161, 15), // "config_fileName"
QT_MOC_LITERAL(12, 177, 9), // "configure"
QT_MOC_LITERAL(13, 187, 10), // "configFile"
QT_MOC_LITERAL(14, 198, 19), // "transmitStartSignal"
QT_MOC_LITERAL(15, 218, 18), // "transmitStopSignal"
QT_MOC_LITERAL(16, 237, 18), // "openSettingsWindow"
QT_MOC_LITERAL(17, 256, 32), // "updateFrameCanvasesDivision_slot"
QT_MOC_LITERAL(18, 289, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(19, 306, 14), // "parentTreeItem"
QT_MOC_LITERAL(20, 321, 29), // "selectDeselectChamberChildren"
QT_MOC_LITERAL(21, 351, 16), // "parentTreeWidget"
QT_MOC_LITERAL(22, 368, 25) // "numberOfReadoutsToDisplay"

    },
    "online::display::CDaqServerConfig\0"
    "sendStartDaq\0\0std::string\0command\0"
    "sendStopDaq\0sendConfigDaq\0configWithFile\0"
    "setConfigFilePath\0config_filePath\0"
    "setConfigFileName\0config_fileName\0"
    "configure\0configFile\0transmitStartSignal\0"
    "transmitStopSignal\0openSettingsWindow\0"
    "updateFrameCanvasesDivision_slot\0"
    "QTreeWidgetItem*\0parentTreeItem\0"
    "selectDeselectChamberChildren\0"
    "parentTreeWidget\0numberOfReadoutsToDisplay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_online__display__CDaqServerConfig[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    1,   82,    2, 0x06 /* Public */,
       6,    1,   85,    2, 0x06 /* Public */,
       7,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   91,    2, 0x0a /* Public */,
      10,    1,   94,    2, 0x0a /* Public */,
      12,    1,   97,    2, 0x0a /* Public */,
      14,    0,  100,    2, 0x0a /* Public */,
      15,    0,  101,    2, 0x0a /* Public */,
      16,    0,  102,    2, 0x0a /* Public */,
      17,    1,  103,    2, 0x0a /* Public */,
      20,    1,  106,    2, 0x0a /* Public */,
      22,    1,  109,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 18,   21,
    QMetaType::Int, 0x80000000 | 18,   21,

       0        // eod
};

void online::display::CDaqServerConfig::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CDaqServerConfig *_t = static_cast<CDaqServerConfig *>(_o);
        switch (_id) {
        case 0: _t->sendStartDaq((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->sendStopDaq((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->sendConfigDaq((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 3: _t->configWithFile((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->setConfigFilePath((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setConfigFileName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->configure((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->transmitStartSignal(); break;
        case 8: _t->transmitStopSignal(); break;
        case 9: _t->openSettingsWindow(); break;
        case 10: _t->updateFrameCanvasesDivision_slot((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 11: _t->selectDeselectChamberChildren((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 12: { int _r = _t->numberOfReadoutsToDisplay((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CDaqServerConfig::*_t)(std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDaqServerConfig::sendStartDaq)) {
                *result = 0;
            }
        }
        {
            typedef void (CDaqServerConfig::*_t)(std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDaqServerConfig::sendStopDaq)) {
                *result = 1;
            }
        }
        {
            typedef void (CDaqServerConfig::*_t)(std::string );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDaqServerConfig::sendConfigDaq)) {
                *result = 2;
            }
        }
        {
            typedef void (CDaqServerConfig::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CDaqServerConfig::configWithFile)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject online::display::CDaqServerConfig::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_online__display__CDaqServerConfig.data,
      qt_meta_data_online__display__CDaqServerConfig,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *online::display::CDaqServerConfig::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *online::display::CDaqServerConfig::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_online__display__CDaqServerConfig.stringdata))
        return static_cast<void*>(const_cast< CDaqServerConfig*>(this));
    return QObject::qt_metacast(_clname);
}

int online::display::CDaqServerConfig::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void online::display::CDaqServerConfig::sendStartDaq(std::string _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void online::display::CDaqServerConfig::sendStopDaq(std::string _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void online::display::CDaqServerConfig::sendConfigDaq(std::string _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void online::display::CDaqServerConfig::configWithFile(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
