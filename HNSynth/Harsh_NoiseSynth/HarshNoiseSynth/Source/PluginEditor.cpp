/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
HarshNoiseSynthAudioProcessorEditor::HarshNoiseSynthAudioProcessorEditor (HarshNoiseSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	attackAttatchment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "ATTACK", attackSlider);
	decayAttatchment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "DECAY", decaySlider);
	sustainAttatchment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "SUSTAIN", sustainSlider);
	releaseAttatchment = std::make_unique<SliderAttachment>(audioProcessor.apvts, "RELEASE", releaseSlider);

	oscSelectAttatchment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(audioProcessor.apvts, "OSC", oscSelector);

	//Sliders structure
	setSliderParams(attackSlider);
	setSliderParams(decaySlider);
	setSliderParams(sustainSlider);
	setSliderParams(releaseSlider);
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
	//Boundaries of the plug-in visual interface
	const auto bounds = getLocalBounds().reduced(10);
	const auto padding = 10;
	const auto sliderWidth = bounds.getWidth() / 4 - padding;
	const auto sliderHeight = bounds.getHeight() / 4 - padding;
	const auto sliderStartX = 0;
	const auto sliderStartY = bounds.getHeight() / 2 - (sliderHeight / 2);

	attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
	decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void HarshNoiseSynthAudioProcessorEditor::setSliderParams (juce::Slider& slider)
{
	//Slider structure (attack)
	slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
	addAndMakeVisible(slider);
}