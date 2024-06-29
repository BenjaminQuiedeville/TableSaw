/*
  ==============================================================================
    Author:  Benjamin Quiedeville
  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Processor::Processor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
,
apvts(*this, nullptr, juce::Identifier("Params"), createParameterLayout())

{
    
    overSampler = new OverSampler();
}

Processor::~Processor()
{
    delete overSampler;
}

//==============================================================================
const juce::String Processor::getName() const
{
    return JucePlugin_Name;
}

bool Processor::acceptsMidi() const
{
    #if JucePlugin_WantsMidiInput
    return true;
    #else
    return false;
    #endif
}

bool Processor::producesMidi() const
{
    #if JucePlugin_ProducesMidiOutput
    return true;
    #else
    return false;
    #endif
}

bool Processor::isMidiEffect() const
{
    #if JucePlugin_IsMidiEffect
    return true;
    #else
    return false;
    #endif
}

double Processor::getTailLengthSeconds() const
{
    return 0.0;
}

int Processor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
    // so this should be at least 1, even if you're not really implementing programs.
}

int Processor::getCurrentProgram()
{
    return 0;
}

void Processor::setCurrentProgram (int index)
{
    juce::ignoreUnused (index);
}

const juce::String Processor::getProgramName (int index)
{
    juce::ignoreUnused (index);
    return {};
}

void Processor::changeProgramName (int index, const juce::String& newName)
{
    juce::ignoreUnused (index, newName);
}

//==============================================================================
void Processor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    samplerate = sampleRate;
    upSamplerate = UP_SAMPLE_FACTOR * samplerate;
    
    inputFilter.prepareToPlay();
    softClipperFilter.prepareToPlay();
    couplingFilter.prepareToPlay();
    hardClipperFilter.prepareToPlay();
    
    lowFilter.prepareToPlay();
    highFilter1.prepareToPlay();
    highFilter2.prepareToPlay();
    
    gain.init(1.0f);
    volume.init(1.0f);

    inputFilter.setCoefficients(100.0, upSamplerate);
    softClipperFilter.setCoefficients(20000.0, upSamplerate);
    couplingFilter.setCoefficients(50.0f, upSamplerate);
    hardClipperFilter.setCoefficients(80000.f, upSamplerate);

    lowFilter.setCoefficients(85.0, FILTER_Q, 20.0, samplerate);
    highFilter1.setCoefficients(1100.0, FILTER_Q, 20.0, samplerate);

    overSampler->upSampleFilter1.prepareToPlay();
    overSampler->upSampleFilter2.prepareToPlay();
    overSampler->downSampleFilter1.prepareToPlay();
    overSampler->downSampleFilter2.prepareToPlay();

    // earlevel.com/main/2016/09/29/cascading-filters
    overSampler->upSampleFilter1.setCoefficients(samplerate/2 * 0.9, 0.54119610, atodb(UP_SAMPLE_FACTOR), upSamplerate);
    overSampler->upSampleFilter2.setCoefficients(samplerate/2 * 0.9, 1.3065630, atodb(UP_SAMPLE_FACTOR), upSamplerate);
    overSampler->downSampleFilter1.setCoefficients(samplerate/2 * 0.9, 0.54119610, 0.0, upSamplerate);
    overSampler->downSampleFilter2.setCoefficients(samplerate/2 * 0.9, 1.3065630, 0.0, upSamplerate);

    if (upSampledBlockL) {
        upSampledBlockL = (Sample *)realloc(upSampledBlockL, samplesPerBlock * UP_SAMPLE_FACTOR * sizeof(Sample));
    } else {
        upSampledBlockL = (Sample *)calloc(samplesPerBlock * UP_SAMPLE_FACTOR, sizeof(Sample));
    }
    
    if (upSampledBlockR) {
        upSampledBlockR = (Sample *)realloc(upSampledBlockR, samplesPerBlock * UP_SAMPLE_FACTOR * sizeof(Sample));
    } else {
        upSampledBlockR = (Sample *)calloc(samplesPerBlock * UP_SAMPLE_FACTOR, sizeof(Sample));
    }

}

void Processor::releaseResources() {}

bool Processor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
    #else
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

void Processor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ignoreUnused (midiMessages);
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();
    
    const u32 numSamples = buffer.getNumSamples();
        
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i) {
        buffer.clear (i, 0, numSamples);
    }
    
    Sample *audioPtrL = buffer.getWritePointer(0);
    Sample *audioPtrR = buffer.getWritePointer(1);

    if (channelConfig == Mono) { 
        audioPtrR = nullptr;
    }

    if (channelConfig == FakeStereo) {
        for (u32 i = 0; i < numSamples; i++) {
            audioPtrR[i] = -audioPtrL[i];
        }
    }

    
    
    // input filtering
    // gain 
    // upsampling
    // soft clip asym (avec filtre passe haut ?)
    // decoupling
    // diode (noisegatething)
    // hard clipping 
    // lowpass 
    // eq
    // volume
    
    

}

//==============================================================================
bool Processor::hasEditor() const {
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Processor::createEditor() {
    return new Editor (*this);
}

//==============================================================================
void Processor::getStateInformation (juce::MemoryBlock& destData)
{
    juce::ignoreUnused (destData);
}

void Processor::setStateInformation (const void* data, int sizeInBytes)
{

    initParameters();
}


void Processor::initParameters() {
    for (size_t i = 0; i < N_PARAMS; i++) {
        parameterChanged(ParamIDs[i].toString(), 
                         *apvts.getRawParameterValue(ParamIDs[i]));
    }
}


void Processor::parameterChanged(const juce::String &parameterId, float newValue) {
    
    const auto id = juce::Identifier(parameterId);

    if (id == ParamIDs[GAIN]) {
        gain.newTarget(scale(newValue, 0.0f, 10.0f, (float)dbtoa(0.0), (float)dbtoa(40.0), 2.0f), 
                       SMOOTH_PARAM_TIME, samplerate);
        return;
    }
    
    if (id == ParamIDs[LOW_BOOST] || id == ParamIDs[LOW_FREQ]) {
        float freq = *apvts.getRawParameterValue(ParamIDs[LOW_FREQ]);
        float amplitude_dB = *apvts.getRawParameterValue(ParamIDs[LOW_BOOST]); 
        
        lowFilter.setCoefficients(freq, FILTER_Q, amplitude_dB, upSamplerate);
        return;
    }
    
    if (id == ParamIDs[HIGH_BOOST] || id == ParamIDs[HIGH_FREQ]) {
        float freq = *apvts.getRawParameterValue(ParamIDs[HIGH_FREQ]);
        float amplitude_dB = *apvts.getRawParameterValue(ParamIDs[HIGH_BOOST]); 
        
        highFilter1.setCoefficients(freq, FILTER_Q, amplitude_dB, upSamplerate);
        return;
    }
    
    if (id == ParamIDs[OUT_VOLUME]) {
        volume.newTarget(dbtoa(newValue), SMOOTH_PARAM_TIME, samplerate);
        return;
    }
    
    if (id == ParamIDs[CHANNEL_CONFIG]) {
        channelConfig = (ChannelConfig)newValue;
        return;
    }
}


juce::AudioProcessorValueTreeState::ParameterLayout Processor::createParameterLayout() {

    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    auto attributes = juce::AudioParameterFloatAttributes()
                        .withStringFromValueFunction ([] (auto x, auto) { return juce::String (x, 1); });

    params.push_back(std::make_unique<juce::AudioParameterFloat>(
                    ParamIDs[GAIN].toString(), "GAIN", 
                    juce::NormalisableRange<float>(0.0f, 10.0f, 0.01f, 1.0f), 5.0f, attributes
    ));
                    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
                    ParamIDs[LOW_BOOST].toString(), "LOW_BOOST", 
                    juce::NormalisableRange<float>(0.0f, 25.0f, 0.1f, 1.0f), 15.0f, attributes
    ));
                    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
                    ParamIDs[LOW_FREQ].toString(), "LOW_FREQ", 
                    juce::NormalisableRange<float>(50.0f, 100.0f, 0.1f, 1.0f), 80.0f, attributes
    ));
                    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
                    ParamIDs[HIGH_BOOST].toString(), "HIGH_BOOST", 
                    juce::NormalisableRange<float>(0.0f, 25.0f, 0.1f, 1.0f), 15.0f, attributes
    ));
                    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
                    ParamIDs[HIGH_FREQ].toString(), "HIGH_FREQ", 
                    juce::NormalisableRange<float>(800.0f, 1500.0f, 1.0f, 1.0f), 1200.0f, attributes
    ));
                    
    params.push_back(std::make_unique<juce::AudioParameterFloat>(
                    ParamIDs[OUT_VOLUME].toString(), "OUT_VOLUME", 
                    juce::NormalisableRange<float>(-60.0f, 0.0f, 0.1f, 1.0f), -3.0f, attributes
    ));
                    
    params.push_back(std::make_unique<juce::AudioParameterChoice>(
                    ParamIDs[CHANNEL_CONFIG].toString(), "Channel config", 
                    juce::StringArray{"Mono", "Fake Stereo", "Stereo"}, 0
    ));

    return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Processor();
}
