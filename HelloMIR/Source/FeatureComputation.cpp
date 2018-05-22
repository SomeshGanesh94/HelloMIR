/*
  ==============================================================================

    FeatureComputation.cpp
    Created: 20 May 2018 4:13:14pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#include "FeatureComputation.h"



FeatureComputation::FeatureComputation(int iNumChannels, float fSampleRateInHz, int iBlockLength): m_iNumChannels(iNumChannels), m_iBlockLength(iBlockLength), m_fSampleRateInHz(fSampleRateInHz) 
{
    m_eCurrentFeatureName = kNumFeatures;
    
    /* TimeRms */
    m_fEpsilon = 1e-5;
    
    /* TimePeakEnvelope */
    m_fAlpha[kAlphaAttack] = 1 - exp(-2.2 / (m_fSampleRateInHz * 0.01));
    m_fAlpha[kAlphaRelease] = 1 - exp(-2.2 / (m_fSampleRateInHz * 1.5));
    m_fFilterBuf = 0.0;
    m_ppfVpTemp = new float*[m_iNumChannels];
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        m_ppfVpTemp[iChannel] = new float[m_iBlockLength];
    }
}

FeatureComputation::~FeatureComputation()
{
    /* TimeRms */
    m_fEpsilon = 0;
    
    /* TimePeakEnvelope */
    m_fAlpha[kAlphaAttack] = 0.0;
    m_fAlpha[kAlphaRelease] = 0.0;
    m_fFilterBuf = 0.0;
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        delete [] m_ppfVpTemp[iChannel];
    }
    delete [] m_ppfVpTemp;
    m_ppfVpTemp = nullptr;
    
    /* General */
    m_eCurrentFeatureName = kNumFeatures;
    m_iNumChannels = 0;
    m_fSampleRateInHz = 0.0;
    m_iBlockLength = 0;
}

/* Choose and compute feature */
void FeatureComputation::computeFeature(FeatureComputation::eFeatureName featureName, float **ppfInputBuffer, float **ppfOutputBuffer)
{
    if (isParamInRange(ppfInputBuffer, ppfOutputBuffer))
    {
        m_eCurrentFeatureName = featureName;
        switch (featureName)
        {
            case kTimeRms:
                computeTimeRms(ppfInputBuffer, ppfOutputBuffer);
                break;
            
            case kTimeStd:
                computeTimeStd(ppfInputBuffer, ppfOutputBuffer);
                break;
                
            case kTimeZcr:
                computeTimeZcr(ppfInputBuffer, ppfOutputBuffer);
                break;
                
            case kTimePeakEnvelope:
                computeTimePeakEnvelope(ppfInputBuffer, ppfOutputBuffer);
                
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
bool FeatureComputation::isParamInRange(float **ppfInputBuffer, float **ppfOutputBuffer)
{
    if (ppfInputBuffer == nullptr || ppfOutputBuffer == nullptr || m_fSampleRateInHz < 1 || m_iBlockLength < 1)
    {
        return false;
    }
    else
    {
        return true;
    }
}

/* Compute time domain root mean square */
void FeatureComputation::computeTimeRms(float **ppfInputBuffer, float **ppfOutputBuffer)
{
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        float fSquareSum = 0.0;
        for (int iSample=0; iSample<m_iBlockLength; iSample++)
        {
            fSquareSum += pow(ppfInputBuffer[iChannel][iSample], 2);
        }
        
        float fRms = sqrt(fSquareSum / float(m_iBlockLength));
        
        /* Convert to dB */
        if (fRms < m_fEpsilon)
        {
            fRms = m_fEpsilon;
        }
        float fRmsInDB = 20.0 * log10(fRms);
        
        ppfOutputBuffer[iChannel][0] = fRmsInDB;
    }
}

/* Compute time domain standard deviation*/
void FeatureComputation::computeTimeStd(float **ppfInputBuffer, float **ppfOutputBuffer)
{
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        /* Compute mean */
        float fMean = 0.0;
        for (int iSample=0; iSample<m_iBlockLength; iSample++)
        {
            fMean += ppfInputBuffer[iChannel][iSample];
        }
        fMean /= float(m_iBlockLength);
        
        /* Compute std */
        float fStd = 0.0;
        for (int iSample=0; iSample<m_iBlockLength; iSample++)
        {
            fStd += pow((ppfInputBuffer[iChannel][iSample] - fMean), 2);
        }
        fStd /= m_iBlockLength;
        fStd = sqrt(fStd);
        
        ppfOutputBuffer[iChannel][0] = fStd;
    }
}

/* Compute time domain zero crossing rate */
void FeatureComputation::computeTimeZcr(float **ppfInputBuffer, float **ppfOutputBuffer)
{
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        float fZcr = 0.0;
        for (int iSample=1; iSample<m_iBlockLength; iSample++)
        {
            if (ppfInputBuffer[iChannel][iSample] * ppfInputBuffer[iChannel][iSample-1] < 0)
            {
                fZcr += 1.0;
            }
        }
        fZcr /= float(m_iBlockLength - 1);
        
        ppfOutputBuffer[iChannel][0] = fZcr;
    }
}

/* Compute two time domain peak envelope measures */
void FeatureComputation::computeTimePeakEnvelope(float **ppfInputBuffer, float **ppfOutputBuffer)
{
    int iHopLength = m_iBlockLength;
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        m_fFilterBuf = m_ppfVpTemp[iChannel][iHopLength-1];
        float fMaxValue0 = 0.0;
        float fMaxValue1 = 0.0;
        for (int iSample=0; iSample<m_iBlockLength; iSample++)
        {
            if (fMaxValue0 < ppfInputBuffer[iChannel][iSample])
            {
                fMaxValue0 = ppfInputBuffer[iChannel][iSample];
            }
            
            if (m_fFilterBuf > abs(ppfInputBuffer[iChannel][iSample]))
            {
                m_ppfVpTemp[iChannel][iSample] = (1 - m_fAlpha[kAlphaRelease]) * m_fFilterBuf;
            }
            else
            {
                m_ppfVpTemp[iChannel][iSample] = m_fAlpha[kAlphaAttack] * abs(ppfInputBuffer[iChannel][iSample]) + (1 - m_fAlpha[kAlphaAttack]) * m_fFilterBuf;
            }
            m_fFilterBuf = m_ppfVpTemp[iChannel][iSample];
            
            if (fMaxValue1 < m_ppfVpTemp[iChannel][iSample])
            {
                fMaxValue1 = m_ppfVpTemp[iChannel][iSample];
            }
        }
        ppfOutputBuffer[iChannel][0] = fMaxValue0;
        ppfOutputBuffer[iChannel][1] = fMaxValue1;
    }
}
