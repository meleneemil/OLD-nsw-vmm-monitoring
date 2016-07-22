//
//  SrsChipApv.cpp
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 18/06/2012.
//  Copyright (c) 2012 CERN - PH/ADE. All rights reserved.
//

#include "SrsChipApv.h"
#include "SrsChannelApvRaw.h"
//#include "RootTreeFillerApvRaw.h"
//#include "RootWriter.h"
#include "SrsEventChannels.h"
#include "SRSEquipmentHeader.h"
//#include "RootReader.h"

#include <TFile.h>

#include <boost/bind.hpp>
//#include <boost/foreach.hpp>

#include <iostream>
#include <stdexcept>
#include <utility>

using namespace online::display;

double CSrsChipApv::ApvZsThreshold = 1.123;
double CSrsChipApv::ApvTimeBinDurationNanoSec = 25.0;
std::string CSrsChipApv::ApvPedestalFileName = "";
CSrsChipApv::ApvCrosstalkMapType CSrsChipApv::ApvCrosstalkMap = CSrsChipApv::ApvCrosstalkMapType();

//CRootTreeFillerApvRaw* CSrsChipApv::m_root_tree_filler_apvraw = 0;


CSrsChipApv::CSrsChipApv(const CSrsChipId& chip_id, const std::string& name) :
CSrsChip(chip_id, name),
//m_pedestals(),
m_pedestals_map(),
m_data_in_peak_mode(false)
{ }


CSrsChipApv::~CSrsChipApv()
{
   
}
 
bool CSrsChipApv::check_equipment_key(uint32_t eqkey)
{
   return SRSEqHdrKeys::SRSEquipmentApvRaw == eqkey 
   || SRSEqHdrKeys::SRSEquipmentApvZeroSuppressed == eqkey;
}


void CSrsChipApv::set_zero_suppression_threshold(double threshold_factor)
{
   CSrsChipApv::ApvZsThreshold = threshold_factor;
}


void CSrsChipApv::set_pedestal_filename(const std::string& filename)
{
   CSrsChipApv::ApvPedestalFileName = filename;
}

void CSrsChipApv::load_pedestal_file()
{   

}



SApvPedestal CSrsChipApv::get_pedestal(const uint32_t& channel_id) const
{
   ApvPedestalMap::const_iterator found = m_pedestals_map.find(channel_id);
   if (found == m_pedestals_map.end()) {
      return SApvPedestal(0, 0.0, 0.0, 0.0);
   }
   return found->second;

}


void CSrsChipApv::set_pedestal(const uint32_t& channel_id,  const std::pair<double, double>& ped)
{
   m_pedestals_map[channel_id] = SApvPedestal(CSrsChannelId(channel_id).channel_no(), ped.first, ped.second, 0.0);

}


/** 
 clear pedestals and crosstalk definitions
 */
void CSrsChipApv::clear_pedestals()
{
   m_pedestals_map.clear();
}


void CSrsChipApv::set_crosstalk_map(const ApvCrosstalkMapType& xtalkmap)
{
   ApvCrosstalkMap = xtalkmap;
}

void CSrsChipApv::clear_crosstalk_map() 
{
   ApvCrosstalkMap.clear();  
}


void CSrsChipApv::set_peak_mode(bool enable)
{
   m_data_in_peak_mode = enable;
}

bool CSrsChipApv::get_peak_mode() const
{
   return m_data_in_peak_mode;
}

void CSrsChipApv::process_event( SrsChannelList& channels)
{
   
   //should not run for ZS data
   if (m_data_in_peak_mode) {
      process_event_zs(channels);
   } else {
      process_event_raw(channels);
      calculate_channel_qt(channels);
   }
}

void CSrsChipApv::process_event_raw(SrsChannelList& channels)
{
}

void CSrsChipApv::process_event_zs(SrsChannelList& channels)
{
   std::cout << "TODO: implement CSrsChipApv::process_event_zs()" << std::endl;
   
}
