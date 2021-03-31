/*
  ==============================================================================

    AdsrComponent.h
    Created: 31 Mar 2021 6:00:05pm
    Author:  david

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class AdsrComponent  : public juce::Component
{
public:
    AdsrComponent(juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    void paint (juce::Graphics&) override;
    void resized() override;

private:
	void setSliderParams(juce::Slider& slider);

	juce::Slider attackSlider;
	juce::Slider decaySlider;
	juce::Slider sustainSlider;
	juce::Slider releaseSlider;

	using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;

	//unique_ptr allows to free up memory once the plug-in is closed
	std::unique_ptr<SliderAttachment> attackAttatchment;
	std::unique_ptr<SliderAttachment> decayAttatchment;
	std::unique_ptr<SliderAttachment> sustainAttatchment;
	std::unique_ptr<SliderAttachment> releaseAttatchment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};
