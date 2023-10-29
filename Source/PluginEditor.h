#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "BinaryData.h"
#include "Component/HorizontalMeter.h"

//==============================================================================


class SacredTrinityVerbAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Slider::Listener, public juce::Timer
{
public:
    SacredTrinityVerbAudioProcessorEditor(SacredTrinityVerbAudioProcessor&);
    ~SacredTrinityVerbAudioProcessorEditor() override;

    //==============================================================================

    void timerCallback() override;

    void paint(juce::Graphics&) override;
    void resized() override;


    void loadIRbinary(const char* resourceName, int dataSizeInBytes, size_t resourceSize);
    void sliderValueChanged(juce::Slider* slider);

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    


private:
    SacredTrinityVerbAudioProcessor& audioProcessor;
    juce::ComboBox irMenu;
    
    
    juce::Slider gainSlider;
    std::unique_ptr<SliderAttachment> gainSliderAttachment;
    juce::Label gainLabel;

    juce::Slider mixSlider;
    std::unique_ptr<SliderAttachment> mixSliderAttachment;
    juce::Label mixLabel;
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    std::unique_ptr<ComboBoxAttachment> irMenuAttachment;

    // for metering
    Gui::HorizontalMeter horizontalMeterL, horizontalMeterR;



    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SacredTrinityVerbAudioProcessorEditor)
};
