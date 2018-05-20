/*
  ==============================================================================

    FeatureComputation.h
    Created: 20 May 2018 4:13:14pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once
#include <iostream>
#include <math.h>

class FeatureComputation
{
public:
    
    FeatureComputation();
    ~FeatureComputation();
    
    enum eFeatureName
    {
        kTimeRms,
        kTimeStd,
        
        kNumFeatures
    };
    
    float computeFeature(eFeatureName featureName, float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    
private:
    
    float computeTimeRms(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    float computeTimeStd(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
};
