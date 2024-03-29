

#ifndef online_display_SrsChipBnl_h
#define online_display_SrsChipBnl_h
#include "SrsChip.h"

class TFile;
class TTree;

namespace online {
   namespace display {
      

      class CSrsChipBnl : public CSrsChip
      {
         
      public:
         CSrsChipBnl(const CSrsChipId& chip_id, const std::string& name);
         virtual ~CSrsChipBnl();



      };
   }
} // namespace

#endif
