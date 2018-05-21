/*
  ==============================================================================

    FeatureComputation.cpp
    Created: 20 May 2018 4:13:14pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#include "FeatureComputation.h"



FeatureComputation::FeatureComputation(int iNumChannels): m_iNumChannels(iNumChannels)
{
    m_eCurrentFeatureName = kNumFeatures;
}

FeatureComputation::~FeatureComputation()
{
    m_eCurrentFeatureName = kNumFeatures;
    m_iNumChannels = 0;
}

/* Choose and compute feature */
void FeatureComputation::computeFeature(FeatureComputation::eFeatureName featureName, float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength)
{
    if (isParamInRange(ppfInputBuffer, ppfOutputBuffer, fSampleRateInHz, iBlockLength))
    {
        m_eCurrentFeatureName = featureName;
        switch (featureName)
        {
            case kTimeRms:
                computeTimeRms(ppfInputBuffer, ppfOutputBuffer, fSampleRateInHz, iBlockLength);
                break;
            
            case kTimeStd:
                computeTimeStd(ppfInputBuffer, ppfOutputBuffer, fSampleRateInHz, iBlockLength);
                break;
                
            case kTimeZcr:
                computeTimeZcr(ppfInputBuffer, ppfOutputBuffer, fSampleRateInHz, iBlockLength);
                break;
                
            default:
                break;
        }
    }
    else
    {
        return;
    }
}

/* Check if input parameters for feature computation are valid/in range */
bool FeatureComputation::isParamInRange(float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength)
{
    if (ppfInputBuffer == nullptr || ppfOutputBuffer == nullptr || fSampleRateInHz < 1 || iBlockLength < 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Compute time domain root mean square */
void FeatureComputation::computeTimeRms(float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength)
{
    float fEpsilon = 1e-5;
    
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        float fSquareSum = 0.0;
        for (int iSample=0; iSample<iBlockLength; iSample++)
        {
            fSquareSum += pow(ppfInputBuffer[iChannel][iSample], 2);
        }
        
        float fRms = sqrt(fSquareSum / float(iBlockLength));
        
        /* Convert to dB */
        if (fRms < fEpsilon)
        {
            fRms = fEpsilon;
        }
        float fRmsInDB = 20.0 * log10(fRms);
        
        ppfOutputBuffer[iChannel][0] = fRmsInDB;
    }
}

/* Compute time domain standard deviation*/
void FeatureComputation::computeTimeStd(float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength)
{
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        /* Compute mean */
        float fMean = 0.0;
        for (int iSample=0; iSample<iBlockLength; iSample++)
        {
            fMean += ppfInputBuffer[iChannel][iSample];
        }
        fMean /= float(iBlockLength);
        
        /* Compute std */
        float fStd = 0.0;
        for (int iSample=0; iSample<iBlockLength; iSample++)
        {
            fStd += pow((ppfInputBuffer[iChannel][iSample] - fMean), 2);
        }
        fStd /= iBlockLength;
        fStd = sqrt(fStd);
        
        ppfOutputBuffer[iChannel][0] = fStd;
    }
}

/* Compute time domain zero crossing rate */
void FeatureComputation::computeTimeZcr(float **ppfInputBuffer, float **ppfOutputBuffer, float fSampleRateInHz, int iBlockLength)
{
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        float fZcr = 0.0;
        for (int iSample=1; iSample<iBlockLength; iSample++)
        {
            if (ppfInputBuffer[iChannel][iSample] * ppfInputBuffer[iChannel][iSample-1] < 0)
            {
                fZcr += 1.0;
            }
        }
        fZcr /= float(iBlockLength - 1);
        
        ppfOutputBuffer[iChannel][0] = fZcr;
    }
}

