/*
  ==============================================================================

    OscComponent.cpp
    Created: 1 Apr 2021 6:10:50pm
    Author:  David L�pez Saludes

  ==============================================================================
*/

#include <JuceHeader.h>
#include "OscComponent.h"

//==============================================================================
OscComponent::OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId)
{
	juce::StringArray choices{ "Sine", "Saw", "Square" };
	oscWaveSelector.addItemList(choices, 1);
	addAndMakeVisible(oscWaveSelector);

	oscWaveSelectorAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, waveSelectorId, oscWaveSelector);

	setSliderWithLabel(fmFreqSlider, fmFreqLabel, apvts, fmFreqId, fmFreqAttatchment);//Fm Freq UI Application
	setSliderWithLabel(fmDepthSlider, fmDepthLabel, apvts, fmDepthId, fmDepthAttatchment);//FmDepth Ui Application
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);
}

void OscComponent::resized()
{
	const auto sliderPosY = 80;
	const auto sliderWidth = 100;
	const auto sliderHeight = 90;
	const auto labelYOffset = 20;
	const auto labelHeight = 20;

	oscWaveSelector.setBounds(0, 0, 90, 20);

	//setSliderLabelBounds(fmFreqSlider, fmFreqLabel, 0, sliderPosY, sliderWidth, sliderHeight, fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, fmFreqSlider.getWidth(), labelHeight);
	//setSliderLabelBounds(fmDepthSlider, fmDepthLabel, fmFreqSlider.getRight(), sliderPosY, sliderWidth, sliderHeight, fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight);

	fmFreqSlider.setBounds(0, sliderPosY, sliderWidth, sliderHeight);
	fmFreqLabel.setBounds(fmFreqSlider.getX(), fmFreqSlider.getY() - labelYOffset, fmFreqSlider.getWidth(), labelHeight);

	fmDepthSlider.setBounds(fmFreqSlider.getRight(), sliderPosY, sliderWidth, sliderHeight);
	fmDepthLabel.setBounds(fmDepthSlider.getX(), fmDepthSlider.getY() - labelYOffset, fmDepthSlider.getWidth(), labelHeight);
}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
	slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
	addAndMakeVisible(slider);

	attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

	label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
	label.setFont(15.0f);
	label.setJustificationType(juce::Justification::centred);
	addAndMakeVisible(label);
}

void OscComponent::setSliderLabelBounds(juce::Slider& slider, juce::Label& label, int xSlider, int ySlider, int widthSlider, int heightSlider, int xLabel, int yLabel, int widthLabel, int heightLabel)
{

	slider.setBounds(xSlider, ySlider, widthSlider, heightSlider);
	label.setBounds(xLabel, yLabel, widthLabel, heightLabel);

}