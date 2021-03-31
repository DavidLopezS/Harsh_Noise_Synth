/*
  ==============================================================================

    SynthVoice.cpp
    Created: 30 Mar 2021 10:38:28am
    Author:  David López Saludes

  ==============================================================================
*/

#include "SynthVoice.h"

bool SynthVoice::canPlaySound(juce::SynthesiserSound* sound) 
{
	return dynamic_cast<juce::SynthesiserSound*>(sound) != nullptr;
}
void SynthVoice::startNote(int midiNoteNumber, float velocity, juce::SynthesiserSound* sound, int currentPitchWheelPosition)
{
	//Turns on the note
	osc.setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber));
	adsr.noteOn();
}
void SynthVoice::stopNote(float velocity, bool allowTailOff)
{
	//Turns off the note
	adsr.noteOff();

	if (!allowTailOff || !adsr.isActive())
		clearCurrentNote();
}
void SynthVoice::controllerMoved(int controllerNumber, int newControllerValue)
{

}
void SynthVoice::pitchWheelMoved(int newPitchWheelValue)
{

}
void SynthVoice::prepareToPlay(double sampleRate, int samplesPerBlock, int outputChannels)
{
	//Setting the params of the adsr, oscillators and gain
	adsr.setSampleRate(sampleRate);

	juce::dsp::ProcessSpec spec;
	spec.maximumBlockSize = samplesPerBlock;
	spec.sampleRate = sampleRate;
	spec.numChannels = outputChannels;

	osc.prepare(spec);
	gain.prepare(spec);

	gain.setGainLinear(0.3f);

	isPrepared = true;//bool that checks if the fucntion is being called correctly
}
void SynthVoice::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
	adsrParams.attack = attack;
	adsrParams.decay = decay;
	adsrParams.sustain = sustain;
	adsrParams.release = release;

	adsr.setParameters(adsrParams);
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float> &outputBuffer, int startSample, int numSamples)
{
	jassert(isPrepared); 

	//Application of the main synth parameters

	if (!isVoiceActive())
		return;

	synthBuffer.setSize(outputBuffer.getNumChannels(), numSamples, false, false, false);
	synthBuffer.clear();

	juce::dsp::AudioBlock<float> audioBlock{ synthBuffer };
	osc.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));
	gain.process(juce::dsp::ProcessContextReplacing<float>(audioBlock));

	adsr.applyEnvelopeToBuffer(synthBuffer, 0, synthBuffer.getNumSamples());

	for (int channel = 0; channel < outputBuffer.getNumChannels(); ++channel)
	{
		outputBuffer.addFrom(channel, startSample, synthBuffer, channel, 0, numSamples);

		if (!adsr.isActive())
			clearCurrentNote();
	}
}