/*
  ==============================================================================

    AdsrComponent.cpp
    Created: 31 Mar 2021 6:00:06pm
    Author:  David López Saludes

  ==============================================================================
*/

#include <JuceHeader.h>
#include "AdsrComponent.h"

//==============================================================================
AdsrComponent::AdsrComponent(juce::AudioProcessorValueTreeState& apvts)
{
	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	attackAttatchment = std::make_unique<SliderAttachment>(apvts, "ATTACK", attackSlider);
	decayAttatchment = std::make_unique<SliderAttachment>(apvts, "DECAY", decaySlider);
	sustainAttatchment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
	releaseAttatchment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);

	//Sliders structure
	setSliderParams(attackSlider);
	setSliderParams(decaySlider);
	setSliderParams(sustainSlider);
	setSliderParams(releaseSlider);
}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::paint (juce::Graphics& g)
{
	g.fillAll(juce::Colours::black);
}

void AdsrComponent::resized()
{
	//Boundaries of the plug-in visual interface
	const auto bounds = getLocalBounds().reduced(10);
	const auto padding = 10;
	const auto sliderWidth = bounds.getWidth() / 4 - padding;
	const auto sliderHeight = bounds.getHeight();
	const auto sliderStartX = 0;
	const auto sliderStartY = 0;

	attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
	decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
	releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
}

void AdsrComponent::setSliderParams(juce::Slider& slider)
{
	//Slider structure (attack)
	slider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
	slider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 50, 25);
	addAndMakeVisible(slider);
}