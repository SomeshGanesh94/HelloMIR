/*
  ==============================================================================

    TimePeakEnvelopeUI.h
    Created: 8 Jun 2018 12:00:06am
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FeatureUIBase.h"

//==============================================================================
/*
*/
class TimePeakEnvelopeUI    : public FeatureUIBase
{
public:
    TimePeakEnvelopeUI()
    {
        m_ppfPeakValue = new float*[m_iMaxChannels];
        for (int iChannel=0; iChannel<m_iMaxChannels; iChannel++)
        {
            m_ppfPeakValue[iChannel] = new float[2];
        }
        m_iNumChannels = 1;
        
        m_lMinRange.setText("-inf dB", dontSendNotification);
        m_lMinRange.setFont(10);
        addAndMakeVisible(m_lMinRange);
        
        m_lMaxRange.setText("0 dB", dontSendNotification);
        m_lMaxRange.setFont(10);
        addAndMakeVisible(m_lMaxRange);
        
        m_lMaxPeak.setText("Max", dontSendNotification);
        m_lMaxPeak.setFont(10);
        addAndMakeVisible(m_lMaxPeak);
        
        m_lPPM.setText("PPM", dontSendNotification);
        m_lPPM.setFont(10);
        addAndMakeVisible(m_lPPM);
    }

    ~TimePeakEnvelopeUI()
    {
        for (int iChannel=0; iChannel<m_iMaxChannels; iChannel++)
        {
            delete [] m_ppfPeakValue[iChannel];
        }
        delete [] m_ppfPeakValue;
        m_ppfPeakValue = nullptr;
        
        m_iNumChannels = 1;
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::green);
        
        g.setColour (Colours::green);
        
        float fWidth = float(getWidth() - 30) / 2;
        float fChannelBlockSize = (fWidth - (float(m_iNumChannels) - 1) * 10.0) / float(m_iNumChannels);
        float fVolumeBlockSize = getHeight() / 12;
        
        for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
        {
            float fStart = float(iChannel) * fChannelBlockSize + 10 * float(iChannel);
            float fHeight = abs(m_ppfPeakValue[iChannel][0]) * fVolumeBlockSize;
            
            if (m_ppfPeakValue[iChannel][0] >= 0)
            {
                g.setColour(Colours::red);
            }
            else
            {
                g.setColour(Colours::green);
            }
            
            g.fillRect(fStart, fHeight, fChannelBlockSize, float(getHeight()));
        }
        
        
        g.setColour (Colours::green);
        
        fWidth = float(getWidth() - 30) / 2;
        fChannelBlockSize = (fWidth - (float(m_iNumChannels) - 1) * 10.0) / float(m_iNumChannels);
        fVolumeBlockSize = getHeight() / 12;
        
        for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
        {
            float fStart = float(iChannel) * fChannelBlockSize + 10 * float(iChannel) + float(getWidth() - 30) / 2;
            float fHeight = abs(m_ppfPeakValue[iChannel][1]) * fVolumeBlockSize;
            
            if (m_ppfPeakValue[iChannel][1] >= 0)
            {
                g.setColour(Colours::red);
            }
            else
            {
                g.setColour(Colours::green);
            }
            
            g.fillRect(fStart, fHeight, fChannelBlockSize, float(getHeight()));
        }
        
        g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

        g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("TimePeakEnvelope", getLocalBounds(),
                    Justification::centred, true);   // draw some placeholder text
    }

    void resized() override
    {
        m_lMinRange.setBounds(90, 235, 30, 15);
        m_lMaxRange.setBounds(90, 0, 30, 15);
        m_lMaxPeak.setBounds(10, 235, 35, 15);
        m_lPPM.setBounds(55, 235, 35, 15);
    }

    void setValue (float **ppfPeakValue) override
    {
        for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
        {
            float fDBValue[2] = {static_cast<float>(20.0*log10(ppfPeakValue[iChannel][0])), static_cast<float>(20.0*log10(ppfPeakValue[iChannel][1]))};
            
            if (fDBValue[0] > -12.0)
            {
                m_ppfPeakValue[iChannel][0] = fDBValue[0];
            }
            else
            {
                m_ppfPeakValue[iChannel][0] = -12.0;
            }
            if (fDBValue[1] > -12.0)
            {
                m_ppfPeakValue[iChannel][1] = fDBValue[1];
            }
            else
            {
                m_ppfPeakValue[iChannel][1] = -12.0;
            }
        }
        this->repaint();
    }
    
    void setNumChannels (int iNumChannels) override
    {
        m_iNumChannels = iNumChannels;
    }
    
private:
    
    int m_iNumChannels;
    float **m_ppfPeakValue;
    
    Label m_lMaxPeak;
    Label m_lPPM;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimePeakEnvelopeUI)
};
