/*
  ==============================================================================

    TimeAcfCoeff.h
    Created: 8 Jun 2018 4:13:34pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once
#include "AbstractFeature.h"

class TimeAcfCoeff: public AbstractFeature
{
public:
    
    TimeAcfCoeff();
    ~TimeAcfCoeff();
    
    Error_t init(float fSampleRateInHz, int iNumChannels, int iBlockLength);
    Error_t reset();
    Error_t process(float **ppfInputBuffer, float **ppfOutputBuffer);
    Error_t setNumCoeff(int iNumCoeff);
    int getNumCoeff();
    Error_t setNormalize(bool bValue);
    bool isNormalized();
    
private:
    
    int m_iNumCoeff;
    bool m_bNormalize;
    float m_fNormCoeff;
};
