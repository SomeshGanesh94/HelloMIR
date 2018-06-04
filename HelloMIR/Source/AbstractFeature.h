/*
  ==============================================================================

    AbstractFeature.h
    Created: 3 Jun 2018 12:57:29am
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once
#include "ErrorDef.h"
#include <math.h>
#include "FeatureDef.h"

class AbstractFeature
{
public:
    
    AbstractFeature(){}
    virtual ~AbstractFeature(){}
    
    /* Pure virtual functions necessary for each feature */
    virtual Error_t init(float fSampleRateInHz, int iNumChannels, int iBlockLength) = 0;
    virtual Error_t reset() = 0;
    virtual Error_t process(float **ppfInputBuffer, float **ppfOutputBuffer) = 0;
    virtual bool isInitialized() = 0;
    
    virtual int getNumChannels()
    {
        return m_iNumChannels;
    }
    
protected:
    
    bool m_bIsInitialized;
    float m_fSampleRateInHz;
    int m_iNumChannels;
    int m_iBlockLength;
};
