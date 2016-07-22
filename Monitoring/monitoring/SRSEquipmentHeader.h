

#ifndef online_display_SRSEquipmentHeader_h
#define online_display_SRSEquipmentHeader_h

#include "SrsTypes.h"

#ifndef Q_MOC_RUN

#include <boost/bind.hpp>
#endif


#include <iostream>
#include <iomanip>
#include <vector>
#include <stdint.h>

namespace online {
   namespace display {

      typedef std::pair<uint32_t, bool> SRSEquipmentKey;
      

      struct SRSEqSizeKey : public std::unary_function<uint32_t, bool>
      {
         bool operator() (uint32_t word) {
            return ((word >> 16 ) & 0xFFFF) == 0xAABB;
         }
      };  

   }
} // namespace

#endif
