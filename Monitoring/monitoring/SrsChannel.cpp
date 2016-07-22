//
//  SrsChannel.cpp
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 23.5.12.
//  Copyright (c) 2012 CERN - PH/ADE. All rights reserved.
//

#include "SrsChannel.h"
#include "SrsTypes.h"
#include <iostream>

using namespace online::display;

CSrsChannel::CSrsChannel(const CSrsChannelId& channel_id) :
m_channel_id(channel_id),
m_channel_data(),
m_suppressed(false)
{
   
}

CSrsChannel::CSrsChannel(const CSrsChannelId& channel_id, const CSrsChannelData& data) :
m_channel_id(channel_id),
m_channel_data(data),
m_suppressed(false)
{
   
}

CSrsChannel::~CSrsChannel()
{
   
}

double CSrsChannel::calculate_channel_pedestal()
{
   

}
