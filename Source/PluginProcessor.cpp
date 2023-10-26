// R J Baldwin - Project started 26/10/2023
// Sacred Trinity Church Reverb plugin.
// This plugin uses impulse responses that I gather with my third year BAMP students 
// from Sacred Trinity Church in Salford, Greater Manchester.  There are 3 main rooms that we produce impulse responses of.
// Thanks to Rev Andy Salmon for allowing in to do this for the past 10 years in a row!
// This is my third piece of proper software ever! 

#include "PluginProcessor.h"
#include "PluginEditor.h"


//==============================================================================
SacredTrinityVerbAudioProcessor::SacredTrinityVerbAudioProcessor()
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
{
}

SacredTrinityVerbAudioProcessor::~SacredTrinityVerbAudioProcessor()
{
}

//==============================================================================
const juce::String SacredTrinityVerbAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SacredTrinityVerbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SacredTrinityVerbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SacredTrinityVerbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SacredTrinityVerbAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SacredTrinityVerbAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SacredTrinityVerbAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SacredTrinityVerbAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String SacredTrinityVerbAudioProcessor::getProgramName (int index)
{
    return {};
}

void SacredTrinityVerbAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void SacredTrinityVerbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    spec.maximumBlockSize = samplesPerBlock;
    spec.sampleRate = sampleRate;
    spec.numChannels = getTotalNumInputChannels();

    irLoader.reset();
    irLoader.prepare(spec);
}

void SacredTrinityVerbAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SacredTrinityVerbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void SacredTrinityVerbAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    juce::dsp::AudioBlock<float>block{ buffer };

    // for IR loader
    if (irLoader.getCurrentIRSize() > 0)
    {
        irLoader.process(juce::dsp::ProcessContextReplacing<float>(block));
    }
}

//==============================================================================
bool SacredTrinityVerbAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* SacredTrinityVerbAudioProcessor::createEditor()
{
    return new SacredTrinityVerbAudioProcessorEditor (*this);
}

//==============================================================================
void SacredTrinityVerbAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void SacredTrinityVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SacredTrinityVerbAudioProcessor();
}
