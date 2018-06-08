/*
  ==============================================================================

    TimePeakEnvelope.cpp
    Created: 7 Jun 2018 11:19:51pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#include "TimePeakEnvelope.h"

TimePeakEnvelope::TimePeakEnvelope()
{
}

TimePeakEnvelope::~TimePeakEnvelope()
{
}

Error_t TimePeakEnvelope::init(float fSampleRateInHz, int iNumChannels, int iBlockLength)
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
    
    m_fAlpha[kAlphaAttack] = 1 - exp(-2.2 / (m_fSampleRateInHz * 0.01));
    m_fAlpha[kAlphaRelease] = 1 - exp(-2.2 / (m_fSampleRateInHz * 1.5));
    m_fFilterBuf = 0.0;
    m_ppfVpTemp = new float*[m_iNumChannels];
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        m_ppfVpTemp[iChannel] = new float[m_iBlockLength];
    }
    
    m_bIsInitialized = true;
    return kNoError;
}

Error_t TimePeakEnvelope::reset()
{
    if (!m_bIsInitialized)
    {
        return kNotInitializedError;
    }
    
    m_fAlpha[kAlphaAttack] = 0.0;
    m_fAlpha[kAlphaRelease] = 0.0;
    m_fFilterBuf = 0.0;
    for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
    {
        delete [] m_ppfVpTemp[iChannel];
    }
    delete [] m_ppfVpTemp;
    m_ppfVpTemp = nullptr;
    
    m_fSampleRateInHz = 0.0;
    m_iNumChannels = 0;
    m_iBlockLength = 0;
    
    m_bIsInitialized = false;
    return kNoError;
}

Error_t TimePeakEnvelope::process(float **ppfInputBuffer, float **ppfOutputBuffer)
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
    
    return kNoError;
}
