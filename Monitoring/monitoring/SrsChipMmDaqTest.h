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


class TFile;
class TTree;

namespace online {
   namespace display {

      class CDaqServerConfig;

      
      class CSrsChipMmDaqTest : public CSrsChip
      {
         
      public:
         CSrsChipMmDaqTest(const CSrsChipId& chip_id, const std::string& name);
         virtual ~CSrsChipMmDaqTest();
         

      };
   }
} // namespace

#endif
