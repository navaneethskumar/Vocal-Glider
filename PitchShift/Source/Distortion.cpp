/*
  =============================================================================
    Distortion.cpp
    Created: 1 Nov 2023 7:07:19
    Author:  Navaneeth Suresh Kuma
  ============================================================================
*/

#include "Distortion.h"

Distortion::Distortion()
{
    // Constructor code here
    drive=0.0;
    bias=0.0;
}

Distortion::~Distortion()
{
    // Destructor code here
}

void Distortion::process(juce::AudioBuffer<float>& buffer, float gain, float biasAmount)
{
    drive=gain;
    bias = biasAmount;
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel) {
       
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample) {
           
            float Saturation = 2*std::tanh(buffer.getReadPointer(channel)[sample] * (1+drive)/(juce::MathConstants<float>::pi));
        //                saturation = 2 * atan(obj.drive * input) / pi;
        //    output = (1 + obj.bias) * (input - obj.bias * saturation);
            buffer.getWritePointer(channel)[sample] = (1 + bias) * (buffer.getReadPointer(channel)[sample] - bias * Saturation);
        }
    }
}
