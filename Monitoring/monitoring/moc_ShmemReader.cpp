/****************************************************************************
** Meta object code from reading C++ file 'ShmemReader.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ShmemReader.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShmemReader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShmemReader_t {
    QByteArrayData data[20];
    char stringdata[263];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShmemReader_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShmemReader_t qt_meta_stringdata_ShmemReader = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ShmemReader"
QT_MOC_LITERAL(1, 12, 9), // "readEvent"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 9), // "readStrip"
QT_MOC_LITERAL(4, 33, 14), // "fillHistograms"
QT_MOC_LITERAL(5, 48, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(6, 73, 11), // "runNumberIs"
QT_MOC_LITERAL(7, 85, 21), // "runReadoutHistoFiller"
QT_MOC_LITERAL(8, 107, 11), // "fillReadout"
QT_MOC_LITERAL(9, 119, 4), // "line"
QT_MOC_LITERAL(10, 124, 7), // "newLine"
QT_MOC_LITERAL(11, 132, 16), // "newEventReceived"
QT_MOC_LITERAL(12, 149, 14), // "drawHistograms"
QT_MOC_LITERAL(13, 164, 16), // "handleSharedData"
QT_MOC_LITERAL(14, 181, 17), // "read_event_number"
QT_MOC_LITERAL(15, 199, 17), // "read_event_strips"
QT_MOC_LITERAL(16, 217, 17), // "getNameFromChipId"
QT_MOC_LITERAL(17, 235, 11), // "std::string"
QT_MOC_LITERAL(18, 247, 8), // "uint32_t"
QT_MOC_LITERAL(19, 256, 6) // "chipId"

    },
    "ShmemReader\0readEvent\0\0readStrip\0"
    "fillHistograms\0std::vector<std::string>\0"
    "runNumberIs\0runReadoutHistoFiller\0"
    "fillReadout\0line\0newLine\0newEventReceived\0"
    "drawHistograms\0handleSharedData\0"
    "read_event_number\0read_event_strips\0"
    "getNameFromChipId\0std::string\0uint32_t\0"
    "chipId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShmemReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   79,    2, 0x06 /* Public */,
       3,    0,   80,    2, 0x06 /* Public */,
       4,    2,   81,    2, 0x06 /* Public */,
       6,    1,   86,    2, 0x06 /* Public */,
       7,    0,   89,    2, 0x06 /* Public */,
       8,    1,   90,    2, 0x06 /* Public */,
      10,    0,   93,    2, 0x06 /* Public */,
      11,    1,   94,    2, 0x06 /* Public */,
      12,    0,   97,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   98,    2, 0x0a /* Public */,
      14,    0,   99,    2, 0x0a /* Public */,
      15,    0,  100,    2, 0x0a /* Public */,
      16,    1,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 17, 0x80000000 | 18,   19,

       0        // eod
};

void ShmemReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShmemReader *_t = static_cast<ShmemReader *>(_o);
        switch (_id) {
        case 0: _t->readEvent(); break;
        case 1: _t->readStrip(); break;
        case 2: _t->fillHistograms((*reinterpret_cast< std::vector<std::string>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->runNumberIs((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->runReadoutHistoFiller(); break;
        case 5: _t->fillReadout((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->newLine(); break;
        case 7: _t->newEventReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->drawHistograms(); break;
        case 9: _t->handleSharedData(); break;
        case 10: _t->read_event_number(); break;
        case 11: _t->read_event_strips(); break;
        case 12: { std::string _r = _t->getNameFromChipId((*reinterpret_cast< uint32_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ShmemReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::readEvent)) {
                *result = 0;
            }
        }
        {
            typedef void (ShmemReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::readStrip)) {
                *result = 1;
            }
        }
        {
            typedef void (ShmemReader::*_t)(std::vector<std::string> , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::fillHistograms)) {
                *result = 2;
            }
        }
        {
            typedef void (ShmemReader::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::runNumberIs)) {
                *result = 3;
            }
        }
        {
            typedef void (ShmemReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::runReadoutHistoFiller)) {
                *result = 4;
            }
        }
        {
            typedef void (ShmemReader::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::fillReadout)) {
                *result = 5;
            }
        }
        {
            typedef void (ShmemReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::newLine)) {
                *result = 6;
            }
        }
        {
            typedef void (ShmemReader::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::newEventReceived)) {
                *result = 7;
            }
        }
        {
            typedef void (ShmemReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::drawHistograms)) {
                *result = 8;
            }
        }
    }
}

const QMetaObject ShmemReader::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ShmemReader.data,
      qt_meta_data_ShmemReader,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ShmemReader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShmemReader::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ShmemReader.stringdata))
        return static_cast<void*>(const_cast< ShmemReader*>(this));
    return QObject::qt_metacast(_clname);
}

int ShmemReader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ShmemReader::readEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ShmemReader::readStrip()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ShmemReader::fillHistograms(std::vector<std::string> _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ShmemReader::runNumberIs(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ShmemReader::runReadoutHistoFiller()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}

// SIGNAL 5
void ShmemReader::fillReadout(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ShmemReader::newLine()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void ShmemReader::newEventReceived(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ShmemReader::drawHistograms()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
