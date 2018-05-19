/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloMirAudioProcessorEditor::HelloMirAudioProcessorEditor (HelloMirAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (800, 600);
    
    // Labels
    m_lAppName.setText("Hello MIR", dontSendNotification);
    m_lAppName.setFont(18);
    addAndMakeVisible(m_lAppName);
    
    m_lCreatorName.setText("Somesh Ganesh", dontSendNotification);
    m_lCreatorName.setFont(12);
    addAndMakeVisible(m_lCreatorName);
    
    m_lCurrentSampleValue.setText("0", dontSendNotification);
    m_lCurrentSampleValue.setFont(12);
    addAndMakeVisible(m_lCurrentSampleValue);
    
    // Timer
    startTimer(100);
}

HelloMirAudioProcessorEditor::~HelloMirAudioProcessorEditor()
{
}

//==============================================================================
void HelloMirAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

void HelloMirAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    
    // Labels
    m_lAppName.setBounds(350, 30, 100, 50);
    m_lCreatorName.setBounds(350, 80, 100, 30);
    m_lCurrentSampleValue.setBounds(350, 150, 100, 30);
}

void HelloMirAudioProcessorEditor::timerCallback()
{
    // change value
    m_lCurrentSampleValue.setText(String(processor.getCurrentSampleValue()), dontSendNotification);
}
