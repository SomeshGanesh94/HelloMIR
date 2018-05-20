/*
  ==============================================================================

    FeatureComputation.cpp
    Created: 20 May 2018 4:13:14pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#include "FeatureComputation.h"

FeatureComputation::FeatureComputation()
{
    
}

FeatureComputation::~FeatureComputation()
{
    
}

float FeatureComputation::computeFeature(FeatureComputation::eFeatureName featureName, float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
{
    switch (featureName)
    {
        case kTimeRms:
            return computeTimeRms(pfInputBuffer, fSampleRateInHz, iBlockLength);
            
        default:
            return 0.0;
    }
}

/* Compute time domain root mean square */
float FeatureComputation::computeTimeRms(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
{
    float fSquareSum = 0.0;
    for (int iSample=0; iSample<iBlockLength; iSample++)
    {
        fSquareSum += pow(pfInputBuffer[iSample],2);
    }
    
    float fRms = sqrt(fSquareSum / float(iBlockLength));
    
    /* Convert to dB */
    float fEpsilon = 1e-5;
    
    if (fRms < fEpsilon)
    {
        fRms = fEpsilon;
    }
    float fRmsInDB = 20.0 * log10(fRms);
    
    return fRmsInDB;
}
