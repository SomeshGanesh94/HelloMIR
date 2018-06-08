/*
  ==============================================================================

    Test_TimeZcr.h
    Created: 7 Jun 2018 9:49:36pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class TestTimeZcr: public UnitTest
{
public:
    TestTimeZcr(): UnitTest("TimeZcr")
    {
        m_pCTimeZcr = nullptr;
        m_ppfInputBuffer = nullptr;
        m_ppfOutputBuffer = nullptr;
    }
    
    void runTest() override
    {
        //================================================================================================
        beginTest("Constructor");
        
        m_pCTimeZcr = new TimeZcr();
        expect(m_pCTimeZcr->isInitialized() == false);
        
        //================================================================================================
        beginTest("Not initialized errors");
        
        expect(m_pCTimeZcr->reset() == Error_t::kNotInitializedError);
        
        m_ppfInputBuffer = new float*[3];
        for (int iChannel=0; iChannel<3; iChannel++)
        {
            m_ppfInputBuffer[iChannel] = new float[5];
        }
        m_ppfOutputBuffer = new float*[3];
        for (int iChannel=0; iChannel<3; iChannel++)
        {
            m_ppfOutputBuffer[iChannel] = new float;
        }
        
        expect(m_pCTimeZcr->process(m_ppfInputBuffer, m_ppfOutputBuffer) == Error_t::kNotInitializedError);
        
        //================================================================================================
        beginTest("Initialization");
        
        /* m_pCTimeZcr->init(float fSampleRateInHz, int iNumChannels, int iBlockLength) */
        expect(m_pCTimeZcr->init(-3, 4, 1024) == Error_t::kFunctionInvalidArgsError);
        expect(m_pCTimeZcr->init(5.0, 0, 1024) == Error_t::kFunctionInvalidArgsError);
        expect(m_pCTimeZcr->init(4.0, 4, -2) == Error_t::kFunctionInvalidArgsError);
        
        expect(m_pCTimeZcr->init(44100.0, 3, 5) == Error_t::kNoError);
        expect(m_pCTimeZcr->isInitialized() == true);
        
        //================================================================================================
        beginTest("Process");
        
        /* m_pCTimeZcr->process(float **ppfInputBuffer, float **ppfOutputBuffer) */
        float fTempInput[3][5] = {{0.0, -0.2, -0.4, -1, 0.7}, {0.3, -0.1, 0.6, -0.9, 1}, {0.4, 0.8, 0.2, 0.1, -0.2}};
        float fTempOutput[3][1]  {{0.3750}, {1.0}, {0.25}};
        
        for (int iChannel=0; iChannel<3; iChannel++)
        {
            for (int iSample=0; iSample<5; iSample++)
            {
                m_ppfInputBuffer[iChannel][iSample] = fTempInput[iChannel][iSample];
            }
        }
        m_pCTimeZcr->process(m_ppfOutputBuffer, m_ppfOutputBuffer);
        
        for (int iChannel=0; iChannel<3; iChannel++)
        {
            expect((m_ppfOutputBuffer[iChannel][0] - fTempOutput[iChannel][0]) <= 1e-3);
        }
        
        //================================================================================================
        beginTest("Reset");
        
        expect(m_pCTimeZcr->reset() == Error_t::kNoError);
        expect(m_pCTimeZcr->isInitialized() == false);
        
        delete m_pCTimeZcr;
        m_pCTimeZcr = nullptr;
    }
    
private:
    
    TimeZcr *m_pCTimeZcr;
    float **m_ppfInputBuffer;
    float **m_ppfOutputBuffer;
};

static TestTimeZcr Test_TimeZcr;
