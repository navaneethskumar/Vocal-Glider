/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "stft.h"
#include "istft.h"
#include "shifter.h"
#include <complex>
#include <vector>
#include "gainControl.h"
#include "Distortion.h"
#include "AmplitudeModulation.h"

typedef std::complex<float> Cfloat;
constexpr auto MINBLOCKSPERWINDOW = 16;
//==============================================================================
/**
*/
class PitchShiftAudioProcessor  : public juce::AudioProcessor
                            #if JucePlugin_Enable_ARA
                             , public juce::AudioProcessorARAExtension
                            #endif
{
public:
    //==============================================================================
    PitchShiftAudioProcessor();
    ~PitchShiftAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    std::vector<std::unique_ptr<SHIFTER>> shifterBank;
    

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PitchShiftAudioProcessor)
    AmplitudeModulation AM;
    gainControl outputGain;
    Distortion distortionEffect;
    
    juce::AudioParameterFloat* pitchShiftKnobParameter;
    juce::AudioParameterFloat* distortionGainParameter;
    juce::AudioParameterFloat* biasKnobParameter;
    juce::AudioParameterFloat* phaserFreqParameter;
    juce::AudioParameterFloat* depthParameter;
    juce::AudioParameterFloat* outputGainParameter;
    
    float currentPitch=0;
    float currentDistortionGain;
    float currentBias;
    float currentPhaserFreq;
    float currentDepth;
    float currentOutputGain;
    
};
