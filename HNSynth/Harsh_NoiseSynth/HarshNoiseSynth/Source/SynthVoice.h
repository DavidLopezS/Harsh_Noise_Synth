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
#include "Data/OscData.h"
#include "Data/AdsrData.h"
#include "Data/FilterData.h"

class SynthVoice : public juce::SynthesiserVoice
{
public:

	bool canPlaySound(juce::SynthesiserSound* sound) override;
	void startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition) override;
	void stopNote(float velocity, bool allowTailOff) override;
	void controllerMoved(int controllerNumber, int newControllerValue) override;
	void pitchWheelMoved(int newPitchWheelValue) override;
	void prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels);
	void updateAdsr(const float attack, const float decay, const float sustain, const float release);//The variables are const type because they are not meant to be modified
	void updateFilter(const int filterType, const float cutoff, const float resonance);
	void updateModAdsr(const float attack, const float decay, const float sustain, const float release);
	void renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
	
	//One Line function, always in the header
	OscData& getOscillator() { return osc; }

private:

	juce::AudioBuffer<float> synthBuffer;

	//OscData == Oscillator class
	OscData osc;
	AdsrData adsr;
	FilterData filter;
	AdsrData modAdsr;
	juce::dsp::Gain<float> gain;
	bool isPrepared{ false };

};