/*
  ==============================================================================

    OscComponent.h
    Created: 1 Apr 2021 6:10:50pm
    Author:  David López Saludes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class OscComponent  : public juce::Component
{
public:
    OscComponent(juce::AudioProcessorValueTreeState& apvts, juce::String waveSelectorId, juce::String fmFreqId, juce::String fmDepthId);
    ~OscComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	juce::ComboBox oscWaveSelector;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscWaveSelectorAttachment;

	juce::Slider fmFreqSlider;
	juce::Slider fmDepthSlider;

	using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	std::unique_ptr<Attachment> fmFreqAttatchment;
	std::unique_ptr<Attachment> fmDepthAttatchment;

	juce::Label waveSelectorLabel{ "Wave Type", "Wave Type" };
	juce::Label fmFreqLabel{ "FM Freq", "FM Freq" };
	juce::Label fmDepthLabel{ "FM Depth", "FM Depth" };

	void setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment);
	void setSliderLabelBounds(juce::Slider& slider, juce::Label& label, int xSlider, int ySlider, int widthSlider, int heightSlider, int xLabel, int yLabel, int widthLabel, int heightLabel);

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OscComponent)
};
