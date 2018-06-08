/*
  ==============================================================================

    TimeZcrUI.h
    Created: 5 Jun 2018 11:15:16pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../../JuceLibraryCode/JuceHeader.h"
#include "FeatureUIBase.h"

//==============================================================================
/*
*/
class TimeZcrUI    : public FeatureUIBase
{
public:
    TimeZcrUI()
    {
        m_pfZcrValue = new float[m_iMaxChannels];
        m_iNumChannels = 1;
        
        m_lMinRange.setText("0", dontSendNotification);
        m_lMinRange.setFont(12);
        addAndMakeVisible(m_lMinRange);
        
        m_lMaxRange.setText("1", dontSendNotification);
        m_lMaxRange.setFont(12);
        addAndMakeVisible(m_lMaxRange);
    }

    ~TimeZcrUI()
    {
        delete [] m_pfZcrValue;
        m_pfZcrValue = nullptr;
        
        m_iNumChannels = 1;
    }

    void paint (Graphics& g) override
    {
        g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));   // clear the background
        
        g.setColour (Colours::green);
        
        float fWidth = float(getWidth() - 20);
        float fChannelBlockSize = (fWidth - (float(m_iNumChannels) - 1) * 10.0) / float(m_iNumChannels);
        float fVolumeBlockSize = float(getHeight());
        
        for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
        {
            float fStart = float(iChannel) * fChannelBlockSize + 10 * float(iChannel);
            float fHeight = (1.0 - m_pfZcrValue[iChannel]) * fVolumeBlockSize;
            
            g.setColour(Colours::green);
            g.fillRect(fStart, fHeight, fChannelBlockSize, float(getHeight()));
        }
        
        
        g.drawRect (getLocalBounds(), 1);
        
        g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("Time domain Zcr", getLocalBounds(),
                    Justification::centred, true);
    }

    void resized() override
    {
        m_lMinRange.setBounds(100, 235, 20, 15);
        m_lMaxRange.setBounds(100, 0, 20, 15);
    }
    
    void setValue (float **ppfZcrValue) override
    {
        for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
        {
            m_pfZcrValue[iChannel] = ppfZcrValue[iChannel][0];
        }
        this->repaint();
    }
    
    void setNumChannels (int iNumChannels) override
    {
        m_iNumChannels = iNumChannels;
    }

private:
    
    int m_iNumChannels;
    float *m_pfZcrValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeZcrUI)
};
