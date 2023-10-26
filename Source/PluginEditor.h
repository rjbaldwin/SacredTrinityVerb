#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================


class SacredTrinityVerbAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    SacredTrinityVerbAudioProcessorEditor(SacredTrinityVerbAudioProcessor&);
    ~SacredTrinityVerbAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;

private:
    SacredTrinityVerbAudioProcessor& audioProcessor;

    juce::TextButton loadBtn;
    juce::ComboBox irMenu;
    juce::TextButton hall2m, hall4m, hall5m, hall9m, smallRoom, balcony3m, balcony6m;


    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SacredTrinityVerbAudioProcessorEditor)
};
