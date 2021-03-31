/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class HarshNoiseSynthAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    HarshNoiseSynthAudioProcessorEditor (HarshNoiseSynthAudioProcessor&);
    ~HarshNoiseSynthAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:

	void HarshNoiseSynthAudioProcessorEditor::setSliderParams(juce::Slider& slider);

	juce::Slider attackSlider;
	juce::Slider decaySlider;
	juce::Slider sustainSlider;
	juce::Slider releaseSlider;
	juce::ComboBox oscSelector;

	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	//unique_ptr allows to free up memory once the plug-in is closed
	std::unique_ptr<SliderAttachment> attackAttatchment;
	std::unique_ptr<SliderAttachment> decayAttatchment;
	std::unique_ptr<SliderAttachment> sustainAttatchment;
	std::unique_ptr<SliderAttachment> releaseAttatchment;
	std::unique_ptr<juce::AudioProcessorValueTreeState::ComboBoxAttachment> oscSelectAttatchment;

	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	HarshNoiseSynthAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (HarshNoiseSynthAudioProcessorEditor)
};
