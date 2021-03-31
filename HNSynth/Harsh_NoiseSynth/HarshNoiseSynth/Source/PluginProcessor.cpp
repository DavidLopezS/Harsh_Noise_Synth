/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
HarshNoiseSynthAudioProcessor::HarshNoiseSynthAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "Parameters", createParams())
#endif
{
	synth.addSound(new SynthSound());
	synth.addVoice(new SynthVoice());
}

HarshNoiseSynthAudioProcessor::~HarshNoiseSynthAudioProcessor()
{
}

//==============================================================================
const juce::String HarshNoiseSynthAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool HarshNoiseSynthAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool HarshNoiseSynthAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool HarshNoiseSynthAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double HarshNoiseSynthAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int HarshNoiseSynthAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int HarshNoiseSynthAudioProcessor::getCurrentProgram()
{
    return 0;
}

void HarshNoiseSynthAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String HarshNoiseSynthAudioProcessor::getProgramName (int index)
{
    return {};
}

void HarshNoiseSynthAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void HarshNoiseSynthAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
	synth.setCurrentPlaybackSampleRate(sampleRate);

	for (int i = 0; i < synth.getNumVoices(); i++) 
	{
		if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
		{
			voice->prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
		}
	}
}

void HarshNoiseSynthAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool HarshNoiseSynthAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void HarshNoiseSynthAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

	for(int i = 0; i < synth.getNumVoices(); ++i)
	{
		if(auto voice = dynamic_cast<SynthVoice*>(synth.getVoice(i)))
		{
			//Osc controll
			//ADSR
			//LFO

			auto &attack = *apvts.getRawParameterValue("ATTACK");
			auto &decay = *apvts.getRawParameterValue("DECAY");
			auto &sustain = *apvts.getRawParameterValue("SUSTAIN");
			auto &release = *apvts.getRawParameterValue("RELEASE");

			//load() used because we are dealing with atomic floats
			voice->update(attack.load(), decay.load(), sustain.load(), release.load());
		}
	}

	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

//==============================================================================
bool HarshNoiseSynthAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* HarshNoiseSynthAudioProcessor::createEditor()
{
    return new HarshNoiseSynthAudioProcessorEditor (*this);
}

//==============================================================================
void HarshNoiseSynthAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void HarshNoiseSynthAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new HarshNoiseSynthAudioProcessor();
}

//Value Tree
juce::AudioProcessorValueTreeState::ParameterLayout HarshNoiseSynthAudioProcessor::createParams()
{
	std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

	//Combobox: switch oscillators
	
	params.push_back(std::make_unique<juce::AudioParameterChoice>("OSC", "Oscillator", juce::StringArray{ "Sine", "Saw", "Square" }, 0));

	//ADSR
	params.push_back(std::make_unique<juce::AudioParameterFloat>("ATTACK", "Attack", juce::NormalisableRange<float>{0.1f, 1.0f, }, 0.1f));//Attack
	params.push_back(std::make_unique<juce::AudioParameterFloat>("DECAY", "Decay", juce::NormalisableRange<float>{0.1f, 1.0f, }, 0.1f));//Decay
	params.push_back(std::make_unique<juce::AudioParameterFloat>("SUSTAIN", "Sustain", juce::NormalisableRange<float>{0.1f, 1.0f, }, 1.0f));//Sustain
	params.push_back(std::make_unique<juce::AudioParameterFloat>("RELEASE", "Release", juce::NormalisableRange<float>{0.1f, 3.0f, }, 0.4f));//Release

	return { params.begin(), params.end() };
}