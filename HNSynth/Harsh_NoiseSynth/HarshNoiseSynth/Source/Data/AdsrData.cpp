/*
  ==============================================================================

    AdsrData.cpp
    Created: 31 Mar 2021 6:00:42pm
    Author:  david

  ==============================================================================
*/

#include "AdsrData.h"

void AdsrData::updateADSR(const float attack, const float decay, const float sustain, const float release)
{
	adsrParams.attack = attack;
	adsrParams.decay = decay;
	adsrParams.sustain = sustain;
	adsrParams.release = release;

	setParameters(adsrParams);
};
