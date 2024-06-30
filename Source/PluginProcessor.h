/*
  ==============================================================================
    Author:  Benjamin Quiedeville
  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

#include "common.h"
#include "SmoothParam.h"

#include "Biquad.h"

#include <vector>
#include <assert.h>

#ifndef  JucePlugin_Name
#define JucePlugin_Name "TableSaw"
#endif



#define UP_SAMPLE_FACTOR 4
#define FILTER_Q 0.4


enum Params {
    GAIN,
    
    LOW_BOOST,
    LOW_FREQ,
    
    HIGH_BOOST,
    HIGH_FREQ,
    
    OUT_VOLUME,

    CHANNEL_CONFIG,
    
    N_PARAMS 
};

static std::vector<juce::Identifier> ParamIDs = {
    "GAIN",
    
    "LOW_BOOST",
    "LOW_FREQ",
    
    "HIGH_BOOST",
    "HIGH_FREQ",
    
    "OUT_VOLUME",
    
    "CHANNEL_CONFIG"
};


enum ChannelConfig {
    Mono,
    FakeStereo,
    Stereo
};


struct OverSampler {

    Biquad upSampleFilter1 {BIQUAD_LOWPASS};
    Biquad upSampleFilter2 {BIQUAD_LOWPASS};
    
    Biquad downSampleFilter1 {BIQUAD_LOWPASS};
    Biquad downSampleFilter2 {BIQUAD_LOWPASS};
};


struct Processor  : public juce::AudioProcessor,
                           juce::AudioProcessorValueTreeState::Listener
                           #if JucePlugin_Enable_ARA
                           , public juce::AudioProcessorARAExtension
                           #endif
{
    //==============================================================================
    Processor();
    ~Processor() override;
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;
    
    #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
    #endif
    
    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    
    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;
    
    //==============================================================================
    const juce::String getName() const override;
    
    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;
    
    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;
    
    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    juce::AudioProcessorValueTreeState apvts;
    
    OnepoleFilter inputFilter;
    OnepoleFilter softClipperFilter;
    OnepoleFilter couplingFilter;
    OnepoleFilter hardClipperFilter;
    Biquad lowFilter {BIQUAD_PEAK};
    Biquad highFilter1 {BIQUAD_PEAK};
    Biquad highFilter2 {BIQUAD_PEAK};
    SmoothParamLinear gain;
    SmoothParamLinear volume;
    
    
    double samplerate = 44100.0;
    double upSamplerate = UP_SAMPLE_FACTOR * samplerate;
    
    u32 upBlockSize = 0;

    OverSampler *overSampler;
    Sample *upSampledBlockL;
    Sample *upSampledBlockR;
    
    ChannelConfig channelConfig = Mono;
    
    void initParameters();
    void parameterChanged(const juce::String &parameterID, float newValue) override;
    
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Processor)
};
