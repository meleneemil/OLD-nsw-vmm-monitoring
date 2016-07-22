//
//  SrsChip.cpp
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 23.5.12.
//  Copyright (c) 2012 CERN - PH/ADE. All rights reserved.
//

#include "SrsChip.h"
#include "SrsChannel.h"
//#include "EventBuilderInputBuffer.h"
#include "SrsEventChannels.h"
#include "DetConnector.h"
#include "mainwindow.cpp"

//#include "RootTreeFiller.h"
//#include <TFile.h>

#include <boost/bind.hpp>
//#include <boost/foreach.hpp>
#include <boost/thread.hpp>

#include <iostream>
#include <vector>
#include <string.h>

using namespace online::display;

CSrsChip::CSrsChip(const CSrsChipId& chip_id, const std::string& name) :
CSrsBase(chip_id.chip_id(), name),
m_chip_id(chip_id),
//m_event_channels(),
m_event_channels_flatmap(),
m_chip_mutex(),
m_connector(),
m_channel_strip_map(),
m_chip_raw_histo(new TH1D(name.c_str(),name.c_str(),4000,0,4000)),
  m_chip_statistics_histo(new TH1D(std::string("Statistics_"+name).c_str(),std::string("Statistics_"+name).c_str(),620,0,620)),
  m_chip_charge_statistics_histo(new TH1D(std::string("Charge_"+name).c_str(),std::string("Charge_"+name).c_str(),400,0,2000)),
  m_chip_time_statistics_histo(new TH1D(std::string("Time_"+name).c_str(),std::string("Time_"+name).c_str(),400,0,800))
{


    m_chip_raw_histo->SetLineColor(kGreen+4);
    m_chip_raw_histo->SetTitleSize(0.04);

    m_chip_statistics_histo->SetLineColor(38);
    m_chip_statistics_histo->SetFillColor(38);
    m_chip_statistics_histo->SetTitleSize(0.04);
    m_chip_statistics_histo->GetXaxis()->SetLabelSize(0.06);

    m_chip_charge_statistics_histo->SetLineColor(46);
    m_chip_charge_statistics_histo->SetFillColor(46);
    m_chip_charge_statistics_histo->GetXaxis()->SetLabelSize(0.06);
    m_chip_charge_statistics_histo->SetTitleSize(0.04);

    m_chip_time_statistics_histo->SetLineColor(8);
    m_chip_time_statistics_histo->SetFillColor(8);
    m_chip_time_statistics_histo->GetXaxis()->SetLabelSize(0.06);
    m_chip_time_statistics_histo->SetTitleSize(0.04);


    chip1dHistos.push_back(m_chip_statistics_histo);
    chip1dHistos.push_back(m_chip_charge_statistics_histo);
    chip1dHistos.push_back(m_chip_time_statistics_histo);
    chip1dHistos.push_back(m_chip_raw_histo);

}

CSrsChip::~CSrsChip()
{

}



std::ostream& online::display::operator<< (std::ostream & out, const CSrsChip & chip)
{
   if (!chip.m_event_channels_flatmap.empty()) {
      SrsEventChannelsPtr evchans = chip.m_event_channels_flatmap.begin()->second;
      Q_FOREACH(SrsChannelPtr chan, evchans->channels()) {
      }
   }
   return out;
}


void CSrsChip::reset()
{
   boost::mutex::scoped_lock lock(m_chip_mutex);
   m_event_channels_flatmap.clear();
   m_connector.reset();
}

size_t CSrsChip::uid() const
{
   return m_chip_id.chip_id();
}

void CSrsChip::set_chip_id_to_fec(size_t fec_id)
{
   boost::mutex::scoped_lock lock(m_chip_mutex);
   m_chip_id = CSrsChipId(fec_id, m_chip_id.chip_no());
}



void CSrsChip::move_received_event_channels(const CSrsEventId& srs_event_id, SrsChannelList& channels)
{
   typedef std::pair<EBEventIdType, SrsEventChannelsPtr> SrsEventChannelsMapType;

   boost::mutex::scoped_lock lock(m_chip_mutex);
   EBEventIdType event_id = srs_event_id.event_assembly_id(AssembleBySrsTimeStamp);

   SrsEventChannelsMap::iterator evtfound = std::find_if(m_event_channels_flatmap.begin(),
                                                      m_event_channels_flatmap.end(),
                                                      FirstComparator<SrsEventChannelsMapType>(event_id));
   if (evtfound == m_event_channels_flatmap.end()) {
      std::cout << "CSrsChip::move_received_event_channels() : in chip " << name() << " eventid="<< event_id << " not found" <<std::endl;

      std::pair<SrsEventChannelsMap::iterator, bool > rc =
      m_event_channels_flatmap.insert(SrsEventChannelsMapType(event_id,
                                                SrsEventChannelsPtr(new CSrsEventChannels(srs_event_id, channels)) ));
      evtfound = rc.first;
   }
   else {
      std::cout << "CSrsChip::move_received_event_channels() in chip "<< name()
      << "moving channels " << channels.size() << std::endl;
       evtfound->second->move_event_channels(channels);
   }


   evtfound->second->process(shared_from_this());
}



/**
 for each channel calculate qmax, and tbqmax as charge and time values
 */
void CSrsChip::calculate_channel_qt(SrsChannelList& channels)
{
   std::for_each(channels.begin(), channels.end(), boost::bind(&CSrsChannel::calculate_qt, _1));
}



size_t CSrsChip::total_number_channels()
{
   typedef std::pair<EBEventIdType, SrsEventChannelsPtr> SrsEventMapPair;
   size_t counter = 0;
   boost::mutex::scoped_lock lock(m_chip_mutex);
   Q_FOREACH(SrsEventMapPair p, m_event_channels_flatmap) {
      if(p.second) {
         counter += p.second->size();
      }

   }
   return counter;
}

void CSrsChip::connect_to_connector(boost::shared_ptr<CDetConnector> conn)
{

   m_connector = conn;

   std::cout << "CSrsChip::connect_to_connector()  chip " << name()
   << " is connected to " << conn->name()  << " on " << (conn->parent().lock()?conn->parent().lock()->name(): "NOT CONNECTED") << std::endl;
}


bool CSrsChip::get_event_data(const EBEventIdType& evid, CSrsEventChannels& channels)
{
   typedef std::pair<EBEventIdType, SrsEventChannelsPtr> SrsEventChannelsMapType;

   SrsEventChannelsMap::iterator evtfound = std::find_if(m_event_channels_flatmap.begin(),
                                                         m_event_channels_flatmap.end(),
                                                         FirstComparator<SrsEventChannelsMapType>(evid));
   if (evtfound != m_event_channels_flatmap.end() && evtfound->second) {
      channels.assign(evtfound->second->channels());
      return true;
   }
   return false;
}

void CSrsChip::set_channel_strip_map(std::vector<ChannelStripPair>& ccmap)
{
   m_channel_strip_map = ccmap;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TH1D *CSrsChip::getRawHisto()
{
    return m_chip_raw_histo;
}

TH1D *CSrsChip::getChipStatistcsHisto()
{
    return m_chip_statistics_histo;
}

TH1D *CSrsChip::getChipChargeStatistcsHisto()
{
    return m_chip_charge_statistics_histo;
}

TH1D *CSrsChip::getChipTimeStatistcsHisto()
{
    return m_chip_time_statistics_histo;
}


