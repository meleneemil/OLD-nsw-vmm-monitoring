//
//  SrsChipMmDaqTest.h
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 14/11/2012.
//  Copyright 2012 CERN - PH/ADE. All rights reserved.
//

#ifndef online_display_SrsChipMmDaqTest_h
#define online_display_SrsChipMmDaqTest_h

#include "SrsChip.h"
//#include "SrsPedestal.h"


class TFile;
class TTree;

namespace online {
   namespace display {
      
      //class CRootTreeFillerMmDaqTest;
      class CDaqServerConfig;

      
      class CSrsChipMmDaqTest : public CSrsChip
      {
         
      public:
         CSrsChipMmDaqTest(const CSrsChipId& chip_id, const std::string& name);
         virtual ~CSrsChipMmDaqTest();
         
         
         virtual bool check_equipment_key(uint32_t eqkey);
         /// get correct root tree filler for the chip type
         ///
         virtual void load_pedestal_file(){};
         
      protected:
         virtual void calculate_pedestals(const CSrsEventId& srs_event_id, SrsChannelList& channels) {};

      };
   }
} // namespace

#endif
