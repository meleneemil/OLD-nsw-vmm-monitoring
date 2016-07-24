
#ifndef SHMEMREADER_H
#define SHMEMREADER_H

#include "AsioService.h"
#include "mainwindow.h"
#include "DisplayDrawer.h"

#include "DetBase.h"
#include "DetChamber.h"
#include "DetReadout.h"
#include "SrsTypes.h"
#include "DetTypes.h"
#include "SrsFec.h"
#include "SrsChip.h"


#include <QObject>
#include <QWaitCondition>
#include <QMutex>
#include <QTimer>
#include <QVector>

#include <vector>

#ifndef Q_MOC_RUN

#include <qlocalsocket.h>
#include <QLocalSocket>

#endif
//+++++++++++++++++++++++++++namespaces for shared memory data++++++++++++++++++++++++++++++++++++++++++++++++++
namespace bipc = boost::interprocess;

typedef bipc::managed_shared_memory::segment_manager ShmemSegmentManagerType;

typedef boost::interprocess::interprocess_mutex ShmemMutexType;
typedef boost::interprocess::scoped_lock< ShmemMutexType > ShmemScopedLock;

typedef boost::interprocess::named_mutex ShmemNamedMutexType;
typedef boost::interprocess::scoped_lock< ShmemNamedMutexType > ShmemNamedScopedLock;

typedef boost::interprocess::named_condition ShmemNamedCondition;

//Typedefs of allocators and containers
typedef bipc::allocator<void, ShmemSegmentManagerType>                        ShmemVoidAllocator;
//string, vector of string
typedef bipc::allocator<char, ShmemSegmentManagerType>                        ShmemCharAllocator;
typedef bipc::basic_string<char, std::char_traits<char>, ShmemCharAllocator>  ShmemCharString;
typedef bipc::allocator<ShmemCharString, ShmemSegmentManagerType>             ShmemCharVectorAllocator;
typedef bipc::vector<ShmemCharString, ShmemCharVectorAllocator>               ShmemCharStringVector;
//uint32
typedef bipc::allocator<uint32_t, ShmemSegmentManagerType>  ShmemUint32Allocator;
typedef bipc::vector<uint32_t, ShmemUint32Allocator>        ShmemUint32Vector;
//int16
typedef bipc::allocator<int16_t, ShmemSegmentManagerType>  ShmemInt16Allocator;
typedef bipc::vector<int16_t, ShmemInt16Allocator>        ShmemInt16Vector;


//all this to have map of vectors ShmemRawDataMap

//Note that map<Key, MappedType>'s value_type is std::pair<const Key, MappedType>,
//so the allocator must allocate that pair.
//map is [chipid] = (raw vector int16)
typedef uint32_t  ShmemRawMapKeyType;
typedef ShmemInt16Vector ShmemRawMapMappedType;
typedef std::pair<const ShmemRawMapKeyType, ShmemRawMapMappedType> ShmemRawMapValueType;

//Alias an STL compatible allocator of for the map.
//This allocator will allow to place containers
//in managed shared memory segments
typedef bipc::allocator<ShmemRawMapValueType, ShmemSegmentManagerType> ShmemRawMapAllocator;

//Alias a map of ints that uses the previous STL-like allocator.
//Note that the third parameter argument is the ordering function
//of the map, just like with std::map, used to compare the keys.

typedef bipc::map<ShmemRawMapKeyType, ShmemRawMapMappedType, std::less<ShmemRawMapKeyType>, ShmemRawMapAllocator> ShmemRawMap;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


class ShmemReader : public QObject
{
    Q_OBJECT

public:
    ShmemReader(
                std::vector<
                    std::pair<
                        boost::shared_ptr<online::display::CDetChamber>,
                        std::vector<boost::shared_ptr<online::display::CDetReadout> >
                    >
                > chamberElements,
                MainWindow *window);

    ~ShmemReader();

    MainWindow *mainWindow;
    DisplayDrawer *mainDrawer;

    std::vector<std::pair<boost::shared_ptr<online::display::CDetChamber>, std::vector<boost::shared_ptr<online::display::CDetReadout> > > > configuredChamberElements;
    std::vector <std::string> stripDataEvent;
    int eventDisplayed;

private:
    bool realEvent;

signals:
    void fillHistograms(std::vector <std::string>, int);
    void drawHistograms();


private:
    QLocalSocket *socket;
    QString currentFortune;
    quint16 blockSize;

private slots:
    void readFortune();


};

#endif // SHMEMREADER_H
