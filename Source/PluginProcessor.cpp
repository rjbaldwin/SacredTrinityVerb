// R J Baldwin - Project started 26/10/2023
// Sacred Trinity Church Reverb plugin.
// This plugin uses impulse responses that I gather with my third year BAMP students 
// from Sacred Trinity Church in Salford, Greater Manchester.  There are 3 main rooms that we produce impulse responses of.
// Thanks to Rev Andy Salmon for allowing me to do this for the past 10 years in a row!
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
                       ),
    treeState{ *this,nullptr,"PARAMETERS", createParameterLayout() }

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

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            channelData[sample] = buffer.getSample(channel, sample) * rawVolume;
        }
    }

    rmsLevelLeft = juce::Decibels::gainToDecibels(buffer.getRMSLevel(0, 0, buffer.getNumSamples()));
    rmsLevelRight = juce::Decibels::gainToDecibels(buffer.getRMSLevel(1, 0, buffer.getNumSamples()));

    
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
    auto state = treeState.copyState();
    std::unique_ptr<juce::XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);
}

void SacredTrinityVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(treeState.state.getType()))
           treeState.replaceState(juce::ValueTree::fromXml(*xmlState));
}


juce::AudioProcessorValueTreeState::ParameterLayout SacredTrinityVerbAudioProcessor::createParameterLayout()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    auto gainParam = std::make_unique<juce::AudioParameterFloat>("GAIN", "Gain", -48.0f, 0.0f, -10.0f);
    params.push_back(std::move(gainParam));

    return { params.begin(), params.end() };
}

void SacredTrinityVerbAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{

}

float SacredTrinityVerbAudioProcessor::getRMSValue(const int channel) const
{
    jassert(channel == 0 || channel == 1);
    if (channel == 0)
        return rmsLevelLeft;
    if (channel == 1)
        return rmsLevelRight;
    return 0.f;
}







//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SacredTrinityVerbAudioProcessor();
}
