/*
  ==============================================================================

    TimeRms.h
    Created: 3 Jun 2018 1:13:54am
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once
#include "AbstractFeature.h"

class TimeRms: public AbstractFeature
{
public:
    
    TimeRms();
    ~TimeRms();
    
    Error_t init(float fSampleRateInHz, int iNumChannels, int iBlockLength);
    Error_t reset();
    Error_t process(float **ppfInputBuffer, float **ppfOutputBuffer);
    
private:
    
    float m_fEpsilon;
};
