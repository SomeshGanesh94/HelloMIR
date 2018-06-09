/*
  ==============================================================================

    Test_TimeAcfCoeff.h
    Created: 8 Jun 2018 5:19:05pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"

class TestTimeAcfCoeff: public UnitTest
{
public:
    TestTimeAcfCoeff(): UnitTest ("TimeAcfCoeff")
    {
        m_pCTimeAcfCoeff = nullptr;
        m_ppfInputBuffer = nullptr;
        m_ppfOutputBuffer = nullptr;
    }
    
    void runTest() override
    {
        //================================================================================================
        beginTest("Constructor");
        
        m_pCTimeAcfCoeff = new TimeAcfCoeff();
        expect(m_pCTimeAcfCoeff->isInitialized() == false);
        
        //================================================================================================
        beginTest("Not initialized errors");
        
        expect(m_pCTimeAcfCoeff->reset() == Error_t::kNotInitializedError);
        
        m_ppfInputBuffer = new float*[2];
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            m_ppfInputBuffer[iChannel] = new float[10];
        }
        m_ppfOutputBuffer = new float*[2];
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            m_ppfOutputBuffer[iChannel] = new float[5];
        }
        
        expect(m_pCTimeAcfCoeff->process(m_ppfInputBuffer, m_ppfOutputBuffer) == Error_t::kNotInitializedError);
        
        //================================================================================================
        beginTest("Initialization");
        
        /* m_pCTimeAcfCoeff->init(float fSampleRateInHz, int iNumChannels, int iBlockLength) */
        expect(m_pCTimeAcfCoeff->init(0.0, 2, 512) == Error_t::kFunctionInvalidArgsError);
        expect(m_pCTimeAcfCoeff->init(44100.0, -2, 512) == Error_t::kFunctionInvalidArgsError);
        expect(m_pCTimeAcfCoeff->init(44100.0, 2, -4) == Error_t::kFunctionInvalidArgsError);
        
        expect(m_pCTimeAcfCoeff->init(44100.0, 2, 10) == Error_t::kNoError);
        expect(m_pCTimeAcfCoeff->isInitialized() == true);
        
        //================================================================================================
        beginTest("Normalize");
        expect(m_pCTimeAcfCoeff->isNormalized() == false);
        expect(m_pCTimeAcfCoeff->setNormalize(true) == Error_t::kNoError);
        expect(m_pCTimeAcfCoeff->isNormalized() == true);
        
        //================================================================================================
        beginTest("Setting number of coefficients");
        
        expect(m_pCTimeAcfCoeff->setNumCoeff(-3) == Error_t::kFunctionInvalidArgsError);
        
        expect(m_pCTimeAcfCoeff->setNumCoeff(5) == Error_t::kNoError);
        expect(m_pCTimeAcfCoeff->getNumCoeff() == 5);
        
        //================================================================================================
        beginTest("Process");
        
        /* m_pCTimeAcfCoeff->process(float **ppfInputBuffer, float **ppfOutputBuffer) */
        
        float fTempInput[2][10] = {{0.412, -0.43, 0.0, 0.0, 0.35, -0.86, 0.62, 0.84, -0.38, -0.58}, {0.4, 0.8, 0.2, 0.1, -0.2, 0.3, -0.1, 0.6, -0.9, 1}};
        float fTempOutput[2][5] = {{-0.2114, -0.4406, 0.0397, 0.3156, -0.2956}, {-0.3513, 0.3291, -0.1772, 0.2152, -0.0411}};
        
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            for (int iSample=0; iSample<10; iSample++)
            {
                m_ppfInputBuffer[iChannel][iSample] = fTempInput[iChannel][iSample];
            }
        }
        expect(m_pCTimeAcfCoeff->process(m_ppfInputBuffer, m_ppfOutputBuffer) == Error_t::kNoError);
               
        for (int iChannel=0; iChannel<2; iChannel++)
        {
            for (int iSample=0; iSample<5; iSample++)
            {
                expect((m_ppfOutputBuffer[iChannel][iSample] - fTempOutput[iChannel][iSample]) <= 1e-3);
            }
        }
               
        //================================================================================================
        beginTest("Reset");
       
        expect(m_pCTimeAcfCoeff->reset() == Error_t::kNoError);
        expect(m_pCTimeAcfCoeff->isInitialized() == false);
       
        delete m_pCTimeAcfCoeff;
        m_pCTimeAcfCoeff = nullptr;
    }
    
private:
    
    TimeAcfCoeff *m_pCTimeAcfCoeff;
    float **m_ppfInputBuffer;
    float **m_ppfOutputBuffer;
};

static TestTimeAcfCoeff Test_TimeAcfCoeff;
