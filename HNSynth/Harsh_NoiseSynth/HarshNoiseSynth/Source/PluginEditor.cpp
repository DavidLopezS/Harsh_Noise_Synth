/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HarshNoiseSynthAudioProcessorEditor::HarshNoiseSynthAudioProcessorEditor (HarshNoiseSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), 
	audioProcessor (p), 
	osc (audioProcessor.apvts, "OSC1WAVETYPE", "OSC1FMFREQ", "OSC1FMDEPTH"), 
	adsr (audioProcessor.apvts),
	filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERES")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(600, 500);

	//make adsr visible
	addAndMakeVisible(osc);

	//make adsr visible
	addAndMakeVisible(adsr);

	//make filter visible
	addAndMakeVisible(filter);
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

	const auto paddingX = 5;
	const auto paddingY = 35; 
	const auto paddingY2 = 235;

	osc.setBounds(paddingX, paddingY, 300, 200);
	adsr.setBounds(osc.getRight(), paddingY, 280, 200);
	filter.setBounds(paddingX, paddingY2, 300, 200);
}