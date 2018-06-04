/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "GUI/FeatureUIHeaders.h"

//==============================================================================
/**
*/
class HelloMirAudioProcessorEditor  : public AudioProcessorEditor, public Timer, public ComboBox::Listener
{
public:
    HelloMirAudioProcessorEditor (HelloMirAudioProcessor&);
    ~HelloMirAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;
    
    void timerCallback() override;
    void comboBoxChanged(ComboBox *cb) override;

private:
    /* This reference is provided as a quick way for your editor to access the processor object that created it */
    HelloMirAudioProcessor& processor;
    
    Label m_lAppName;
    Label m_lCreatorName;
    Label m_lCurrentDisplayValue;
    
    ComboBox m_cbFeatureSelect;
    
    TimeRmsUI m_TimeRmsUI;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HelloMirAudioProcessorEditor)
};
