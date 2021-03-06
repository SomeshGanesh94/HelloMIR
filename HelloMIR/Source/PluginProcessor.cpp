/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HelloMirAudioProcessor::HelloMirAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    m_pFeature = nullptr;
}

HelloMirAudioProcessor::~HelloMirAudioProcessor()
{
    delete m_pFeature;
    m_pFeature = nullptr;
}

//==============================================================================
const String HelloMirAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HelloMirAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HelloMirAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HelloMirAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HelloMirAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HelloMirAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HelloMirAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HelloMirAudioProcessor::setCurrentProgram (int index)
{
}

const String HelloMirAudioProcessor::getProgramName (int index)
{
    return {};
}

void HelloMirAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void HelloMirAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    m_ppfCurrentDisplayValue = new float*[getTotalNumInputChannels()];
    for (int iChannel=0; iChannel<getTotalNumInputChannels(); iChannel++)
    {
        m_ppfCurrentDisplayValue[iChannel] = new float[samplesPerBlock];
    }
    
    m_iBlockLength = samplesPerBlock;
}

void HelloMirAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
    
    for (int iChannel=0; iChannel<getTotalNumInputChannels(); iChannel++)
    {
        delete [] m_ppfCurrentDisplayValue[iChannel];
    }
    delete [] m_ppfCurrentDisplayValue;
    m_ppfCurrentDisplayValue = nullptr;
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HelloMirAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HelloMirAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.

//    pCFeatureComputation->computeFeature(FeatureComputation::eFeatureName::kTimeRms, (float**) buffer.getArrayOfReadPointers(), m_ppfCurrentDisplayValue);

    if (m_pFeature != nullptr)
    {
        m_pFeature->process((float**) buffer.getArrayOfReadPointers(), m_ppfCurrentDisplayValue);

    }
}

//==============================================================================
bool HelloMirAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* HelloMirAudioProcessor::createEditor()
{
    return new HelloMirAudioProcessorEditor (*this);
}

//==============================================================================
void HelloMirAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HelloMirAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HelloMirAudioProcessor();
}

float** HelloMirAudioProcessor::getCurrentDisplayValue()
{
    return m_ppfCurrentDisplayValue;
}

Error_t HelloMirAudioProcessor::setFeature(Feature_t featureType)
{
    if (m_pFeature != nullptr)
    {
        m_pFeature->reset();
        delete m_pFeature;
    }
    
    switch (featureType)
    {
        case kTimeRms:
            m_pFeature = new TimeRms();
            break;
            
        case kTimeZcr:
            m_pFeature = new TimeZcr();
            break;
            
        case kTimeStd:
            m_pFeature = new TimeStd();
            break;
            
        case kTimePeakEnvelope:
            m_pFeature = new TimePeakEnvelope();
            break;
            
        case kTimeAcfCoeff:
            m_pFeature = new TimeAcfCoeff();
            
        default:
            m_pFeature = new TimeRms();
            break;
    }
    
    m_pFeature->init(this->getSampleRate(), this->getTotalNumInputChannels(), m_iBlockLength);
    
    return kNoError;
}
