/*
  ==============================================================================

    TimeStd.h
    Created: 7 Jun 2018 10:37:14pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once
#include "AbstractFeature.h"

class TimeStd: public AbstractFeature
{
public:
    
    TimeStd();
    ~TimeStd();
    
    Error_t init(float fSampleRateInHz, int iNumChannels, int iBlockLength);
    Error_t reset();
    Error_t process(float **ppfInputBuffer, float **ppfOutputBuffer);
};
