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

/* Class for feature computation */
class FeatureComputation
{
public:
    
    FeatureComputation();
    ~FeatureComputation();
    
    enum eFeatureName
    {
        kTimeRms,
        kTimeStd,
        kTimeZcr,
        kTimePeakEnvelope,
        
        kNumFeatures
    };
    
    float computeFeature(eFeatureName featureName, float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    
private:
    
    bool isParamInRange(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    
    void computeTimeRms(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    void computeTimeStd(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    void computeTimeZcr(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    void computeTimePeakEnvelope(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    
    float* m_pfCurrentFeatureValue;
    eFeatureName m_eCurrentFeatureName;
};
