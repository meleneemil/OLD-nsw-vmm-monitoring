//
//  SrsChipMmDaqTest.cpp
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 14/11/2012.
//  Copyright (c) 2012 CERN - PH/ADE. All rights reserved.
//

#include "SrsChipMmDaqTest.h"
#include "SRSEquipmentHeader.h"


#include <iostream>

using namespace online::display;

CSrsChipMmDaqTest::CSrsChipMmDaqTest(const CSrsChipId& chip_id, const std::string& name) :
CSrsChip(chip_id, name)
{
}


CSrsChipMmDaqTest::~CSrsChipMmDaqTest()
{
   
}

bool CSrsChipMmDaqTest::check_equipment_key(uint32_t eqkey)
{
   return SRSEqHdrKeys::SRSEquipmentMmDaqTest == eqkey;

}




