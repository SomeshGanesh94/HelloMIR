/*
  ==============================================================================

    Test_TimePeakEnvelope.h
    Created: 8 Jun 2018 1:04:31am
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class TestTimePeakEnvelope: public UnitTest
{
public:
    TestTimePeakEnvelope(): UnitTest ("TimePeakEnvelope")
    {
        m_pCTimePeakEnvelope = nullptr;
        m_ppfInputBuffer = nullptr;
        m_ppfOutputBuffer = nullptr;
    }
    
    void runTest() override
    {
        //================================================================================================
        beginTest("Constructor");
        
        m_pCTimePeakEnvelope = new TimePeakEnvelope();
        expect(m_pCTimePeakEnvelope->isInitialized() == false);
        
        //================================================================================================
        beginTest("Not initialized errors");
        
        expect(m_pCTimePeakEnvelope->reset() == Error_t::kNotInitializedError);
        
        m_ppfInputBuffer = new float*[2];
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            m_ppfInputBuffer[iChannel] = new float[5];
        }
        m_ppfOutputBuffer = new float*[2];
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            m_ppfOutputBuffer[iChannel] = new float[2];
        }
        
        expect(m_pCTimePeakEnvelope->process(m_ppfInputBuffer, m_ppfOutputBuffer) == Error_t::kNotInitializedError);
        
        //================================================================================================
        beginTest("Initialization");
        
        /* m_pCTimePeakEnvelope->init(float fSampleRateInHz, int iNumChannels, int iBlockLength) */
        expect(m_pCTimePeakEnvelope->init(0.0, 2, 512) == Error_t::kFunctionInvalidArgsError);
        expect(m_pCTimePeakEnvelope->init(44100.0, -2, 512) == Error_t::kFunctionInvalidArgsError);
        expect(m_pCTimePeakEnvelope->init(44100.0, 2, -4) == Error_t::kFunctionInvalidArgsError);
        
        expect(m_pCTimePeakEnvelope->init(44100.0, 2, 4) == Error_t::kNoError);
        expect(m_pCTimePeakEnvelope->isInitialized() == true);
        
        //================================================================================================
        beginTest("Process");
        
        /* m_pCTimePeakEnvelope->process(float **ppfInputBuffer, float **ppfOutputBuffer) */
        float fTempInput[2][10] = {{0.2, 0.1, -0.2, -0.5, 1, 0.4, 0.2, 0.7546, -0.142}, {0.412, -0.43, 0.0, 0.0, 0.35, -0.86, 0.62, 0.84, -0.38, -0.58}};
        float fTempOutput1 [2][2] = {{0, -40.0845}, {-7.3306, -44.5824}};
        float fTempOutput2 [2][2] = {{-2.4457, -35.3417}, {-1.3100, -33.1928}};
        
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            for (int iSample=0; iSample<5; iSample++)
            {
                m_ppfInputBuffer[iChannel][iSample] = fTempInput[iChannel][iSample];
            }
        }
        m_pCTimePeakEnvelope->process(m_ppfInputBuffer, m_ppfOutputBuffer);
        
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            expect((m_ppfOutputBuffer[iChannel][0] - fTempOutput1[iChannel][0]) <= 1e-3);
        }
        
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            for (int iSample=0; iSample<5; iSample++)
            {
                m_ppfInputBuffer[iChannel][iSample] = fTempInput[iChannel][iSample+5];
            }
        }
        m_pCTimePeakEnvelope->process(m_ppfInputBuffer, m_ppfOutputBuffer);
        
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            expect((m_ppfOutputBuffer[iChannel][0] - fTempOutput2[iChannel][0]) <= 1e-3);
        }
        
        //================================================================================================
        beginTest("Reset");
        
        expect(m_pCTimePeakEnvelope->reset() == Error_t::kNoError);
        expect(m_pCTimePeakEnvelope->isInitialized() == false);
        
        delete m_pCTimePeakEnvelope;
        m_pCTimePeakEnvelope = nullptr;
    }
    
private:
    
    TimePeakEnvelope *m_pCTimePeakEnvelope;
    float **m_ppfInputBuffer;
    float **m_ppfOutputBuffer;
};

static TestTimePeakEnvelope Test_TimePeakEnvelope;
