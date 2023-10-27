#include "PluginProcessor.h"
#include "PluginEditor.h"




//==============================================================================
SacredTrinityVerbAudioProcessorEditor::SacredTrinityVerbAudioProcessorEditor(SacredTrinityVerbAudioProcessor& p)
                                            : AudioProcessorEditor(&p), 
                                              audioProcessor(p)
{
    

    addAndMakeVisible(gainSlider);
    gainSlider.setSliderStyle(juce::Slider::SliderStyle::LinearVertical);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 200, 25);
    gainSlider.setTextValueSuffix(" dB");
    gainSlider.setRange(-48.0f, 0.0f);
    gainSlider.setNumDecimalPlacesToDisplay(1);
    gainSlider.setValue(-10.0f);
    gainSlider.addListener(this);
    
    
    addAndMakeVisible(gainLabel);
    gainLabel.attachToComponent(&gainSlider, false);
    gainLabel.setText("Gain", juce::dontSendNotification);

    gainSliderAttachment = std::make_unique<SliderAttachment>(audioProcessor.treeState, "GAIN", gainSlider);
    

    addAndMakeVisible(irMenu);
    // TO DO - create a funtion fot this lot
    irMenu.addItem("Main Hall 2m", 1);
    irMenu.addItem("Main Hall 4m", 2);
    irMenu.addItem("Main Hall 5m", 3);
    irMenu.addItem("Main Hall 9m", 4);
    irMenu.addItem("Small Room 2m", 5);
    irMenu.addItem("Balcony 3m", 6);
    irMenu.addItem("Balcony 6m", 7);

    //irMenuAttachment = std::make_unique<ComboBoxAttachment>(audioProcessor.treeState, "IRMENU", irMenu);

    irMenu.onChange = [this]
        {  
            int selectedId = irMenu.getSelectedId();
            
     
            switch (selectedId)
            {
            case 1:

                loadIRbinary("main_hall_2m_wav", BinaryData::main_hall_2m_wavSize, BinaryData::main_hall_2m_wavSize);
                break;
            case 2:
                loadIRbinary("main_hall_4m_wav", BinaryData::main_hall_4m_wavSize, BinaryData::main_hall_4m_wavSize);
                break;
            case 3:
                loadIRbinary("main_hall_5m_wav", BinaryData::main_hall_5m_wavSize, BinaryData::main_hall_5m_wavSize);
                break;
            case 4:
                loadIRbinary("main_hall_9m_wav", BinaryData::main_hall_9m_wavSize, BinaryData::main_hall_9m_wavSize);
                break;
            case 5:
                loadIRbinary("small_room_2m_wav", BinaryData::small_room_2m_wavSize, BinaryData::small_room_2m_wavSize);
                break;
            case 6:
                loadIRbinary("balcony_3m_wav", BinaryData::balcony_3m_wavSize, BinaryData::balcony_3m_wavSize);
                break;
            case 7:
                loadIRbinary("balcony_6m_wav", BinaryData::balcony_6m_wavSize, BinaryData::balcony_6m_wavSize);
                break;
            default:
                break;
            }
        };
    

    // level meter
    addAndMakeVisible(horizontalMeterL);
    addAndMakeVisible(horizontalMeterR);
    startTimerHz(24);


    setSize (600, 600);
}





SacredTrinityVerbAudioProcessorEditor::~SacredTrinityVerbAudioProcessorEditor()
{
}

void SacredTrinityVerbAudioProcessorEditor::timerCallback()
{
    horizontalMeterL.setLevel(audioProcessor.getRMSValue(0));
    horizontalMeterR.setLevel(audioProcessor.getRMSValue(1));
    horizontalMeterL.repaint();
    horizontalMeterR.repaint();
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

    const auto gsX = getWidth() * JUCE_LIVE_CONSTANT(0.06);
    const auto gsY = getHeight()* JUCE_LIVE_CONSTANT(0.25);
    const auto gsW = getWidth() * JUCE_LIVE_CONSTANT(0.12);
    const auto gsH = getHeight() * JUCE_LIVE_CONSTANT(0.30);
    gainSlider.setBounds(gsX,gsY,gsW,gsH);

    // level meter
    horizontalMeterL.setBounds(100, 400, 200, 15);
    horizontalMeterR.setBounds(100, 420, 200, 15);

}

// IR Binary loader

void SacredTrinityVerbAudioProcessorEditor::loadIRbinary(const char* resourceName, int dataSizeInBytes, size_t resourceSize )
{
    const void* sourceData =  BinaryData::getNamedResource(resourceName, dataSizeInBytes);

    audioProcessor.irLoader.reset(); // clears the buffer for next ir file
    audioProcessor.irLoader.loadImpulseResponse(sourceData, resourceSize, juce::dsp::Convolution::Stereo::yes, juce::dsp::Convolution::Trim::yes, 0, juce::dsp::Convolution::Normalise::yes);

}

// gain too decibels

void SacredTrinityVerbAudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &gainSlider)
    {
        audioProcessor.rawVolume = pow(10, gainSlider.getValue() / 20);
    }
}

