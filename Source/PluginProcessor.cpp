/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
WahWahAudioProcessor::WahWahAudioProcessor()
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
    so = std::unique_ptr<SinOscilator>(new SinOscilator(10,400));
    cf = std::unique_ptr<CanonicalFilter>(new CanonicalFilter(Mode::BANDPASS, *so));

    addParameter (control_freq = new AudioParameterFloat ("control_freq", // parameter ID
                                                  "control frequency", // parameter name
                                                  1.f,   // minimum value
                                                  20.f,   // maximum value
                                                  10.f)); // default value

    addParameter (amplitude = new AudioParameterFloat ("control amplitude", // parameter ID
                                                       "amplitude", // parameter name
                                                       1.f,   // minimum value
                                                       499.f,   // maximum value
                                                       50.f)); // default value

    addParameter (center_freq = new AudioParameterFloat ("center_freq", // parameter ID
                                                      "center frequency", // parameter name
                                                      500.f,   // minimum value
                                                      1000.f,   // maximum value
                                                      500.f)); // default value

}

WahWahAudioProcessor::~WahWahAudioProcessor()
{

}

//==============================================================================
const String WahWahAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WahWahAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WahWahAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WahWahAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WahWahAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WahWahAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WahWahAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WahWahAudioProcessor::setCurrentProgram (int index)
{
}

const String WahWahAudioProcessor::getProgramName (int index)
{
    return {};
}

void WahWahAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WahWahAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    cf->resize_channels(getTotalNumInputChannels());
    cf->init_states(sampleRate, samplesPerBlock);
    so->init_states(sampleRate,samplesPerBlock);
}

void WahWahAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WahWahAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void WahWahAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    for(int i=0; i< buffer.getNumSamples();i++){
        so->set_amplitude(amplitude->get());
        so->set_frequency(control_freq->get());
        cf->set_frequency(center_freq->get());

        for(int channel = 0;channel < totalNumInputChannels;++channel){
            auto* channelData = buffer.getWritePointer (channel);

            cf->process_sample(channelData[i],channel);
        }
    }
}

//==============================================================================
bool WahWahAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WahWahAudioProcessor::createEditor()
{
    return new GenericAudioProcessorEditor (this);
}

//==============================================================================
void WahWahAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WahWahAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WahWahAudioProcessor();
}
