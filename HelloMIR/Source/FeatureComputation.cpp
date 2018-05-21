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
    m_pSFeatureValues = new FeatureValues();
}

FeatureComputation::~FeatureComputation()
{
    delete m_pSFeatureValues;
    m_pSFeatureValues = nullptr;
}

/* Choose and compute feature */
float FeatureComputation::computeFeature(FeatureComputation::eFeatureName featureName, float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
{
    if (isParamInRange(pfInputBuffer, fSampleRateInHz, iBlockLength))
    {
        switch (featureName)
        {
            case kTimeRms:
                computeTimeRms(pfInputBuffer, fSampleRateInHz, iBlockLength);
                return *m_pSFeatureValues->pfTimeRms;
            
            case kTimeStd:
                computeTimeStd(pfInputBuffer, fSampleRateInHz, iBlockLength);
                return *m_pSFeatureValues->pfTimeStd;
                
            case kTimeZcr:
                computeTimeZcr(pfInputBuffer, fSampleRateInHz, iBlockLength);
                return *m_pSFeatureValues->pfTimeZcr;
                
            default:
                return 0.0f;
        }
    }
    else
    {
        return 0.0f;
    }
}

/* Check if input parameters for feature computation are valid/in range */
bool FeatureComputation::isParamInRange(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
{
    if (pfInputBuffer == nullptr || fSampleRateInHz < 1 || iBlockLength < 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Compute time domain root mean square */
void FeatureComputation::computeTimeRms(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
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
    
    m_pSFeatureValues->pfTimeRms[0] = fRmsInDB;
}

/* Compute time domain standard deviation*/
void FeatureComputation::computeTimeStd(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
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
    
    m_pSFeatureValues->pfTimeStd[0] = fStd;
}

/* Compute time domain zero crossing rate */
void FeatureComputation::computeTimeZcr(float *pfInputBuffer, float fSampleRateInHz, int iBlockLength)
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
    
    m_pSFeatureValues->pfTimeZcr[0] = fZcr;
}
