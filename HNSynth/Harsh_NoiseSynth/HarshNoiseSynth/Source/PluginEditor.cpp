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
	adsr ("Amp Envelope", audioProcessor.apvts, "ATTACK", "DECAY", "SUSTAIN", "RELEASE"),
	filter(audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERES"),
	modAdsr("Mod Envelope", audioProcessor.apvts, "MODATTACK", "MODDECAY", "MODSUSTAIN", "MODRELEASE")
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
	setSize(620, 500);

	//make adsr visible
	addAndMakeVisible(osc);

	//make adsr visible
	addAndMakeVisible(adsr);

	//make filter visible
	addAndMakeVisible(filter);

	//make mod adsr visible
	addAndMakeVisible(modAdsr);
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
	const auto width = 300;
	const auto height = 200;

	osc.setBounds(paddingX, paddingY, width, height);
	adsr.setBounds(osc.getRight(), paddingY, width, height);
	filter.setBounds(paddingX, paddingY2, width, height);
	modAdsr.setBounds(filter.getRight(), paddingY2, width, height);
}