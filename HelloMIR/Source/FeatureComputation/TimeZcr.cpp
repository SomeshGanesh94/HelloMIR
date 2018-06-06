/*
  ==============================================================================

    TimeZcr.cpp
    Created: 5 Jun 2018 9:15:45pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#include "TimeZcr.h"

TimeZcr::TimeZcr()
{
}

TimeZcr::~TimeZcr()
{
}

Error_t TimeZcr::init(float fSampleRateInHz, int iNumChannels, int iBlockLength)
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

Error_t TimeZcr::reset()
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

Error_t TimeZcr::process(float **ppfInputBuffer, float **ppfOutputBuffer)
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
    
    return kNoError;
}
