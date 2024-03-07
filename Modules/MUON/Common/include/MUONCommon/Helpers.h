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

#ifndef QC_MODULE_MUON_COMMON_HELPERS_H
#define QC_MODULE_MUON_COMMON_HELPERS_H

#include "QualityControl/CustomParameters.h"
#include <gsl/span>

class TH1;
class TLine;

namespace o2::quality_control_modules::muon
{
template <class T>
T getConfigurationParameter(o2::quality_control::core::CustomParameters customParameters, std::string parName, const T defaultValue)
{
  T result = defaultValue;
  auto parOpt = customParameters.atOptional(parName);
  if (parOpt.has_value()) {
    std::stringstream ss(parOpt.value());
    ss >> result;
  }
  return result;
}

template <class T>
T getConfigurationParameter(o2::quality_control::core::CustomParameters customParameters, std::string parName, const T defaultValue, const o2::quality_control::core::Activity& activity)
{
  auto parOpt = customParameters.atOptional(parName, activity);
  if (parOpt.has_value()) {
    T result;
    std::stringstream ss(parOpt.value());
    ss >> result;
    return result;
  }
  return getConfigurationParameter<T>(customParameters, parName, defaultValue);
}

TLine* addHorizontalLine(TH1& histo, double y,
                         int lineColor = 1, int lineStyle = 10,
                         int lineWidth = 1);
TLine* addVerticalLine(TH1& histo, double x,
                       int lineColor = 1, int lineStyle = 10,
                       int lineWidth = 1);
void cleanup(TH1& histo, const char* classname);
void markBunchCrossing(TH1& histo,
                       gsl::span<int> bunchCrossings);

} // namespace o2::quality_control_modules::muon

#endif
