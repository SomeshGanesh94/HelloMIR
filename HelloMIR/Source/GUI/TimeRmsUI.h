/*
  ==============================================================================

    TimeRmsUI.h
    Created: 3 Jun 2018 12:04:10am
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FeatureUIBase.h"

//==============================================================================
/*
*/
class TimeRmsUI    : public FeatureUIBase
{
public:
    TimeRmsUI()
    {
        m_pfRmsValue = new float[m_iMaxChannels];
        m_iNumChannels = 1;
        
        m_lMinRange.setText("-inf dB", dontSendNotification);
        m_lMinRange.setFont(10);
        addAndMakeVisible(m_lMinRange);
        
        m_lMaxRange.setText("0 dB", dontSendNotification);
        m_lMaxRange.setFont(10);
        addAndMakeVisible(m_lMaxRange);
    }

    ~TimeRmsUI()
    {
        delete [] m_pfRmsValue;
        m_pfRmsValue = nullptr;
        
        m_iNumChannels = 1;
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background

        g.setColour (Colours::green);
        
        float fWidth = float(getWidth() - 30);
        float fChannelBlockSize = (fWidth - (float(m_iNumChannels) - 1) * 10.0) / float(m_iNumChannels);
        float fVolumeBlockSize = getHeight() / 12;
        
        for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
        {
            float fStart = float(iChannel) * fChannelBlockSize + 10 * float(iChannel);
            float fHeight = abs(m_pfRmsValue[iChannel]) * fVolumeBlockSize;
            
            if (m_pfRmsValue[iChannel] >= 0)
            {
                g.setColour(Colours::red);
            }
            else
            {
                g.setColour(Colours::green);
            }
            
            g.fillRect(fStart, fHeight, fChannelBlockSize, float(getHeight()));
        }
        
        
        g.drawRect (getLocalBounds(), 1);

        g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("Time domain Rms", getLocalBounds(),
                    Justification::centred, true);
    }

    void resized() override
    {
        m_lMinRange.setBounds(90, 235, 30, 15);
        m_lMaxRange.setBounds(90, 0, 30, 15);
    }

    void setValue (float **ppfRmsValue) override
    {
        for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
        {
            m_pfRmsValue[iChannel] = ppfRmsValue[iChannel][0];
        }
        this->repaint();
    }
    
    void setNumChannels (int iNumChannels) override
    {
        m_iNumChannels = iNumChannels;
    }
    
private:
    
    int m_iNumChannels;
    float *m_pfRmsValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeRmsUI)
};
