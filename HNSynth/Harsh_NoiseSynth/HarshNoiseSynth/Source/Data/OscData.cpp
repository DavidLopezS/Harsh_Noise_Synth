/*
  ==============================================================================

    OscData.cpp
    Created: 1 Apr 2021 5:21:13pm
    Author:  David López Saludes

  ==============================================================================
*/

#include "OscData.h"

void OscData::prepareToPlay(juce::dsp::ProcessSpec& spec)
{
	fmOsc.prepare(spec);
	prepare(spec);	
}

void OscData::setWaveType(const int choice)
{
	switch(choice)
	{
	case 0: //Sine Wave
		initialise([](float x) {return std::sin(x); });
		break;

	case 1: //Saw Wave
		initialise([](float x) {return x / juce::MathConstants<float>::pi; });
		break;

	case 2: //Square Wave
		initialise([](float x) {return x < 0.0f ? -1.0f : 1.0f; });
		break;

	default:
		jassertfalse;
		break;
	}

}

void OscData::setWaveFrequency(const int midiNoteNumber)
{
	setFrequency(juce::MidiMessage::getMidiNoteInHertz(midiNoteNumber) + fmMod);
	lastMidiNote = midiNoteNumber;
}

void OscData::getNextAudioBlock(juce::dsp::AudioBlock<float>& block)
{
	for(int channel = 0; channel < block.getNumChannels(); ++channel)
	{
		for (int sample = 0; sample < block.getNumSamples(); ++sample) 
		{
			fmMod = fmOsc.processSample(block.getSample(channel, sample)) * fmDepth;
		}
	}

	process(juce::dsp::ProcessContextReplacing<float>(block));
}

void OscData::setFmParams(const float depth, const float freq)
{
	fmOsc.setFrequency(freq);
	fmDepth = depth;
	setFrequency(juce::MidiMessage::getMidiNoteInHertz(lastMidiNote) + fmMod);
}
