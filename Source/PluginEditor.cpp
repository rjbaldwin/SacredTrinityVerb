#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SacredTrinityVerbAudioProcessorEditor::SacredTrinityVerbAudioProcessorEditor(SacredTrinityVerbAudioProcessor& p)
                                            : AudioProcessorEditor(&p), 
                                              audioProcessor(p)
{
    
    addAndMakeVisible(loadBtn);
    loadBtn.setButtonText("Load IR");
    loadBtn.onClick = [this]()
        {
            fileChooser = std::make_unique<juce::FileChooser>("Choose IR", audioProcessor.root, "*");
            const auto fileChooserFlags = juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::canSelectDirectories;

            fileChooser->launchAsync(fileChooserFlags, [this](const juce::FileChooser& chooser)
                {
                    juce::File result(chooser.getResult());

                    if (result.getFileExtension() == ".wav" || result.getFileExtension() == ".aif")
                    {
                        audioProcessor.savedFile = result;
                        audioProcessor.root = result.getParentDirectory().getFullPathName();
                        audioProcessor.irLoader.reset(); // clears the buffer for next ir file
                        audioProcessor.irLoader.loadImpulseResponse(result, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0);
                    }
                });
        };


    addAndMakeVisible(irMenu);
    // TO DO - create a funtion fot this lot
    irMenu.addItem("Main Hall 2m", 1);
    irMenu.addItem("Main Hall 4m", 2);
    irMenu.addItem("Main Hall 5m", 3);
    irMenu.addItem("Main Hall 9m", 4);
    irMenu.addItem("Small Room 2m", 5);
    irMenu.addItem("Balcony 3m", 6);
    irMenu.addItem("Balcony 6m", 7);
    irMenu.onChange = [this] {  };
    //irMenu.setSelectedId(1);


    setSize (800, 600);
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

    // load button
    const auto btnX =       getWidth() * JUCE_LIVE_CONSTANT(0.25);
    const auto btnY =       getHeight() * JUCE_LIVE_CONSTANT(0.5);
    const auto btnWidth =   getWidth() * JUCE_LIVE_CONSTANT(0.1);
    const auto btnHeight =  btnWidth * 0.5;

    loadBtn.setBounds(btnX, btnY, btnWidth, btnHeight);

    // combo box
    const auto irComboX = getWidth() * JUCE_LIVE_CONSTANT(0.25);
    const auto irComboY = getHeight() * 0.15; // JUCE_LIVE_CONSTANT(0.5); //0.15
    const auto irComboWidth = getWidth() * JUCE_LIVE_CONSTANT(0.25);
    const auto irComboHeight = getHeight() * 0.06; //JUCE_LIVE_CONSTANT(0.5); // 0.06

    irMenu.setBounds(irComboX, irComboY, irComboWidth, irComboHeight);

}



