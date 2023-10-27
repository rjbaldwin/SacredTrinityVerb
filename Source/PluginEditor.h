#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "BinaryData.h"

//==============================================================================


class SacredTrinityVerbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SacredTrinityVerbAudioProcessorEditor(SacredTrinityVerbAudioProcessor&);
    ~SacredTrinityVerbAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;


    void loadIRbinary(const char* resourceName, int dataSizeInBytes, size_t resourceSize);

private:
    SacredTrinityVerbAudioProcessor& audioProcessor;

    juce::ComboBox irMenu;



    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SacredTrinityVerbAudioProcessorEditor)
};
