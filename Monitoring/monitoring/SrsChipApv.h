//
//  SrsChipApv.h
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 18/06/2012.
//  Copyright 2012 CERN - PH/ADE. All rights reserved.
//

#ifndef online_display_SrsChipApv_h
#define online_display_SrsChipApv_h

#include "SrsChip.h"
#include "SrsTypes.h"



#include <map>
#include <vector>
#include <functional>

class TFile;


namespace online {
   namespace display {
      

      class CSrsChipApv : public  CSrsChip
      {
      public:
         
         typedef std::map<uint32_t, std::vector <uint32_t> > ApvCrosstalkMapType;
         
      public:
         CSrsChipApv(const CSrsChipId& chip_id, const std::string& name);
         virtual ~CSrsChipApv();
         
         virtual bool check_equipment_key(uint32_t eqkey); 
         
         virtual void process_event(SrsChannelList& channels);

         /// process udp data -raw format
         void process_event_raw(SrsChannelList& channels);
         
         /// process udp data - zero suppression on FEC format
         void process_event_zs(SrsChannelList& channels);

         
         //apv specific
         static double ApvZsThreshold;
         static double ApvTimeBinDurationNanoSec;
         static void set_zero_suppression_threshold(double threshold_factor);

         
         
         //TODO: xtalk
         //TODO: define somewhere and load ( det config?):
         static ApvCrosstalkMapType ApvCrosstalkMap;
         static void set_crosstalk_map(const ApvCrosstalkMapType& xtalkmap);
         static void clear_crosstalk_map();

         void set_peak_mode(bool enable);
         bool get_peak_mode() const;
         
      protected:
         void correct_apv_crosstalk(SrsChannelList& channels);
         

         bool m_data_in_peak_mode;
      };
   }
} // namespace

#endif

