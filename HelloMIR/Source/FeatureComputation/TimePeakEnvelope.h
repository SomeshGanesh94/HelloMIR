/*
  ==============================================================================

    TimePeakEnvelope.h
    Created: 7 Jun 2018 11:19:51pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once
#include "AbstractFeature.h"

class TimePeakEnvelope: public AbstractFeature
{
public:
    
    TimePeakEnvelope();
    ~TimePeakEnvelope();
    
    Error_t init(float fSampleRateInHz, int iNumChannels, int iBlockLength);
    Error_t reset();
    Error_t process(float **ppfInputBuffer, float **ppfOutputBuffer);
    
private:
    
    enum eAlphaType
    {
        kAlphaAttack,
        kAlphaRelease,
        
        kNumAlphaTypes
    };
    
    float m_fAlpha[kNumAlphaTypes];
    float m_fFilterBuf;
    float **m_ppfVpTemp;
};
