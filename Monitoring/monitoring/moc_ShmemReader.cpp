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
    QByteArrayData data[9];
    char stringdata[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ShmemReader_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ShmemReader_t qt_meta_stringdata_ShmemReader = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ShmemReader"
QT_MOC_LITERAL(1, 12, 14), // "fillHistograms"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 24), // "std::vector<std::string>"
QT_MOC_LITERAL(4, 53, 14), // "drawHistograms"
QT_MOC_LITERAL(5, 68, 16), // "handleSharedData"
QT_MOC_LITERAL(6, 85, 17), // "read_event_number"
QT_MOC_LITERAL(7, 103, 17), // "read_event_strips"
QT_MOC_LITERAL(8, 121, 11) // "readFortune"

    },
    "ShmemReader\0fillHistograms\0\0"
    "std::vector<std::string>\0drawHistograms\0"
    "handleSharedData\0read_event_number\0"
    "read_event_strips\0readFortune"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ShmemReader[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       4,    0,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   50,    2, 0x0a /* Public */,
       6,    0,   51,    2, 0x0a /* Public */,
       7,    0,   52,    2, 0x0a /* Public */,
       8,    0,   53,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::Int,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ShmemReader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ShmemReader *_t = static_cast<ShmemReader *>(_o);
        switch (_id) {
        case 0: _t->fillHistograms((*reinterpret_cast< std::vector<std::string>(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->drawHistograms(); break;
        case 2: _t->handleSharedData(); break;
        case 3: _t->read_event_number(); break;
        case 4: _t->read_event_strips(); break;
        case 5: _t->readFortune(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ShmemReader::*_t)(std::vector<std::string> , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::fillHistograms)) {
                *result = 0;
            }
        }
        {
            typedef void (ShmemReader::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ShmemReader::drawHistograms)) {
                *result = 1;
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
void ShmemReader::fillHistograms(std::vector<std::string> _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ShmemReader::drawHistograms()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
