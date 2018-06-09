/*
  ==============================================================================

    TimeAcfCoeff.cpp
    Created: 8 Jun 2018 4:13:34pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#include "TimeAcfCoeff.h"

TimeAcfCoeff::TimeAcfCoeff()
{
}

TimeAcfCoeff::~TimeAcfCoeff()
{
}

Error_t TimeAcfCoeff::init(float fSampleRateInHz, int iNumChannels, int iBlockLength)
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
    
    m_iNumCoeff = 1;
    
    m_bNormalize = false;
    m_fNormCoeff = 0.0;
    
    m_bIsInitialized = true;
    return kNoError;
}

Error_t TimeAcfCoeff::reset()
{
    if (!m_bIsInitialized)
    {
        return kNotInitializedError;
    }
    
    m_iNumCoeff = 1;
    
    m_fSampleRateInHz = 0.0;
    m_iNumChannels = 0;
    m_iBlockLength = 0;
    
    m_bNormalize = false;
    m_fNormCoeff = 0.0;
    
    m_bIsInitialized = false;
    return kNoError;
}

Error_t TimeAcfCoeff::process(float **ppfInputBuffer, float **ppfOutputBuffer)
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
        if (m_bNormalize)
        {
            m_fNormCoeff = 0;
            for (int iSample=0; iSample<m_iBlockLength; iSample++)
            {
                m_fNormCoeff += pow(ppfInputBuffer[iChannel][iSample], 2);
            }
        }
        for (int iLag=1; iLag<=m_iNumCoeff; iLag++)
        {
            float fSum = 0;
            for (int iSample=0; iSample<m_iBlockLength-iLag; iSample++)
            {
                fSum += ppfInputBuffer[iChannel][iSample] * ppfInputBuffer[iChannel][iSample+iLag];
            }
            if (m_bNormalize)
            {
                ppfOutputBuffer[iChannel][iLag-1] = fSum / m_fNormCoeff;
            }
            else
            {
                ppfOutputBuffer[iChannel][iLag-1] = fSum;
            }
        }
    }
    return kNoError;
}

Error_t TimeAcfCoeff::setNumCoeff(int iNumCoeff)
{
    if (iNumCoeff <= 0)
    {
        return kFunctionInvalidArgsError;
    }
    
    m_iNumCoeff = iNumCoeff;
    return kNoError;
}

int TimeAcfCoeff::getNumCoeff()
{
    return m_iNumCoeff;
}

Error_t TimeAcfCoeff::setNormalize(bool bValue)
{
    m_bNormalize = bValue;
    return kNoError;
}

bool TimeAcfCoeff::isNormalized()
{
    return m_bNormalize;
}
