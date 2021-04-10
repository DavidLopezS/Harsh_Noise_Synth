/*
  ==============================================================================

    FilterData.h
    Created: 2 Apr 2021 11:31:39am
    Author:  David López Saludes

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class FilterData
{
public:
	void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
	void process(juce::AudioBuffer<float>& buffer);
	void updateParameters(const int filterType, const float frequency, const float resonance, const float modulator = 1.0f);//Modulator is an optional parameter, thus it has value
	void reset();

private:
	juce::dsp::StateVariableTPTFilter <float> filter;
	bool isPrepared = false;

};
