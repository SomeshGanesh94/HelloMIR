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
    
    FeatureComputation(int iNumChannels);
    ~FeatureComputation();
    
    enum eFeatureName
    {
        kTimeRms,
        kTimeStd,
        kTimeZcr,
        kTimePeakEnvelope,
        
        kNumFeatures
    };
    
    void computeFeature(eFeatureName featureName, float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength);
    
private:
    
    bool isParamInRange(float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength);
    
    void computeTimeRms(float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength);
    void computeTimeStd(float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength);
    void computeTimeZcr(float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength);
    void computeTimePeakEnvelope(float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength);
    
    eFeatureName m_eCurrentFeatureName;
    int m_iNumChannels;
};
