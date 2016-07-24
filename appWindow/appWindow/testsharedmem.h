#include <qlocalserver.h>

#ifndef TESTSHAREDMEM_H
#define TESTSHAREDMEM_H

class testSharedMemTool{

public:
    testSharedMemTool();
    void initializeSharedMemory();
    void sendData();

    int previous_size;

private :
    uint64_t n_event_counter;
    QLocalServer *server;

};
#endif
