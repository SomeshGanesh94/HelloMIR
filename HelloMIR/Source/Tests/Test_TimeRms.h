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
            m_ppfInputBuffer[iChannel] = new float[4];
        }
        m_ppfOutputBuffer = new float*[2];
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            m_ppfOutputBuffer[iChannel] = new float;
        }
        
        expect(m_pCTimeRms->process(m_ppfInputBuffer, m_ppfOutputBuffer) == Error_t::kNotInitializedError);
        
        //================================================================================================
        beginTest("Initialization");
        
        /* m_pCTimeRms->init(float fSampleRateInHz, int iNumChannels, int iBlockLength) */
        expect(m_pCTimeRms->init(0.0, 2, 512) == Error_t::kFunctionInvalidArgsError);
        expect(m_pCTimeRms->init(44100.0, -2, 512) == Error_t::kFunctionInvalidArgsError);
        expect(m_pCTimeRms->init(44100.0, 2, -4) == Error_t::kFunctionInvalidArgsError);
        
        expect(m_pCTimeRms->init(44100.0, 2, 4) == Error_t::kNoError);
        expect(m_pCTimeRms->isInitialized() == true);
        
        //================================================================================================
        beginTest("Process");
        
        /* m_pCTimeRms->process(float **ppfInputBuffer, float **ppfOutputBuffer) */
        float fTempInput[2][4] = {{0.2, 0.5, -0.3, 0.6}, {1.0, -0.2, 0.3, -0.6}};
        float fTempOutput[2][1] = {{-7.3283}, {-4.2887}};
        
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            for (int iSample=0; iSample<4; iSample++)
            {
                m_ppfInputBuffer[iChannel][iSample] = fTempInput[iChannel][iSample];
            }
        }
        m_pCTimeRms->process(m_ppfInputBuffer, m_ppfOutputBuffer);
        
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            expect((m_ppfOutputBuffer[iChannel][0] - fTempOutput[iChannel][0]) <= 1e-3);
        }
        
        //================================================================================================
        beginTest("Reset");
        
        expect(m_pCTimeRms->reset() == Error_t::kNoError);
        expect(m_pCTimeRms->isInitialized() == false);
        
        delete m_pCTimeRms;
        m_pCTimeRms = nullptr;
    }
    
private:
    
    TimeRms *m_pCTimeRms;
    float **m_ppfInputBuffer;
    float **m_ppfOutputBuffer;
};

static TestTimeRms Test_TimeRms;
