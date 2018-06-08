/*
  ==============================================================================

    Test_TimeStd.h
    Created: 7 Jun 2018 11:03:49pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class TestTimeStd: public UnitTest
{
public:
    TestTimeStd(): UnitTest("TimeStd")
    {
        m_pCTimeStd = nullptr;
        m_ppfInputBuffer = nullptr;
        m_ppfOutputBuffer = nullptr;
    }
    
    void runTest() override
    {
        //================================================================================================
        beginTest("Constructor");
        
        m_pCTimeStd = new TimeStd();
        expect(m_pCTimeStd->isInitialized() == false);
        
        //================================================================================================
        beginTest("Not initialized errors");
        
        expect(m_pCTimeStd->reset() == Error_t::kNotInitializedError);
        
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
        
        expect(m_pCTimeStd->process(m_ppfInputBuffer, m_ppfOutputBuffer) == Error_t::kNotInitializedError);
        
        //================================================================================================
        beginTest("Initialization");
        
        /* m_pCTimeStd->init(float fSampleRateInHz, int iNumChannels, int iBlockLength) */
        expect(m_pCTimeStd->init(-23, 4, 1024) == Error_t::kFunctionInvalidArgsError);
        expect(m_pCTimeStd->init(5.0, -1, 1024) == Error_t::kFunctionInvalidArgsError);
        expect(m_pCTimeStd->init(4.0, 2, -6) == Error_t::kFunctionInvalidArgsError);
        
        expect(m_pCTimeStd->init(44100.0, 3, 5) == Error_t::kNoError);
        expect(m_pCTimeStd->isInitialized() == true);
        
        //================================================================================================
        beginTest("Process");
        
        /* m_pCTimeStd->process(float **ppfInputBuffer, float **ppfOutputBuffer) */
        float fTempInput[3][5] = {{0.0, -0.2, -0.4, -1, 0.7}, {0.3, -0.1, 0.6, -0.9, 1}, {0.4, 0.8, 0.2, 0.1, -0.2}};
        float fTempOutput[3][1]  {{0.5528}, {0.6493}, {0.3323}};
        
        for (int iChannel=0; iChannel<3; iChannel++)
        {
            for (int iSample=0; iSample<5; iSample++)
            {
                m_ppfInputBuffer[iChannel][iSample] = fTempInput[iChannel][iSample];
            }
        }
        m_pCTimeStd->process(m_ppfOutputBuffer, m_ppfOutputBuffer);
        
        for (int iChannel=0; iChannel<3; iChannel++)
        {
            expect((m_ppfOutputBuffer[iChannel][0] - fTempOutput[iChannel][0]) <= 1e-3);
        }
        
        //================================================================================================
        beginTest("Reset");
        
        expect(m_pCTimeStd->reset() == Error_t::kNoError);
        expect(m_pCTimeStd->isInitialized() == false);
        
        delete m_pCTimeStd;
        m_pCTimeStd = nullptr;
    }
    
private:
    
    TimeStd *m_pCTimeStd;
    float **m_ppfInputBuffer;
    float **m_ppfOutputBuffer;
};

static TestTimeStd Test_TimeStd;
