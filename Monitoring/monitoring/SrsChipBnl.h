

#ifndef online_display_SrsChipBnl_h
#define online_display_SrsChipBnl_h
#include "SrsChip.h"

class TFile;
class TTree;

namespace online {
   namespace display {
      
      
      struct SBnlPedestal {
         SBnlPedestal() : channel(0), offset(0.0) {}
         SBnlPedestal(short ch, double off) : channel(ch), offset(off) {}
         short channel;
         double offset;
      };
      typedef std::vector<SBnlPedestal> BnlPedestalVect;

      
      class CSrsChipBnl : public CSrsChip
      {
         
      public:
         CSrsChipBnl(const CSrsChipId& chip_id, const std::string& name);
         virtual ~CSrsChipBnl();
         virtual bool check_equipment_key(uint32_t eqkey);


      protected:
         BnlPedestalVect m_pedestals;


      };
   }
} // namespace

#endif
