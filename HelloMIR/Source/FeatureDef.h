/*
  ==============================================================================

    FeatureDef.h
    Created: 3 Jun 2018 1:53:52am
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once
#include <iostream>

#include "../JuceLibraryCode/JuceHeader.h"

enum Feature_t
{
    kTimeRms,
    kTimeStd,
    kTimeZcr,
    kTimePeakEnvelope,
    kTimeAutoCorrelation,
    
    kNumFeatures
};

const StringArray saFeatures = {"Time domain RMS",
                                "Time domain STD",
                                "Time domain ZCR",
                                "Time domain peak envelope",
                                "Time domain auto correlation"};
