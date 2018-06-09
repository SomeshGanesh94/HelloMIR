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
    kTimeZcr,
    kTimeStd,
    kTimePeakEnvelope,
    kTimeAcfCoeff,
    
    kNumFeatures
};

const StringArray saFeatures = {"Time domain RMS",
                                "Time domain ZCR",
                                "Time domain STD",
                                "Time domain peak envelope",
                                "Time domain acf coefficients"};
