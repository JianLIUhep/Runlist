// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

/// \file TestCTPScalers.C
/// \brief create CTP scalers, test it and add to database
/// \author Roman Lietava
#if !defined(__CLING__) || defined(__ROOTCLING__)

#include <fairlogger/Logger.h>
#include "CCDB/CcdbApi.h"
#include "CCDB/BasicCCDBManager.h"
#include "DataFormatsCTP/Scalers.h"
#include "DataFormatsCTP/Configuration.h"
#include <string>
#include <map>
#include <iostream>
#endif
using namespace o2::ctp;
void GetScalers(std::string srun, long time, std::string ccdbHost = "http://alice-ccdb.cern.ch")
{
  std::map<std::string, std::string> metadata;
  metadata["runNumber"] = srun;
  // auto hd = cdb.retrieveHeaders("RCT/Info/RunInformation", {}, runNumber);
  // auto hd = cdb.retrieveHeaders("RCT/Info/RunInformation", metadata);
  // std::cout << stol(hd["SOR"]) << "\n";
  CTPConfiguration ctpcfg;
  CTPRunScalers scl;
  CTPRunManager mng;
  mng.setCCDBHost(ccdbHost);
  bool ok;
  scl = mng.getScalersFromCCDB(time, srun, ok);
  if (ok == 1) {
    scl.convertRawToO2();
    scl.printO2(std::cout);
    scl.printFromZero(std::cout);
    scl.printIntegrals();
    ctpcfg = mng.getConfigFromCCDB(time, srun);
    scl.printRates();
    //  std::vector<int> clsses;
    //  clsses = ctpcfg.getTriggerClassList();
    //  std::cout << clsses.size() << std::endl;
    //  for(auto const& i : clsses) std::cout << i << std::endl;
  } else {
    std::cout << "Can not find run, please, check parameters" << std::endl;
  }
}
