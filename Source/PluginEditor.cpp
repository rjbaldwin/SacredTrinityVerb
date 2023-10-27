#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SacredTrinityVerbAudioProcessorEditor::SacredTrinityVerbAudioProcessorEditor(SacredTrinityVerbAudioProcessor& p)
                                            : AudioProcessorEditor(&p), 
                                              audioProcessor(p)
{
    



    addAndMakeVisible(irMenu);
    // TO DO - create a funtion fot this lot
    irMenu.addItem("Main Hall 2m", 1);
    irMenu.addItem("Main Hall 4m", 2);
    irMenu.addItem("Main Hall 5m", 3);
    irMenu.addItem("Main Hall 9m", 4);
    irMenu.addItem("Small Room 2m", 5);
    irMenu.addItem("Balcony 3m", 6);
    irMenu.addItem("Balcony 6m", 7);
    irMenu.onChange = [this]
        {  
            int selectedId = irMenu.getSelectedId();

            switch (selectedId)
            {
            case 1:
                loadIR("Main_Hall_2m.wav");
                break;
            case 2:
                loadIR("Main_Hall_4m.wav");
                break;
            case 3:
                loadIR("Main_Hall_5m.wav");
                break;
            case 4:
                loadIR("Main_Hall_9m.wav");
                break;
            case 5:
                loadIR("Small_Room_2m.wav");
                break;
            case 6:
                loadIR("Balcony_3m.wav");
                break;
            case 7:
                loadIR("Balcony_6m.wav");
                break;
            default:
                break;
            }
        };
    


    setSize (600, 600);
}





SacredTrinityVerbAudioProcessorEditor::~SacredTrinityVerbAudioProcessorEditor()
{
}

//==============================================================================
void SacredTrinityVerbAudioProcessorEditor::paint(juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText ("Sacred Trinityverb V1 - RJBaldwin", getLocalBounds(), juce::Justification::centredTop, 1);
}

void SacredTrinityVerbAudioProcessorEditor::resized()
{
    // these live constants are a lifesaver.  Swap them out for actual values once gui has taken shape! 

    // combo box
    const auto irComboX = getWidth() * JUCE_LIVE_CONSTANT(0.25);
    const auto irComboY = getHeight() * 0.15; // JUCE_LIVE_CONSTANT(0.5); //0.15
    const auto irComboWidth = getWidth() * JUCE_LIVE_CONSTANT(0.25);
    const auto irComboHeight = getHeight() * 0.06; //JUCE_LIVE_CONSTANT(0.5); // 0.06

    irMenu.setBounds(irComboX, irComboY, irComboWidth, irComboHeight);

}

// IR loader
void SacredTrinityVerbAudioProcessorEditor::loadIR(juce::String fileName)
{

    auto file = juce::File::getCurrentWorkingDirectory().getChildFile(fileName);

    DBG("Looking for file at: " << file.getFullPathName());

    if (file.existsAsFile()) {
        DBG("File found: " << file.getFullPathName());

        audioProcessor.irLoader.reset(); // clears the buffer for next ir file
        audioProcessor.irLoader.loadImpulseResponse(file, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
    }
    else {
        DBG("Error: File not found!");
    }
}

