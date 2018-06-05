/*
  ==============================================================================

    AbstractFeatureUI.h
    Created: 4 Jun 2018 7:34:04pm
    Author:  Somesh Ganesh

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class AbstractFeatureUI    : public Component
{
public:
    
    AbstractFeatureUI(){}
    ~AbstractFeatureUI(){}

    void paint (Graphics& g) = 0;
    void resized() = 0;
    virtual void setValue (float **ppfInputBuffer) = 0;
    virtual void setNumChannels (int iChannels) = 0;

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AbstractFeatureUI)
};
