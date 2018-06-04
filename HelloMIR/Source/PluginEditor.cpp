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
    
    addAndMakeVisible(m_TimeRmsUI);
    m_TimeRmsUI.setSize(120, 250);
    
    /* Labels */
    m_lAppName.setText("Hello MIR", dontSendNotification);
    m_lAppName.setFont(24);
    addAndMakeVisible(m_lAppName);
    
    m_lCreatorName.setText("Somesh Ganesh", dontSendNotification);
    m_lCreatorName.setFont(12);
    addAndMakeVisible(m_lCreatorName);
    
    m_lCurrentDisplayValue.setText("0.0", dontSendNotification);
    m_lCurrentDisplayValue.setFont(12);
    addAndMakeVisible(m_lCurrentDisplayValue);
    
    /* Feature selector */
    m_cbFeatureSelect.setText("Choose a feature");
    m_cbFeatureSelect.addItemList(saFeatures, 1);
    m_cbFeatureSelect.addListener(this);
    addAndMakeVisible(m_cbFeatureSelect);
    
    /* Timer */
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
    
    m_TimeRmsUI.setBounds(350, 250, 120, 250);
    m_TimeRmsUI.setNumChannels(processor.getTotalNumInputChannels());
    
    /* Labels */
    m_lAppName.setBounds(350, 20, 100, 50);
    m_lCreatorName.setBounds(355, 50, 100, 30);
    m_lCurrentDisplayValue.setBounds(375, 150, 100, 30);
    
    /* Combo box */
    m_cbFeatureSelect.setBounds(300, 200, 200, 25);
}

void HelloMirAudioProcessorEditor::timerCallback()
{
    /* Change value */
    float** ppfTemp = processor.getCurrentDisplayValue();
    m_lCurrentDisplayValue.setText(String(ppfTemp[0][0]), dontSendNotification);
    
    m_TimeRmsUI.setValue(ppfTemp);
}

void HelloMirAudioProcessorEditor::comboBoxChanged(ComboBox *cb)
{
    /* Feature selector */
    if (cb == &m_cbFeatureSelect)
    {
        int iItemId = m_cbFeatureSelect.getSelectedId();
        processor.setFeature(static_cast<Feature_t>(iItemId - 1));
    }
}
