//
//  PropertyTreeParserSrs.cpp
//  mmdaq3-server
//
//  Created by Marcin Byszewski on 30.5.12.
//  Copyright (c) 2012 CERN - PH/ADE. All rights reserved.
//

#include "PropertyTreeParserSrs.h"
#include "SrsSru.h"
#include "SrsFec.h"
#include "SrsChipId.h"
#include "SrsChipApv.h"
#include "SrsChipBnl.h"
#include "SrsChipMmDaqTest.h"


#include <QObject>


//#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#include <iostream>

namespace bpt = boost::property_tree;

using namespace online::display;

CPropertyTreeParserSrs::CPropertyTreeParserSrs(const boost::property_tree::ptree& ptree, CDaqServerConfig& daqconfig) :
CPropertyTreeParser(ptree, daqconfig),
srs_elements_(),
chip_names_(),
apv25_zero_suppression_threshold_()
{
   
}


CPropertyTreeParserSrs::~CPropertyTreeParserSrs()
{
   
}

const std::vector<SrsBasePtr>& CPropertyTreeParserSrs::make_srs_elements() 
{
   
   Q_FOREACH(const bpt::ptree::value_type &v, ptree_.get_child("srs")) {
      if (v.first == "fec") {
         try {
            SrsBasePtr fec = parse_ptree_srs_node<CSrsFec>(v);
            push_new_srs_element(fec);
         } catch (std::exception& e) {
            std::cout << "---> ERROR creating FEC" << std::endl;
            throw;
         }
      }
      else if (v.first == "<xmlcomment>") {
         //         std::cout << "comment in file: " << v.second.data() << std::endl;
      }
      else if (v.first == "<xmlattr>") {
         //         std::cout << "<xmlattr>=" << v.second.data() << std::endl;
      }
      else {
         std::cout << "WARN: bad data in config: unknown key '" << v.first << "' in <srs> section" << std::endl;
      }
   }
   
   std::cout << "......................................................................." << " check srs" << std::endl;

   
   return srs_elements_;
}


void CPropertyTreeParserSrs::push_new_srs_element(SrsBasePtr elem)
{
   if (std::binary_search(srs_elements_.begin(), srs_elements_.end(), elem, CSrsBase::IdNumberCompare())) {
      throw std::runtime_error("Duplicate SRS id number");
   }
   srs_elements_.push_back(elem);
   std::sort(srs_elements_.begin(), srs_elements_.end(), CSrsBase::IdNumberCompare());  
}



boost::shared_ptr<CSrsChip> CPropertyTreeParserSrs::parse_ptree_srs_chip_node(const boost::property_tree::ptree::value_type& node)
{
   //make a new chip
   std::string idstr;
   std::string typestr;
   std::string namestr;
   
   Q_FOREACH(const boost::property_tree::ptree::value_type &v, node.second) {      
      if (v.first == "name") {
         namestr = v.second.data();
      }
      else if (v.first == "type") {
         typestr = v.second.data();
      }
      else if (v.first == "<xmlcomment>") {
         //         std::cout << "comment in SRU section: " << v.second.data() << std::endl;
      }
      else if (v.first == "<xmlattr>") {
         idstr = v.second.get<std::string>("id");
         typestr = v.second.get<std::string>("type","");
         //         std::cout << "read id=" << idstr << std::endl;
      }
      else {
         std::cout << "WARN: bad data in config: unknown key '" << v.first 
         << "' in section " << node.first << std::endl;
      }
   }
   
   chip_names_.push_back(namestr);
   
   boost::shared_ptr<CSrsChip> chipptr;
   
   if (typestr == "chip") {
      chipptr.reset(new CSrsChipApv(CSrsChipId(0, id_number_from_string(idstr)), namestr) );   
   }
   else {
      throw std::runtime_error("Unknown SRS chip type");
   }
   
   return chipptr;
   
}

