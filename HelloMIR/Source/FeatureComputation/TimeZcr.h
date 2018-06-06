/*
  ==============================================================================

    TimeZcr.h
    Created: 5 Jun 2018 9:15:45pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once
#include "AbstractFeature.h"

class TimeZcr: public AbstractFeature
{
public:
    
    TimeZcr();
    ~TimeZcr();
    
    Error_t init(float fSampleRateInHz, int iNumChannels, int iBlockLength);
    Error_t reset();
    Error_t process(float **ppfInputBuffer, float **ppfOutputBuffer);
};
