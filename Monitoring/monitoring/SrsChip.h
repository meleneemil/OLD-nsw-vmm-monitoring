//
//  SrsChip.h
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 23.5.12.
//  Copyright 2012 CERN - PH/ADE. All rights reserved.
//

#ifndef online_display_SrsChip_h
#define online_display_SrsChip_h

#include "SrsTypes.h"
#include "SrsChipId.h"
#include "SrsBase.h"
#include "SrsEventId.h"
#include "EventTypes.h"


#include <map>
#include <vector>
#include <iostream>
#include <functional>
#include <utility>
#include <string>

#ifndef Q_MOC_RUN
#include <boost/thread/mutex.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#endif

#include <stdlib.h>

#include <TCanvas.h>
#include <TRandom.h>
#include <TVirtualX.h>
#include <TSystem.h>
#include <TStyle.h>
#include <TApplication.h>
#include <TFormula.h>
#include <TF1.h>
#include <TH1.h>
#include <TH2.h>
#include <TFrame.h>
#include <TTimer.h>

#include <QTreeWidgetItem>

class TFile;
class TTree;



namespace online {
   namespace display {
      
   class CSrsChannelId;
   class CSrsChannelData;
   class CEventBuilderInputBuffer;
   //class CRootTreeFiller;
   //class CRootWriter;
   class CDetConnector;
   class CDetStripId;



   /**
    srs chip base, a chip should know how to process incoming data :

    */
   class CSrsChip : public CSrsBase, public boost::enable_shared_from_this<CSrsChip>
         {



         public:

            typedef std::pair<CSrsChannelId, CDetStripId> ChannelStripPair;



            explicit CSrsChip(const CSrsChipId& chip_id, const std::string& name);
            virtual ~CSrsChip();

            friend std::ostream& operator<< (std::ostream& out, const CSrsChip& chip);

            virtual void reset();
            virtual size_t uid() const;
            virtual bool check_equipment_key(uint32_t eqkey) = 0;
            virtual void process_event( SrsChannelList& ) { };
            /// get correct root tree filler for the chip type





            CSrsChipId get_chip_id() const { return m_chip_id;}
            void set_chip_id_to_fec(size_t fec_id);



            std::string to_string() const { return m_chip_id.get_string(); }

            void calculate_channel_qt(SrsChannelList& channels);

            size_t total_number_channels();

            void connect_to_connector(boost::shared_ptr<CDetConnector> conn);

            class ChipNoEquals;

            friend class CDaqServerMonitor;


            bool get_event_data(const EBEventIdType& event_id, CSrsEventChannels& channels);

             boost::shared_ptr<CDetConnector> connector() { return m_connector;}


            void set_channel_strip_map(std::vector<ChannelStripPair>& ccmap);

      TH1D* getRawHisto();
      TH1D *getChipStatistcsHisto();
      TH1D *getChipChargeStatistcsHisto();
      TH1D *getChipTimeStatistcsHisto();


      std::vector <TH1D*> chip1dHistos;
      std::vector <TH2D*> chip2dHistos;

      void fill_histogram(std::vector <float> *fill_values_x, std::vector <float> *fill_values_y);
      void clear_histogram();


   protected:

      void move_received_event_channels(const CSrsEventId& srs_event_id, SrsChannelList& channels);

      CSrsChipId m_chip_id;

      SrsEventChannelsMap m_event_channels_flatmap;

      ///locks access to m_event_channels
      boost::mutex m_chip_mutex;

      boost::shared_ptr<CDetConnector> m_connector;


      std::vector<ChannelStripPair> m_channel_strip_map;



      TH1D* m_chip_raw_histo;
      TH1D* m_chip_statistics_histo;
      TH1D* m_chip_charge_statistics_histo;
      TH1D* m_chip_time_statistics_histo;


      std::vector <TH1D*> chipStatisticsHistos;
      std::vector <TH2D*> chipEventHistos;



   };


   class CSrsChip::ChipNoEquals : public std::unary_function<SrsChipPtr, bool> {
      uint32_t chipno_;
   public:
      ChipNoEquals(uint32_t chip_no) : chipno_(chip_no) {}
      bool operator() (const SrsChipPtr& chip) const {
         return chipno_ == chip->get_chip_id().chip_no();
      }
   };

   std::ostream& operator<< (std::ostream& out, const CSrsChip& chip);


   }
} // namespace

#endif


