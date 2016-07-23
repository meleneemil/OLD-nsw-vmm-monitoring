#include "testsharedmem.h"

#include <iostream>
#include <vector>
#include <string>
#include "boost/date_time/posix_time/posix_time.hpp"

int waiting_time = 10000;

testSharedMemTool::testSharedMemTool() :
    previous_size(0),
    m_shm_eventNumber(0),
    n_event_counter(0),
    m_shm_eventinfo_vector(0),
    m_shm_manager(0),
    m_shm_condition(0)
{
}


//// initialize the shared memory objects
void testSharedMemTool::initializeSharedMemory()
{
    boost::interprocess::shared_memory_object::remove("mmDaqSharedMemory");
    boost::interprocess::named_condition::remove("mmDaqSharedCondition");
    boost::interprocess::named_mutex::remove("mmDaqSharedMutex");

    if(!m_shm_manager)
        m_shm_manager = new boost::interprocess::managed_shared_memory(boost::interprocess::open_or_create,
                                                                       "mmDaqSharedMemory",
                                                                       (104857600 * 10) );

    if(!m_shm_condition)
        m_shm_condition = new boost::interprocess::named_condition(boost::interprocess::open_or_create,
                                                                   "mmDaqSharedCondition");
    m_shm_eventNumber = m_shm_manager->find_or_construct<uint64_t>("mmDaqSharedEventNumber")(0);

    m_shm_eventinfo_vector = m_shm_manager->construct<ShmemCharStringVector>
            ("mmDaqSharedEventData")
            (m_shm_manager->get_allocator<ShmemCharVectorAllocator>());

    boost::interprocess::named_mutex shm_mutex(boost::interprocess::open_or_create, "mmDaqSharedMutex");
    boost::interprocess::scoped_lock< boost::interprocess::named_mutex > lock(shm_mutex,
                                                                              boost::interprocess::defer_lock_type());


}

void testSharedMemTool::sendData()
{

    boost::interprocess::named_mutex shm_mutex(boost::interprocess::open_or_create, "mmDaqSharedMutex");
    boost::interprocess::scoped_lock< boost::interprocess::named_mutex > lock(shm_mutex,
                                                                              boost::interprocess::defer_lock_type());
    std::cout << "testSharedMemTool::sendData" << std::endl;

    //    m_shm_condition->notify_all();

    int n = 0;
    while(n<100000) {

//        if(n%1000==0)
//        std::cout << "Done: "<< 1000/100000*100 <<"%\n";
        usleep(5000-rand()%1900);

        try {
//            std::cout << "in try" << std::endl;

            boost::posix_time::ptime timeout(boost::posix_time::second_clock::universal_time() + boost::posix_time::seconds(5));
            //  if(m_shm_condition->timed_wait(lock, timeout)) {
            if(!lock.timed_lock(timeout)) {
//                std::cout << " *** DATAWRITER : LOCK TIMED OUT *** " << std::endl;

                //aikoulou: nah, doesnt work
//                std::cout << " *** TRYING TO FORCE UNLOCK *** " << std::endl;
//                lock.unlock();
            }
            else
            {
                sendEventNumber();
                sendEventInfo();
                m_shm_condition->notify_all();
                //                m_shm_condition->wait(lock);
            }
            //    m_shm_condition->wait(lock);
            if(lock) {
                lock.unlock();
            }
        } // try
        catch(boost::interprocess::interprocess_exception &e) {
            std::cout << " *** DATAWRITER : ERROR :: " << e.what() << std::endl;
        }
        n++;
    } // while
    return;
}

void testSharedMemTool::sendEventNumber()
{
    *m_shm_eventNumber = n_event_counter;
    n_event_counter++;
}

void testSharedMemTool::sendEventInfo()
{
    std::string str_strip = std::to_string(  (rand()%100)/2  +   (rand())%100/2    +120   );
    std::string str_charge = std::to_string(  (rand()%300)/4  +  (rand()%130)/4  +  (rand()%300)/4  +   (rand())%1500/4    +1000   );
    std::string str_time = std::to_string(  (rand()%500)/2  +   (rand())%500/2    +250   );
    std::string str_pdo = std::to_string(  (rand()%500)/2  +   (rand())%300/2    +100   );
    std::string str_tdo = std::to_string(  (rand()%150)/2  +   (rand())%350/2    +500   );

    std::string str_chamber="TZ2";
    //    if(rand()%2==0)
    //        str_chamber="TZ2";

    //      int n =  1    2             3 4 5   6           7 8  9    10             11          12           13
    std::string x = "10 "+str_chamber+" 0 0 X "+str_strip+" 1 20 60 "+str_charge+" "+str_time+" "+str_pdo+" "+str_tdo;
    std::vector<std::string> out;
    for(int i = 0; i < 5; i++) {
        out.push_back(x);
    }
    ShmemCharString local_string(m_shm_manager->get_allocator<ShmemCharAllocator>());
    if(previous_size >= m_shm_eventinfo_vector->size())
    previous_size = m_shm_eventinfo_vector->size();

    if(m_shm_eventinfo_vector->size() > 200)
    {
        //don't send more to memory, because it fills it up, so we wait until the memory is read=cleared to send again.
        //maybe even clear the memory?
        m_shm_eventinfo_vector->clear();
    }
    else
    {
        for(auto ev : out) {
            local_string = ev.c_str();
            m_shm_eventinfo_vector->push_back(local_string);
        } // ev
    }
    out.clear();
    return;

}
