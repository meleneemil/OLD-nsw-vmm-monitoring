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
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ShmemReader.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ShmemReader_t {
    QByteArrayData data[29];
    char stringdata[408];
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
QT_MOC_LITERAL(3, 23, 7), // "readRaw"
QT_MOC_LITERAL(4, 31, 9), // "readStrip"
QT_MOC_LITERAL(5, 41, 14), // "fillHistograms"
QT_MOC_LITERAL(6, 56, 42), // "QVector<std::pair<QString,QVe..."
QT_MOC_LITERAL(7, 99, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(8, 124, 11), // "runNumberIs"
QT_MOC_LITERAL(9, 136, 10), // "fillApvRaw"
QT_MOC_LITERAL(10, 147, 12), // "QVector<int>"
QT_MOC_LITERAL(11, 160, 21), // "runReadoutHistoFiller"
QT_MOC_LITERAL(12, 182, 11), // "fillReadout"
QT_MOC_LITERAL(13, 194, 4), // "line"
QT_MOC_LITERAL(14, 199, 7), // "newLine"
QT_MOC_LITERAL(15, 207, 16), // "newEventReceived"
QT_MOC_LITERAL(16, 224, 14), // "drawHistograms"
QT_MOC_LITERAL(17, 239, 16), // "handleSharedData"
QT_MOC_LITERAL(18, 256, 17), // "read_event_number"
QT_MOC_LITERAL(19, 274, 13), // "read_raw_data"
QT_MOC_LITERAL(20, 288, 17), // "read_event_strips"
QT_MOC_LITERAL(21, 306, 16), // "fillApvChipsList"
QT_MOC_LITERAL(22, 323, 21), // "std::vector<uint32_t>"
QT_MOC_LITERAL(23, 345, 7), // "apvList"
QT_MOC_LITERAL(24, 353, 8), // "apvChips"
QT_MOC_LITERAL(25, 362, 17), // "getNameFromChipId"
QT_MOC_LITERAL(26, 380, 11), // "std::string"
QT_MOC_LITERAL(27, 392, 8), // "uint32_t"
QT_MOC_LITERAL(28, 401, 6) // "chipId"

    },
    "ShmemReader\0readEvent\0\0readRaw\0readStrip\0"
    "fillHistograms\0"
    "QVector<std::pair<QString,QVector<int> > >\0"
    "std::vector<std::string>\0runNumberIs\0"
    "fillApvRaw\0QVector<int>\0runReadoutHistoFiller\0"
    "fillReadout\0line\0newLine\0newEventReceived\0"
    "drawHistograms\0handleSharedData\0"
    "read_event_number\0read_raw_data\0"
    "read_event_strips\0fillApvChipsList\0"
    "std::vector<uint32_t>\0apvList\0apvChips\0"
    "getNameFromChipId\0std::string\0uint32_t\0"
    "chipId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShmemReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   99,    2, 0x06 /* Public */,
       3,    0,  100,    2, 0x06 /* Public */,
       4,    0,  101,    2, 0x06 /* Public */,
       5,    3,  102,    2, 0x06 /* Public */,
       8,    1,  109,    2, 0x06 /* Public */,
       9,    2,  112,    2, 0x06 /* Public */,
      11,    0,  117,    2, 0x06 /* Public */,
      12,    1,  118,    2, 0x06 /* Public */,
      14,    0,  121,    2, 0x06 /* Public */,
      15,    1,  122,    2, 0x06 /* Public */,
      16,    0,  125,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  126,    2, 0x0a /* Public */,
      18,    0,  127,    2, 0x0a /* Public */,
      19,    0,  128,    2, 0x0a /* Public */,
      20,    0,  129,    2, 0x0a /* Public */,
      21,    2,  130,    2, 0x0a /* Public */,
      25,    1,  135,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 7, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 10,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22, 0x80000000 | 7,   23,   24,
    0x80000000 | 26, 0x80000000 | 27,   28,

       0        // eod
};

void ShmemReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShmemReader *_t = static_cast<ShmemReader *>(_o);
        switch (_id) {
        case 0: _t->readEvent(); break;
        case 1: _t->readRaw(); break;
        case 2: _t->readStrip(); break;
        case 3: _t->fillHistograms((*reinterpret_cast< QVector<std::pair<QString,QVector<int> > >(*)>(_a[1])),(*reinterpret_cast< std::vector<std::string>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 4: _t->runNumberIs((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 5: _t->fillApvRaw((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVector<int>(*)>(_a[2]))); break;
        case 6: _t->runReadoutHistoFiller(); break;
        case 7: _t->fillReadout((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->newLine(); break;
        case 9: _t->newEventReceived((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->drawHistograms(); break;
        case 11: _t->handleSharedData(); break;
        case 12: _t->read_event_number(); break;
        case 13: _t->read_raw_data(); break;
        case 14: _t->read_event_strips(); break;
        case 15: _t->fillApvChipsList((*reinterpret_cast< std::vector<uint32_t>(*)>(_a[1])),(*reinterpret_cast< std::vector<std::string>(*)>(_a[2]))); break;
        case 16: { std::string _r = _t->getNameFromChipId((*reinterpret_cast< uint32_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
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
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::readRaw)) {
                *result = 1;
            }
        }
        {
            typedef void (ShmemReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::readStrip)) {
                *result = 2;
            }
        }
        {
            typedef void (ShmemReader::*_t)(QVector<std::pair<QString,QVector<int> > > , std::vector<std::string> , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::fillHistograms)) {
                *result = 3;
            }
        }
        {
            typedef void (ShmemReader::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::runNumberIs)) {
                *result = 4;
            }
        }
        {
            typedef void (ShmemReader::*_t)(QString , QVector<int> );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::fillApvRaw)) {
                *result = 5;
            }
        }
        {
            typedef void (ShmemReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::runReadoutHistoFiller)) {
                *result = 6;
            }
        }
        {
            typedef void (ShmemReader::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::fillReadout)) {
                *result = 7;
            }
        }
        {
            typedef void (ShmemReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::newLine)) {
                *result = 8;
            }
        }
        {
            typedef void (ShmemReader::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::newEventReceived)) {
                *result = 9;
            }
        }
        {
            typedef void (ShmemReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::drawHistograms)) {
                *result = 10;
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
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ShmemReader::readEvent()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void ShmemReader::readRaw()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void ShmemReader::readStrip()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void ShmemReader::fillHistograms(QVector<std::pair<QString,QVector<int> > > _t1, std::vector<std::string> _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ShmemReader::runNumberIs(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ShmemReader::fillApvRaw(QString _t1, QVector<int> _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ShmemReader::runReadoutHistoFiller()
{
    QMetaObject::activate(this, &staticMetaObject, 6, Q_NULLPTR);
}

// SIGNAL 7
void ShmemReader::fillReadout(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ShmemReader::newLine()
{
    QMetaObject::activate(this, &staticMetaObject, 8, Q_NULLPTR);
}

// SIGNAL 9
void ShmemReader::newEventReceived(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ShmemReader::drawHistograms()
{
    QMetaObject::activate(this, &staticMetaObject, 10, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
