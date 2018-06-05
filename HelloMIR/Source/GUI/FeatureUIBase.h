/*
  ==============================================================================

    FeatureUIBase.h
    Created: 4 Jun 2018 7:34:04pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class FeatureUIBase    : public Component
{
public:
    
    FeatureUIBase(){}
    ~FeatureUIBase(){}

    virtual void paint (Graphics& g){}
    virtual void resized(){}
    virtual void setValue (float **ppfInputBuffer){}
    virtual void setNumChannels (int iChannels){}

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (FeatureUIBase)
};
