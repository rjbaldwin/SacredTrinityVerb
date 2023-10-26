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
    std::unique_ptr<juce::FileChooser> fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SacredTrinityVerbAudioProcessorEditor)
};
