/*
  ==============================================================================

    AbstractFeature.h
    Created: 3 Jun 2018 12:57:29am
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once
#include "../Global/ErrorDef.h"
#include "../Global/FeatureDef.h"
#include <math.h>

class AbstractFeature
{
public:
    
    AbstractFeature()
    {
        m_bIsInitialized = false;
    }
    virtual ~AbstractFeature()
    {
        m_bIsInitialized = false;
    }
    
    /* Pure virtual functions necessary for each feature */
    virtual Error_t init(float fSampleRateInHz, int iNumChannels, int iBlockLength) = 0;
    virtual Error_t reset() = 0;
    virtual Error_t process(float **ppfInputBuffer, float **ppfOutputBuffer) = 0;
    
    virtual bool isInitialized()
    {
        return m_bIsInitialized;
    }
    
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
