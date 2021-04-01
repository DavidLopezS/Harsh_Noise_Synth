/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HarshNoiseSynthAudioProcessorEditor::HarshNoiseSynthAudioProcessorEditor (HarshNoiseSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc (audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH"), adsr (audioProcessor.apvts)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	//make adsr visible
	addAndMakeVisible(osc);

	//make adsr visible
	addAndMakeVisible(adsr);
}

HarshNoiseSynthAudioProcessorEditor::~HarshNoiseSynthAudioProcessorEditor()
{
}

//==============================================================================
void HarshNoiseSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);
}

void HarshNoiseSynthAudioProcessorEditor::resized()
{

	osc.setBounds(10, 10, 180, 200);

	//Set adsr bounds
	adsr.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight());
}