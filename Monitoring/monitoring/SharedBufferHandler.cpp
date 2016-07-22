//
//  SharedBufferHandler.cpp
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 09/07/2012.
//  Copyright (c) 2012 CERN - PH/ADE. All rights reserved.
//

#include "SharedBufferHandler.h"

#include <iostream>
#include <vector>
using namespace online::display;

CSharedBufferHandler::CSharedBufferHandler() :
m_shm_manager(bipc::open_or_create, "mmDaqSharedEBSegment", 65536),
m_shm_mutex(m_shm_manager.find< ShmemMutexType >( "mutex" ).first ),
m_shm_chips(m_shm_manager.find< ShmemChipVector >( "mmDaqSharedEBBuffer" ).first  ) ,
m_max_event_depth(0)
{
   
   std::cout << "*** CSharedBufferHandler() constructor" << std::endl;
  
}

void CSharedBufferHandler::print() {
  std::cout << "locking mutex... "<< std::endl;
  if((m_shm_manager.find< ShmemMutexType >( "mutex" ).second != 1))
     return;

  ShmemScopedLock lock(*m_shm_mutex);
   std::cout << "CSharedBufferHandler::print():  #shmchips = " << m_shm_chips->size() << std::endl;
   
   for (ShmemChipVector::const_iterator isc = m_shm_chips->begin(); isc != m_shm_chips->end(); ++isc) {
      isc->print();
   }

}

CSharedBufferHandler::~CSharedBufferHandler()
{
   std::cout << "*** CSharedBufferHandler() destructor" << std::endl;
 try
   {
      m_shm_mutex->unlock();
   }
   catch ( ... )
   {
   }
}


void CSharedBufferHandler::clear()
{
}

size_t CSharedBufferHandler::max_event_depth() const
{
   return m_max_event_depth;
}

