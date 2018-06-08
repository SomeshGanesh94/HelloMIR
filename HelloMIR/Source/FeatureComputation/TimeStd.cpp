/*
  ==============================================================================

    TimeStd.cpp
    Created: 7 Jun 2018 10:37:14pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#include "TimeStd.h"

TimeStd::TimeStd()
{
}

TimeStd::~TimeStd()
{
}

Error_t TimeStd::init(float fSampleRateInHz, int iNumChannels, int iBlockLength)
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
    
    m_bIsInitialized = true;
    return kNoError;
}

Error_t TimeStd::reset()
{
    if (!m_bIsInitialized)
    {
        return kNotInitializedError;
    }
    
    m_fSampleRateInHz = 0.0;
    m_iNumChannels = 0;
    m_iBlockLength = 0;
    
    m_bIsInitialized = false;
    return kNoError;
}

Error_t TimeStd::process(float **ppfInputBuffer, float **ppfOutputBuffer)
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
    
    return kNoError;
}
