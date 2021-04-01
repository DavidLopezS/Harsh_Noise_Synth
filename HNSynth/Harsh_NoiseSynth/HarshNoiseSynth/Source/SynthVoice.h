/*
  ==============================================================================

    SynthVoice.h
    Created: 30 Mar 2021 10:38:28am
    Author:  David López Saludes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "SynthSound.h"
#include "Data/AdsrData.h"
#include "Data/OscData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:

	bool canPlaySound(juce::SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
	void update(const float attack, const float decay, const float sustain, const float release);
	void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
	
	//One Line function, always in the header
	OscData& getOscillator() { return osc; }

private:

	AdsrData adsr;
	juce::AudioBuffer<float> synthBuffer;

	//OscData == Oscillator class
	OscData osc;
	//juce::dsp::Oscillator<float> osc{ [](float x) {return x / juce::MathConstants<float>::pi; } };
	juce::dsp::Gain<float> gain;
	bool isPrepared{ false };

};