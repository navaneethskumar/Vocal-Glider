/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "VocoderTools.h"
//==============================================================================
PitchShiftAudioProcessor::PitchShiftAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    pitchShiftKnobParameter = new juce::AudioParameterFloat(juce::ParameterID("1", 1), "SemiTone", -12, 12, 0);
     
    distortionGainParameter = new juce::AudioParameterFloat(juce::ParameterID("2", 2), " Distortion", 0.0f, 100.0f, 10.0f);
     biasKnobParameter = new juce::AudioParameterFloat(juce::ParameterID("3", 3), "Output Gain", 0.0f, 1.0f, 0.0f);

    phaserFreqParameter = new juce::AudioParameterFloat(juce::ParameterID("4", 4), "Rate", 0.0f, 20.0f, 2.0f);
    depthParameter = new juce::AudioParameterFloat(juce::ParameterID("5", 5), "Depth", 0.0f, 1.0f, 0.0f);
    outputGainParameter = new juce::AudioParameterFloat(juce::ParameterID("6", 6), "Output Gain", -96.0f, 36.0f, 0.0f);

    addParameter(pitchShiftKnobParameter);
    addParameter(distortionGainParameter);
    addParameter(biasKnobParameter);
    addParameter(phaserFreqParameter);
    addParameter(depthParameter);
    addParameter(outputGainParameter);
    
    currentPitch = *pitchShiftKnobParameter;
    currentDistortionGain = *distortionGainParameter;
    currentPhaserFreq = *phaserFreqParameter;
    currentDepth= *depthParameter;
    currentOutputGain = *outputGainParameter;

}

PitchShiftAudioProcessor::~PitchShiftAudioProcessor()
{
}

//==============================================================================
const juce::String PitchShiftAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool PitchShiftAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool PitchShiftAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool PitchShiftAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double PitchShiftAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int PitchShiftAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int PitchShiftAudioProcessor::getCurrentProgram()
{
    return 0;
}

void PitchShiftAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String PitchShiftAudioProcessor::getProgramName (int index)
{
    return {};
}

void PitchShiftAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void PitchShiftAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    // Determine FFT order
    int minWindowLength = MINBLOCKSPERWINDOW * samplesPerBlock;
    int order = 0;
    int windowLength = 1;
    while (windowLength < minWindowLength)
    {
        order++;
        windowLength *= 2;
    }
    shifterBank.resize(getNumInputChannels());
    for (auto ch = 0; ch < getNumInputChannels(); ch++)
    {
        shifterBank[ch] = std::unique_ptr<SHIFTER>(new SHIFTER);
        shifterBank[ch]->init(order);
    }
    AM.prepareToPlay(sampleRate);
}

void PitchShiftAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PitchShiftAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
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

void PitchShiftAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    


    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());
    if(currentPitch!= *pitchShiftKnobParameter){
        currentPitch= *pitchShiftKnobParameter;
    }
    float hopratio = pow(2.0f, *pitchShiftKnobParameter / 12.0);

    for (auto ch = 0; ch < totalNumInputChannels; ch++)
        shifterBank[ch]->step(buffer.getWritePointer(ch), buffer.getNumSamples(), hopratio);
    
    if (*distortionGainParameter != currentDistortionGain|| *biasKnobParameter != currentBias) {
                currentDistortionGain = *distortionGainParameter;
        currentBias = *biasKnobParameter;
            }
    distortionEffect.process(buffer, *distortionGainParameter,*biasKnobParameter);
    
            
    if (*phaserFreqParameter != currentPhaserFreq || *depthParameter != currentDepth) {

        currentPhaserFreq = *phaserFreqParameter;
        currentDepth = *depthParameter;
    }

    

    AM.processBlock(buffer, *phaserFreqParameter, *depthParameter);


    
    if (*outputGainParameter != currentOutputGain) {
        currentOutputGain = *outputGainParameter;
        outputGain.setGain(*outputGainParameter);
    }
    outputGain.processAudio(buffer);

}

//==============================================================================
bool PitchShiftAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* PitchShiftAudioProcessor::createEditor()
{
    return new PitchShiftAudioProcessorEditor (*this);
}

//==============================================================================
void PitchShiftAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void PitchShiftAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new PitchShiftAudioProcessor();
}
