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
    
    FeatureComputation(int iNumChannels, float fSampleRateInHz, int iBlockLength);
    ~FeatureComputation();
    
    enum eFeatureName
    {
        kTimeRms,
        kTimeStd,
        kTimeZcr,
        kTimePeakEnvelope,
        kTimeAutoCorrelation,
        
        kNumFeatures
    };
    
    void computeFeature(eFeatureName featureName, float **ppfInputBuffer, float **ppfOutputBuffer);
    
private:
    
    bool isParamInRange(float **ppfInputBuffer, float **ppfOutputBuffer);
    
    void computeTimeRms(float **ppfInputBuffer, float **ppfOutputBuffer);
    void computeTimeStd(float **ppfInputBuffer, float **ppfOutputBuffer);
    void computeTimeZcr(float **ppfInputBuffer, float **ppfOutputBuffer);
    void computeTimePeakEnvelope(float **ppfInputBuffer, float **ppfOutputBuffer);
    void computeTimeAutoCorrelation(float **ppfInputBuffer, float **ppfOutputBuffer);
    
    eFeatureName m_eCurrentFeatureName;
    int m_iNumChannels;
    int m_iBlockLength;
    float m_fSampleRateInHz;
    
    //============================================================================================
    /* Private helper functions */
    
    /* Feature specific variables */
    
    /* TimeRms */
    float m_fEpsilon;
    
    /* TimePeakEnvelope */
    enum eAlphaType
    {
        kAlphaAttack,
        kAlphaRelease,
        
        kNumAlphaTypes
    };
    float m_fAlpha[kNumAlphaTypes];
    float m_fFilterBuf;
    float **m_ppfVpTemp;
};
