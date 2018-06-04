/*
  ==============================================================================

    TimeRmsUI.h
    Created: 3 Jun 2018 12:04:10am
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class TimeRmsUI    : public Component
{
public:
    TimeRmsUI()
    {
        m_pfRmsValue = new float[m_iMaxChannels];
        m_iNumChannels = 1;
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
        
        float fChannelBlockSize = (getWidth() - (m_iNumChannels - 1) * 10) / m_iNumChannels;
        float fVolumeBlockSize = getHeight() / 12;
        
        for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
        {
            float fStart = float(iChannel) * fChannelBlockSize + 10 * float(iChannel);
            float fEnd = fStart + fChannelBlockSize;
            float fHeight = abs(m_pfRmsValue[iChannel]) * fVolumeBlockSize;
            
            if (m_pfRmsValue[iChannel] >= 0)
            {
                g.setColour(Colours::red);
            }
            else
            {
                g.setColour(Colours::green);
            }
            
            g.fillRect(fStart, fHeight, fEnd, float(getHeight()));
        }
        
        
        g.drawRect (getLocalBounds(), 1);

        g.setColour (Colours::white);
        g.setFont (14.0f);
        g.drawText ("Time domain Rms", getLocalBounds(),
                    Justification::centred, true);
        
        
    }

    void resized() override
    {
    }

    void setValue (float **ppfRmsValue)
    {
        for (int iChannel=0; iChannel<m_iNumChannels; iChannel++)
        {
            m_pfRmsValue[iChannel] = ppfRmsValue[iChannel][0];
        }
        this->repaint();
    }
    
    void setNumChannels (int iNumChannels)
    {
        m_iNumChannels = iNumChannels;
    }
    
private:
    
    const int m_iMaxChannels = 128;
    
    int m_iNumChannels;
    float *m_pfRmsValue;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TimeRmsUI)
};
