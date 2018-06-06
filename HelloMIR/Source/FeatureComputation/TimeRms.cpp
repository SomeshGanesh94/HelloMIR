/*
  ==============================================================================

    TimeRms.cpp
    Created: 3 Jun 2018 1:13:54am
    Author:  Somesh Ganesh

  ==============================================================================
*/

#include "TimeRms.h"

TimeRms::TimeRms()
{
}

TimeRms::~TimeRms()
{
}

Error_t TimeRms::init(float fSampleRateInHz, int iNumChannels, int iBlockLength)
{
    this->reset();
    
    if (fSampleRateInHz <= 0 ||
        iNumChannels    <= 0 ||
        iBlockLength    <= 0)
    {
        return kFunctionInvalidArgsError;
    }
    
    m_fSampleRateInHz = fSampleRateInHz;
    m_iNumChannels = iNumChannels;
    m_iBlockLength = iBlockLength;
    
    m_fEpsilon = 1e-5;
    
    m_bIsInitialized = true;
    return kNoError;
}

Error_t TimeRms::reset()
{
    if (!m_bIsInitialized)
    {
        return kNotInitializedError;
    }
    
    m_fEpsilon = 0.0;
    
    m_fSampleRateInHz = 0.0;
    m_iNumChannels = 0;
    m_iBlockLength = 0;
    
    m_bIsInitialized = false;
    return kNoError;
}

Error_t TimeRms::process(float **ppfInputBuffer, float **ppfOutputBuffer)
{
    if (!m_bIsInitialized)
    {
        return kNotInitializedError;
    }
    
    if (ppfInputBuffer == nullptr ||
        ppfOutputBuffer == nullptr)
    {
        return kFunctionInvalidArgsError;
    }
    
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
    
    return kNoError;
}
