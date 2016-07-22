//
//  SharedEBBuffer.cpp
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 08/07/2012.
//  Copyright (c) 2012 CERN - PH/ADE. All rights reserved.
//


#include "SharedEBBuffer.h"
//#include "SharedMMEvent.h"
//#include "DaqServerConfig.h"

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
//#include <boost/foreach.hpp>
#include <cassert>

#include <iostream>

#include <QObject>

using namespace online::display;

namespace bipc= boost::interprocess;

CSharedEBBuffer::CSharedEBBuffer(ShmemVoidAllocator alloc_inst) :
m_mutex(),
m_chips(alloc_inst),
m_max_event_depth(0)
{ }


CSharedEBBuffer::~CSharedEBBuffer()
{
   std::cout << "CSharedEBBuffer() destructor" << std::endl;
}

size_t CSharedEBBuffer::max_event_depth() const
{
   return m_max_event_depth;
}


void CSharedEBBuffer::print() const
{
   std::cout << "=== CSharedEBBuffer::print() === " << std::endl;
   std::cout << " chips size = "<< m_chips.size() << std::endl;
   int ii =0;
   Q_FOREACH(CSharedChip chip, m_chips) {

            chip.print();
   }
}
