//
//  SrsFec.cpp
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 26.4.12.
//  Copyright (c) 2012 CERN - PH/ADE. All rights reserved.
//

#include "SrsFec.h"
#include "UDPFrame.h"
//#include "EventBuilder.h"
//#include "SrsEventBuilder.h"
#include "SrsChip.h"
#include "DaqServerConfig.h"


#include <boost/thread.hpp>
//#include <boost/foreach.hpp>

#include <sstream>
#include <iostream>
#include <algorithm>


using namespace online::display;

CSrsFec::TimeStampModeType CSrsFec::SrsTimeStampMode = CSrsFec::fecTsModeInvalid;


CSrsFec::CSrsFec(size_t idnum, const std::string& name, const std::string& ip_address) :
CSrsNetworkDevice(idnum, name, boost::asio::ip::address::from_string(ip_address)),
m_chips(),
m_event_number(0),
m_counter_error_decode_fec_header(0),
m_counter_error_decode_udp(0),
m_counter_error_create_event(0)
{
   
}

CSrsFec::CSrsFec(size_t idnum, const std::string& name, const boost::asio::ip::address& ip_address) :
CSrsNetworkDevice(idnum, name, ip_address),
m_chips(),
m_event_number(0),
m_counter_error_decode_fec_header(0),
m_counter_error_decode_udp(0),
m_counter_error_create_event(0)
{
   
}

CSrsFec::~CSrsFec()
{
   
}


void CSrsFec::configure(const CDaqServerConfig* daqconfig)
{
   //CSrsFec::SrsTimeStampMode = daqconfig->get_fec_time_stamp_mode();
}

void CSrsFec::reset() 
{
   m_event_number = 0;
   m_counter_error_decode_fec_header = 0;
   m_counter_error_decode_udp = 0;
   m_counter_error_create_event = 0;
   std::for_each(m_chips.begin(), m_chips.end(), boost::bind(&CSrsChip::reset, _1));
}

void CSrsFec::add_chip(boost::shared_ptr<CSrsChip> chip_ptr) 
{
   chip_ptr->set_chip_id_to_fec(m_uid);
   std::cout << "CSrsFec::add_chip to FEC id=" << uid() << " " 
   << chip_ptr->get_chip_id().get_string() << " '" 
   << chip_ptr->name() << "'" << std::endl;
   
   SrsChipPtr old = locate_chip(chip_ptr->get_chip_id().chip_no(), "");

   if (!old) {
      m_chips.push_back(chip_ptr);
   }
   else {
      std::stringstream ss;
      ss << "FEC add chip error: duplicate id " << chip_ptr->get_chip_id().get_string();
      throw std::runtime_error(ss.str().c_str());
   }
}


const std::vector<SrsChipPtr>& CSrsFec::get_chips() const
{
   return m_chips;
}

void CSrsFec::clear()
{
   //m_event_list.clear();
   m_chips.clear();
   m_event_number = 0;
   m_counter_error_decode_fec_header = 0;
   m_counter_error_decode_udp = 0;
   m_counter_error_create_event = 0;
//   CSrsNetworkDevice::clear();
}


boost::shared_ptr<CSrsChip> CSrsFec::get_srs_chip(int chip_no)
{
   typedef std::vector<boost::shared_ptr<CSrsChip> > chip_cont;
   
   chip_cont::iterator found = std::find_if(m_chips.begin(), 
                                         m_chips.end(), 
                                         CSrsChip::ChipNoEquals(chip_no));
   if (found == m_chips.end()) {
      return boost::shared_ptr<CSrsChip>();
   }
   return *found;
}

const size_t& CSrsFec::daq_event_number() const
{
   return m_event_number;
}


void CSrsFec::next_event()
{
   m_event_number+=1;
}


void CSrsFec::increment_counter_decode_fec()
{
   m_counter_error_decode_fec_header += 1;  
}

/**
 search for chip by id or name
 */
boost::shared_ptr<CSrsChip> CSrsFec::locate_chip(long chip_id, const std::string& name)
{
   typedef  std::vector<SrsChipPtr> srs_chip_cont;
   typedef  std::vector<SrsChipPtr>::iterator srs_chip_iter;
   
   int chip_no = chip_id;
   if (chip_id<0 && name.empty()) {
      throw std::runtime_error("CSrsFec::locate_chip() no data to search by ");
//      return boost::shared_ptr<CSrsChip>();
   }
   
   if (chip_id<0) {
      //search by name
      srs_chip_iter chip1 = std::find_if(m_chips.begin(), m_chips.end(), CSrsBase::NameEquals<CSrsChip>(name));
      if (chip1 != m_chips.end()) {
         return *chip1; 
      }
   }
   else if (name.empty()) {
      //search by id
      srs_chip_iter chip1 = std::find_if(m_chips.begin(), m_chips.end(), CSrsChip::ChipNoEquals(chip_no));
      if (chip1 != m_chips.end()) {
         return *chip1; 
      }

   }
   else {
      //search by name and id
      srs_chip_iter chip1 = std::find_if(m_chips.begin(), m_chips.end(), 
                                         CSrsBase::NameEquals<CSrsChip>(name));
      srs_chip_iter chip2 = std::find_if(m_chips.begin(), m_chips.end(), 
                                         CSrsChip::ChipNoEquals(chip_no));
      if (chip1 != chip2) {
         std::stringstream ss ;
         ss << "CSrsFec::locate_chip() chip name='" << name << "' and id=" 
         << chip_no << " do not designate same chip or no such chip in FEC " << uid();
         throw std::runtime_error(ss.str().c_str());
      }
      else {
         if (chip1 != m_chips.end()) {
            return *chip1;
         }
      }
   }
   
   return boost::shared_ptr<CSrsChip>();
}


