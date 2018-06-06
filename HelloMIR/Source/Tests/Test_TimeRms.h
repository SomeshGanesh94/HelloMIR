/*
  ==============================================================================

    Test_TimeRms.h
    Created: 5 Jun 2018 1:57:38am
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class TestTimeRms: public UnitTest
{
public:
    TestTimeRms(): UnitTest ("TimeRms")
    {
        m_pCTimeRms = nullptr;
        m_ppfInputBuffer = nullptr;
        m_ppfOutputBuffer = nullptr;
    }
    
    void runTest() override
    {
        //================================================================================================
        beginTest("Constructor");
        
        m_pCTimeRms = new TimeRms();
        expect(m_pCTimeRms->isInitialized() == false);
        
        //================================================================================================
        beginTest("Not initialized errors");
        
        expect(m_pCTimeRms->reset() == Error_t::kNotInitializedError);
        
        m_ppfInputBuffer = new float*[2];
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            m_ppfInputBuffer[iChannel] = new float[2];
        }
        m_ppfOutputBuffer = new float*[2];
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            m_ppfOutputBuffer[iChannel] = new float[2];
        }
        
        expect(m_pCTimeRms->process(m_ppfInputBuffer, m_ppfOutputBuffer) == Error_t::kNotInitializedError);
        
        //================================================================================================
        beginTest("Initialization");
        
        
    }
    
private:
    
    TimeRms *m_pCTimeRms;
    float **m_ppfInputBuffer;
    float **m_ppfOutputBuffer;
};

static TestTimeRms Test_TimeRms;
