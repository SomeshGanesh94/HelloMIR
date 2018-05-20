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

/* Choose and compute feature */
float FeatureComputation::computeFeature(FeatureComputation::eFeatureName featureName, float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
{
    switch (featureName)
    {
        case kTimeRms:
            return computeTimeRms(pfInputBuffer, fSampleRateInHz, iBlockLength);
        
        case kTimeStd:
            return computeTimeStd(pfInputBuffer, fSampleRateInHz, iBlockLength);
            
        case kTimeZcr:
            return computeTimeZcr(pfInputBuffer, fSampleRateInHz, iBlockLength);
            
        default:
            return 0.0f;
    }
}

/* Compute time domain root mean square */
float FeatureComputation::computeTimeRms(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
{
    float fSquareSum = 0.0;
    for (int iSample=0; iSample<iBlockLength; iSample++)
    {
        fSquareSum += pow(pfInputBuffer[iSample], 2);
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

/* Compute time domain standard deviation*/
float FeatureComputation::computeTimeStd(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
{
    /* Compute mean */
    float fMean = 0.0;
    for (int iSample=0; iSample<iBlockLength; iSample++)
    {
        fMean += pfInputBuffer[iSample];
    }
    fMean /= float(iBlockLength);
    
    /* Compute std */
    float fStd = 0.0;
    for (int iSample=0; iSample<iBlockLength; iSample++)
    {
        fStd += pow((pfInputBuffer[iSample] - fMean), 2);
    }
    fStd /= iBlockLength;
    fStd = sqrt(fStd);
    
    return fStd;
}

/* Compute time domain zero crossing rate */
float FeatureComputation::computeTimeZcr(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
{
    float fZcr = 0.0;
    for (int iSample=1; iSample<iBlockLength; iSample++)
    {
        if (pfInputBuffer[iSample] * pfInputBuffer[iSample-1] < 0)
        {
            fZcr += 1.0;
        }
    }
    fZcr /= float(iBlockLength - 1);
    
    return fZcr;
}
