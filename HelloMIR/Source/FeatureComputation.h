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

struct FeatureValues
{
    FeatureValues()
    {
        pfTimeRms = new float;
        pfTimeStd = new float;
        pfTimeZcr = new float;
    }
    
    ~FeatureValues()
    {
        delete pfTimeRms;
        pfTimeRms = nullptr;
        
        delete pfTimeStd;
        pfTimeStd = nullptr;
        
        delete pfTimeZcr;
        pfTimeZcr = nullptr;
    }
    
    float* pfTimeRms;
    float* pfTimeStd;
    float* pfTimeZcr;
};


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
        
        
        kNumFeatures
    };
    
    float computeFeature(eFeatureName featureName, float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    
private:
    
    bool isParamInRange(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    
    void computeTimeRms(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    void computeTimeStd(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    void computeTimeZcr(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength);
    
    FeatureValues* m_pSFeatureValues;
};
