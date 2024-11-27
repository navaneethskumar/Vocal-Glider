/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "CustomSlider.h"
//==============================================================================
/**
*/
class PitchShiftAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    PitchShiftAudioProcessorEditor (PitchShiftAudioProcessor&);
    ~PitchShiftAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    PitchShiftAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PitchShiftAudioProcessorEditor)
    juce::Slider pitchShiftKnob;
    juce::Label pitchShiftLabel;

    juce::Slider phaserFreqKnob;
    juce::Label phaserFreqLabel;
//    juce::ToggleButton bypassButton;
    
    juce::Slider depthKnob;
    juce::Label depthLabel;

    juce::Slider distortionGainKnob;
    juce::Label distortionGainLabel;
    juce::Slider biasKnob;
    juce::Label biasLabel;

    juce::Slider outputGainKnob;
    juce::Label outputGainLabel;


    //declaring parameters here
    juce::AudioParameterFloat* pitchShiftParameter;
    juce::AudioParameterFloat* distGainKnobParameter;
    juce::AudioParameterFloat* biasKnobParameter;

   

    juce::AudioParameterFloat* outputGainKnobParameter;
    juce::AudioParameterFloat* depthknobParameter;
    juce::AudioParameterFloat* phaserFreqKnobParameter;
    
    juce::Label textLabel;
    juce::Font textFont   { 12.0f };
    juce::Image background;
    CustomSlider Custom;
};
