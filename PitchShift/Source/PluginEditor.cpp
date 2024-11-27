/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PitchShiftAudioProcessorEditor::PitchShiftAudioProcessorEditor (PitchShiftAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);
    setLookAndFeel(&Custom);
    //pitchshift
    addAndMakeVisible(pitchShiftLabel);
    pitchShiftLabel.setText("Pitch Shift", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(pitchShiftKnob);
    
//distortion drive
    addAndMakeVisible(distortionGainLabel);
    distortionGainLabel.setText("Saturation", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(distortionGainKnob);
 //distortion bias
    addAndMakeVisible(biasLabel);
    biasLabel.setText("Bias", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(biasKnob);
    
    
    //outputgain
    addAndMakeVisible(outputGainLabel);
    outputGainLabel.setText("Output Gain", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(outputGainKnob);
    
    //rate
    
    addAndMakeVisible(phaserFreqLabel);
    phaserFreqLabel.setText("Rate", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(phaserFreqKnob);
    
    //depth
    addAndMakeVisible(depthLabel);
    depthLabel.setText("Depth", juce::NotificationType::dontSendNotification);
    addAndMakeVisible(depthKnob);
    
    // styling
    

    pitchShiftKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //feedbackSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::grey);
    pitchShiftKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    pitchShiftKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    pitchShiftKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    pitchShiftKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    pitchShiftLabel.attachToComponent(&pitchShiftKnob, false);
    pitchShiftLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    pitchShiftLabel.setJustificationType(juce::Justification::centredTop);
    pitchShiftLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    pitchShiftLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    
    distortionGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //feedbackSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::grey);
    distortionGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    distortionGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    distortionGainKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    distortionGainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    distortionGainLabel.attachToComponent(&distortionGainKnob, false);
    
    distortionGainLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    distortionGainLabel.setJustificationType(juce::Justification::centredTop);
    distortionGainLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    distortionGainLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    
    biasKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //feedbackSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::grey);
    biasKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    biasKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    biasKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    biasKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    biasLabel.attachToComponent(&biasKnob, false);
    
    biasLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    biasLabel.setJustificationType(juce::Justification::centredTop);
    biasLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    biasLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    
    

    outputGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    //feedbackSlider.setColour(juce::Slider::ColourIds::trackColourId, juce::Colours::grey);
    outputGainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    outputGainKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    outputGainKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    outputGainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    outputGainLabel.attachToComponent(&outputGainKnob, false);
    outputGainLabel.setFont(juce::Font(16.0f, juce::Font::plain));
    outputGainLabel.setJustificationType(juce::Justification::centredTop);

    outputGainLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    outputGainLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    
    phaserFreqKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserFreqKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    phaserFreqKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    phaserFreqKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    phaserFreqKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    phaserFreqLabel.attachToComponent(&phaserFreqKnob, false);
    phaserFreqLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    phaserFreqLabel.setJustificationType(juce::Justification::centredTop);
    phaserFreqLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    phaserFreqLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    depthKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    depthKnob.setColour(juce::Slider::ColourIds::thumbColourId, juce::Colours::purple);
    depthKnob.setColour(juce::Slider::ColourIds::backgroundColourId, juce::Colours::white);
    depthKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    
    
    depthLabel.attachToComponent(&depthKnob, false);
    depthLabel.setFont(juce::Font(15.0f, juce::Font::plain));
    depthLabel.setJustificationType(juce::Justification::centredTop);
    depthLabel.setColour(juce::Label::textColourId, juce::Colours::whitesmoke);
    depthLabel.setColour(juce::Label::backgroundColourId, juce::Colour(juce::Colours::transparentBlack));
    
    
    
    
    
    auto parameterTree = audioProcessor.getParameters();

    pitchShiftParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(0);
    
    distGainKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(1);
    biasKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(2);
   
    
    phaserFreqKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(3);
    depthknobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(4);
    outputGainKnobParameter = (juce::AudioParameterFloat*)parameterTree.getUnchecked(5);
    
//
    pitchShiftKnob.setRange(pitchShiftParameter->range.start, pitchShiftParameter->range.end, pitchShiftParameter->range.interval);
    

//        int minPitch = pitchShiftParameter->getNormalisableRange().start;
//        int maxPitch = pitchShiftParameter->getNormalisableRange().end;
//
//        pitchShiftKnob.setRange(minPitch, maxPitch);
    

    distortionGainKnob.setRange(distGainKnobParameter->range.start, distGainKnobParameter->range.end, distGainKnobParameter->range.interval);
    biasKnob.setRange(biasKnobParameter->range.start, biasKnobParameter->range.end, biasKnobParameter->range.interval);
    
    
    outputGainKnob.setRange(outputGainKnobParameter->range.start, outputGainKnobParameter->range.end, outputGainKnobParameter->range.interval);
    
    phaserFreqKnob.setRange(phaserFreqKnobParameter->range.start, phaserFreqKnobParameter->range.end, phaserFreqKnobParameter->range.interval);
    
    depthKnob.setRange(depthknobParameter->range.start, depthknobParameter->range.end, depthknobParameter->range.interval);
    
    
    //
    
    pitchShiftKnob.setValue(0, juce::NotificationType::dontSendNotification);

    
    
    distortionGainKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    biasKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    
    outputGainKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    
    
    phaserFreqKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    
    depthKnob.setValue(0.0f, juce::NotificationType::dontSendNotification);
    
    
    //
    
    
    pitchShiftKnob.onValueChange = [this]
    {
        *pitchShiftParameter = pitchShiftKnob.getValue();
    };
    distortionGainKnob.onValueChange = [this]
    {
        *distGainKnobParameter = distortionGainKnob.getValue();
    };
    biasKnob.onValueChange = [this]
    {
        *biasKnobParameter = biasKnob.getValue();
    };
    outputGainKnob.onValueChange = [this]
    {
        *outputGainKnobParameter = outputGainKnob.getValue();
    };
    phaserFreqKnob.onValueChange = [this]
    {
        *phaserFreqKnobParameter = phaserFreqKnob.getValue();
    };

    depthKnob.onValueChange = [this]
    {
        *depthknobParameter = depthKnob.getValue();
    };
    
}

PitchShiftAudioProcessorEditor::~PitchShiftAudioProcessorEditor()
{
}

//==============================================================================
void PitchShiftAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));


    g.setColour (juce::Colours::white);
    g.setFont (15.0f);


    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    
   
    
    
    
    background = juce::ImageCache::getFromMemory(BinaryData::background_png, BinaryData::background_pngSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);
   // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    
   // background = juce::ImageCache::getFromMemory(BinaryData::guitar_jpg, BinaryData::guitar_jpgSize);
    g.drawImageWithin(background, 0, 0, getWidth(), getHeight(), juce::RectanglePlacement::stretchToFit);

    g.setColour (juce::Colours::whitesmoke);
    g.setFont(25.0f);
    
    g.setOpacity(0.9f);
    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
//    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void PitchShiftAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    auto x = getWidth() / 10;
    auto y = getHeight() / 10;

    /*
        Use the setBounds() function to position the GUI Components (x,y) and set the width and height (width,height)
     
//    */


pitchShiftKnob.setBounds(3.8 * x, 3 * y, 4.5 * x, 4.5 * y);
    biasKnob.setBounds(0.1 * x, 6.2 * y, 2.5 * x, 2.5 * y);
distortionGainKnob.setBounds(0.1 * x, 1.4 * y, 3 * x, 3 * y);
//dampKnob.setBounds(5.9 * x, 3.2 * y, 4 * x, 4 * y);

    phaserFreqKnob.setBounds(2.5 * x, 6 * y, 2.5 * x, 2.5 * y);
   depthKnob.setBounds(2.5 * x, 1.4 * y, 2.5 * x, 2.5 * y);
    
    
outputGainKnob.setBounds(6.5 * x,  3 * y, 4 * x, 4 * y);

 //   bypassButton.setBounds(4.9 * x, 8.8 * y, 1.4 * x, 1 * y);
    
   
    
}
