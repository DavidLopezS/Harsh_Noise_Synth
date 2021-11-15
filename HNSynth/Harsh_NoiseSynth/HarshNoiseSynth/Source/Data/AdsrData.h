/*
  ==============================================================================

    AdsrData.h
    Created: 31 Mar 2021 6:00:42pm
    Author:  David López Saludes

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class AdsrData : public juce::ADSR
{
public:
	void updateADSR(const float attack, const float decay, const float sustain, const float release);

private:
	juce::ADSR::Parameters adsrParams;

};
