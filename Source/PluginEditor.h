#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "BinaryData.h"

//==============================================================================


class SacredTrinityVerbAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener
{
public:
    SacredTrinityVerbAudioProcessorEditor(SacredTrinityVerbAudioProcessor&);
    ~SacredTrinityVerbAudioProcessorEditor() override;

    //==============================================================================
    void paint(juce::Graphics&) override;
    void resized() override;


    void loadIRbinary(const char* resourceName, int dataSizeInBytes, size_t resourceSize);
    void sliderValueChanged(juce::Slider* slider);

private:
    SacredTrinityVerbAudioProcessor& audioProcessor;
    juce::ComboBox irMenu;
    std::unique_ptr<juce::FileChooser> fileChooser;
    juce::Slider gainSlider;
    juce::Label gainLabel;
    



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SacredTrinityVerbAudioProcessorEditor)
};
