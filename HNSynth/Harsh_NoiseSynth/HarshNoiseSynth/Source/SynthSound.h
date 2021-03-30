/*
  ==============================================================================

    SynthSound.h
    Created: 30 Mar 2021 10:38:45am
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class SynthSound : public juce::SynthesiserSound
{
private:
	bool appliesToNote(int midiNoteNumber) override { return true; }
	bool appliesToChannel(int midiChannel) override { return true; }
};