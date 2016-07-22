//
//  SrsChipApv.cpp
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 18/06/2012.
//  Copyright (c) 2012 CERN - PH/ADE. All rights reserved.
//

#include "SrsChipApv.h"
#include "SrsEventChannels.h"

#include <TFile.h>

#include <boost/bind.hpp>

#include <iostream>
#include <stdexcept>
#include <utility>

using namespace online::display;

double CSrsChipApv::ApvZsThreshold = 1.123;
double CSrsChipApv::ApvTimeBinDurationNanoSec = 25.0;
CSrsChipApv::ApvCrosstalkMapType CSrsChipApv::ApvCrosstalkMap = CSrsChipApv::ApvCrosstalkMapType();


CSrsChipApv::CSrsChipApv(const CSrsChipId& chip_id, const std::string& name) :
CSrsChip(chip_id, name),
m_data_in_peak_mode(false)
{ }


CSrsChipApv::~CSrsChipApv()
{
   
}

void CSrsChipApv::set_zero_suppression_threshold(double threshold_factor)
{
   CSrsChipApv::ApvZsThreshold = threshold_factor;
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
