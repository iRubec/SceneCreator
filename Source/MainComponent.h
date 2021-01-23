/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <fftw3.h>

#include "Artist.h"
#include "Sphere.h"
#include "resources/ambisonicTools.h"
#include "resources/AmbisonicDecoder.h"

#define sqrt4PI  3.544907701811032
#define JUCE_ASIO 1

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class MainComponent : public AudioAppComponent,
                      public Slider::Listener,
                      public Button::Listener,
                      private MidiInputCallback,
                      private MidiKeyboardStateListener,
                      private Timer
{
public:
    //============================================================================
    MainComponent(var info);
    ~MainComponent();

    //==============================================================================
    void prepareToPlay(int samplesPerBlockExpected, double newSampleRate) override;
    void getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill) override;
    void releaseResources() override;
    void sliderValueChanged(Slider* slider) override;
    void buttonClicked(Button* button) override;
    void buttonStateChanged(Button* button) override;
    void timerCallback() override;

    //==============================================================================
    void parser(var info);
    void saveFile();
    void update();
    void openPopup();
    //void selectHeadphoneEQ(int newValue);
    Colour colourSelector(int colourId);

    //==============================================================================
    void paint(Graphics& g) override;
    void resized() override;

    // Armónicos esféricos de Ambisonics de tercer orden
    void SHEval3(const float fX, const float fY, const float fZ, float* pSH)
    {
        float fC0, fC1, fS0, fS1, fTmpA, fTmpB, fTmpC;
        float fZ2 = fZ * fZ;

        pSH[0] = 0.2820947917738781f;
        pSH[2] = 0.4886025119029199f * fZ;
        pSH[6] = 0.9461746957575601f * fZ2 + -0.31539156525252f;
        pSH[12] = fZ * (1.865881662950577f * fZ2 + -1.119528997770346f);
        fC0 = fX;
        fS0 = fY;

        fTmpA = 0.48860251190292f;
        pSH[3] = fTmpA * fC0;
        pSH[1] = fTmpA * fS0;
        fTmpB = 1.092548430592079f * fZ;
        pSH[7] = fTmpB * fC0;
        pSH[5] = fTmpB * fS0;
        fTmpC = 2.285228997322329f * fZ2 + -0.4570457994644658f;
        pSH[13] = fTmpC * fC0;
        pSH[11] = fTmpC * fS0;
        fC1 = fX * fC0 - fY * fS0;
        fS1 = fX * fS0 + fY * fC0;

        fTmpA = 0.5462742152960395f;
        pSH[8] = fTmpA * fC1;
        pSH[4] = fTmpA * fS1;
        fTmpB = 1.445305721320277f * fZ;
        pSH[14] = fTmpB * fC1;
        pSH[10] = fTmpB * fS1;
        fC0 = fX * fC1 - fY * fS1;
        fS0 = fX * fS1 + fY * fC1;

        fTmpC = 0.5900435899266435f;
        pSH[15] = fTmpC * fC0;
        pSH[9] = fTmpC * fS0;
    };

    //constexpr float decodeCorrection(const int N) { return sqrt4PI / (N + 1) / (N + 1); };

    // Lector de mensajes MIDI
    void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override
    {
        const ScopedValueSetter<bool> scopedInputFlag(isAddingFromMidiInput, true);
        const MessageManagerLock mmLock;
        if (message.isController())
        {
            midiMove(message.getNoteNumber(), message.getControllerValue());
        }
        else if (message.isNoteOn())
        {
            midiButton(message.getNoteNumber());
        };

    };

    void handleNoteOn(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float velocity) override {};
    void handleNoteOff(MidiKeyboardState*, int midiChannel, int midiNoteNumber, float /*velocity*/) override {};

    void midiButton(float noteNumber)
    {
        Array<SpherePanner::MyElement*> myElements = sphere.getMyElements();

        if (elements >= 1)
        {
            switch ((int)noteNumber) {
            case 1:
                myElements[0]->setActive(muteButtons[0]->getToggleState());
                muteButtons[0]->setToggleState(!muteButtons[0]->getToggleState(), dontSendNotification);
                break;
            case 3:
                myElements[0]->setActive(true);
                soloButtons[0]->setToggleState(!soloButtons[0]->getToggleState(), dontSendNotification);
                for (int i = 0; i < elements; i++) {
                    if (i != 0) {
                        muteButtons[i]->setToggleState(soloButtons[0]->getToggleState(), dontSendNotification);
                        myElements[i]->setActive(!soloButtons[0]->getToggleState());
                    }
                }
                break;
            default:
                break;
            };
        };

        if (elements >= 2)
        {
            switch ((int)noteNumber) {
            case 4:
                myElements[1]->setActive(muteButtons[1]->getToggleState());
                muteButtons[1]->setToggleState(!muteButtons[1]->getToggleState(), dontSendNotification);
                break;
            case 6:
                myElements[1]->setActive(true);
                soloButtons[1]->setToggleState(!soloButtons[1]->getToggleState(), dontSendNotification);
                for (int i = 0; i < elements; i++) {
                    if (i != 1) {
                        muteButtons[i]->setToggleState(soloButtons[1]->getToggleState(), dontSendNotification);
                        myElements[i]->setActive(!soloButtons[1]->getToggleState());
                    }
                }
                break;
            default:
                break;
            };
        };

        if (elements >= 3)
        {
            switch ((int)noteNumber) {
            case 7:
                myElements[2]->setActive(muteButtons[2]->getToggleState());
                muteButtons[2]->setToggleState(!muteButtons[2]->getToggleState(), dontSendNotification);
                break;
            case 9:
                myElements[2]->setActive(true);
                soloButtons[2]->setToggleState(!soloButtons[2]->getToggleState(), dontSendNotification);
                for (int i = 0; i < elements; i++) {
                    if (i != 2) {
                        muteButtons[i]->setToggleState(soloButtons[2]->getToggleState(), dontSendNotification);
                        myElements[i]->setActive(!soloButtons[2]->getToggleState());
                    }
                }
                break;
            default:
                break;
            };
        };

        if (elements >= 4)
        {
            switch ((int)noteNumber) {
            case 10:
                myElements[3]->setActive(muteButtons[3]->getToggleState());
                muteButtons[3]->setToggleState(!muteButtons[3]->getToggleState(), dontSendNotification);
                break;
            case 12:
                myElements[3]->setActive(true);
                soloButtons[3]->setToggleState(!soloButtons[3]->getToggleState(), dontSendNotification);
                for (int i = 0; i < elements; i++) {
                    if (i != 3) {
                        muteButtons[i]->setToggleState(soloButtons[3]->getToggleState(), dontSendNotification);
                        myElements[i]->setActive(!soloButtons[3]->getToggleState());
                    }
                }
                break;
            default:
                break;
            };
        };

        if (elements >= 5)
        {
            switch ((int)noteNumber) {
            case 13:
                myElements[4]->setActive(muteButtons[4]->getToggleState());
                muteButtons[4]->setToggleState(!muteButtons[4]->getToggleState(), dontSendNotification);
                break;
            case 15:
                myElements[4]->setActive(true);
                soloButtons[4]->setToggleState(!soloButtons[4]->getToggleState(), dontSendNotification);
                for (int i = 0; i < elements; i++) {
                    if (i != 4) {
                        muteButtons[i]->setToggleState(soloButtons[4]->getToggleState(), dontSendNotification);
                        myElements[i]->setActive(!soloButtons[4]->getToggleState());
                    }
                }
                break;
            default:
                break;
            };
        };

        if (elements >= 6)
        {
            switch ((int)noteNumber) {
            case 16:
                myElements[5]->setActive(muteButtons[5]->getToggleState());
                muteButtons[5]->setToggleState(!muteButtons[5]->getToggleState(), dontSendNotification);
                break;
            case 18:
                myElements[5]->setActive(true);
                soloButtons[5]->setToggleState(!soloButtons[5]->getToggleState(), dontSendNotification);
                for (int i = 0; i < elements; i++) {
                    if (i != 5) {
                        muteButtons[i]->setToggleState(soloButtons[5]->getToggleState(), dontSendNotification);
                        myElements[i]->setActive(!soloButtons[5]->getToggleState());
                    }
                }
                break;
            default:
                break;
            };
        };

        if (elements >= 7)
        {
            switch ((int)noteNumber) {
            case 19:
                myElements[6]->setActive(muteButtons[6]->getToggleState());
                muteButtons[6]->setToggleState(!muteButtons[6]->getToggleState(), dontSendNotification);
                break;
            case 21:
                myElements[6]->setActive(true);
                soloButtons[6]->setToggleState(!soloButtons[6]->getToggleState(), dontSendNotification);
                for (int i = 0; i < elements; i++) {
                    if (i != 6) {
                        muteButtons[i]->setToggleState(soloButtons[6]->getToggleState(), dontSendNotification);
                        myElements[i]->setActive(!soloButtons[6]->getToggleState());
                    }
                }
                break;
            default:
                break;
            };
        };

        if (elements >= 8)
        {
            switch ((int)noteNumber) {
            case 22:
                myElements[7]->setActive(muteButtons[7]->getToggleState());
                muteButtons[7]->setToggleState(!muteButtons[7]->getToggleState(), dontSendNotification);
                break;
            case 24:
                myElements[7]->setActive(true);
                soloButtons[7]->setToggleState(!soloButtons[7]->getToggleState(), dontSendNotification);
                for (int i = 0; i < elements; i++) {
                    if (i != 7) {
                        muteButtons[i]->setToggleState(soloButtons[7]->getToggleState(), dontSendNotification);
                        myElements[i]->setActive(!soloButtons[7]->getToggleState());
                    }
                }
                break;
            default:
                break;
            };
        };

        sphere.repaint();

    }

    void midiMove(float noteNumber, int velocity)
    {
        //float div = 361.0/128;
        float div = 2.83465;
        float divGain = 1/12.1;
        if (elements >= 1) {
            switch ((int)noteNumber) {
            case 16:
                azimutSliders[0]->setValue(velocity * div);
                break;
            case 17:
                elevationSliders[0]->setValue(velocity * div);
                break;
            case 18:
                gainSliders[0]->setValue(velocity * divGain + 1.5);
                break;
            default:
                break;
            };
        };
        if (elements >= 2) {
            switch ((int)noteNumber) {
            case 20:
                azimutSliders[1]->setValue(velocity * div);
                break;
            case 21:
                elevationSliders[1]->setValue(velocity * div);
                break;
            case 22:
                gainSliders[1]->setValue(velocity * divGain + 1.5);
                break;
            default:
                break;
            };
        };
        if (elements >= 3) {
            switch ((int)noteNumber) {
            case 24:
                azimutSliders[2]->setValue(velocity * div);
                break;
            case 25:
                elevationSliders[2]->setValue(velocity * div);
                break;
            case 26:
                gainSliders[2]->setValue(velocity * divGain + 1.5);
                break;
            default:
                break;
            };
        };
        if (elements >= 4) {
            switch ((int)noteNumber) {
            case 28:
                azimutSliders[3]->setValue(velocity * div);
                break;
            case 29:
                elevationSliders[3]->setValue(velocity * div);
                break;
            case 30:
                gainSliders[3]->setValue(velocity * divGain + 1.5);
                break;
            default:
                break;
            };
        };
        if (elements >= 5) {
            switch ((int)noteNumber) {
            case 46:
                azimutSliders[4]->setValue(velocity * div);
                break;
            case 47:
                elevationSliders[4]->setValue(velocity * div);
                break;
            case 48:
                gainSliders[4]->setValue(velocity * divGain + 1.5);
                break;
            default:
                break;
            };
        };
        if (elements >= 6) {
            switch ((int)noteNumber) {
            case 50:
                azimutSliders[5]->setValue(velocity * div);
                break;
            case 51:
                elevationSliders[5]->setValue(velocity * div);
                break;
            case 52:
                gainSliders[5]->setValue(velocity * divGain + 1.5);
                break;
            default:
                break;
            };
        };
        if (elements >= 7) {
            switch ((int)noteNumber) {
            case 54:
                azimutSliders[6]->setValue(velocity * div);
                break;
            case 55:
                elevationSliders[6]->setValue(velocity * div);
                break;
            case 56:
                gainSliders[6]->setValue(velocity * divGain + 1.5);
                break;
            default:
                break;
            };
        };
        if (elements >= 8) {
            switch ((int)noteNumber) {
            case 58:
                azimutSliders[7]->setValue(velocity * div);
                break;
            case 59:
                elevationSliders[7]->setValue(velocity * div);
                break;
            case 60:
                gainSliders[7]->setValue(velocity * divGain + 1.5);
                break;
            default:
                break;
            };
        };

        sphere.repaint();

    }

    //static const StringArray headphoneEQs;
    static constexpr int maxNumberOfInputs = 8;
    static constexpr int startNnumberOfInputs = 5;

    constexpr static int numberOfInputChannels = 64;
    constexpr static int numberOfOutputChannels = 2;

private:

    //==============================================================================

    struct Header : public Component
    {
        Header()
        {
        }
        void paint(Graphics& g) override
        {
            g.setColour(Colours::lightgrey);
            g.drawRect(getLocalBounds());
            g.setColour(Colours::white);
            g.setFont(15.0f);
            g.drawText(outputInfo, 10, 5, 450, getHeight() / 3, Justification::left);
            g.drawText(midiInfo, 10, getHeight() / 3 + 3, 150, getHeight() / 3, Justification::left);
            g.drawText(cpuInfo, 10, 2 * getHeight() / 3, 250, getHeight() / 3, Justification::left);
            g.setFont(25.0f);
            g.drawText("SONORIZARTE SCENE RECREATOR", 0, 0, getWidth(), getHeight(), Justification::centred);
        }

        void resized() override
        {
        }

        void setInfo(int num, String info)
        {
            switch (num)
            {
            case 1:
                outputInfo = "Output : " + info;
                break;
            case 2:
                midiInfo = "MIDI Mix: " + info;
                break;
            case 3:
                cpuInfo = "CPU usage: " + info;
                break;
            default:
                break;
            }
            repaint();
        }

        String midiInfo = "", outputInfo = "", cpuInfo = "";

    };

    struct MainPanel : public Component
    {
        MainPanel()
        {

        }
        void paint(Graphics& g) override
        {
            g.setColour(Colours::lightgrey);
            g.drawRect(getLocalBounds());
        }

        void resized() override
        {
        }
    };

    struct Demode : public Component
    {
        Demode()
        {

            seeArtists.setName("Tracks");
            seeArtists.setButtonText("T\nR\nA\nC\nK\nS");
            seeArtists.setRadioGroupId(1, dontSendNotification);
            seeArtists.setToggleState(true, dontSendNotification);
            seeArtists.onClick = [this]
            { 
                seeSetup.setToggleState(false, dontSendNotification);
                seeArtists.setToggleState(true, dontSendNotification);
                
                const Array<Component*> cs = getChildren();

                for (int i = 0; i < cs.size(); i++)
                {
                    String name = cs[i]->getName();
                    if (name == "Tracks" || name == "Setup") {}
                    else
                    {
                        if (name == "")
                        {
                            Component* c = getChildComponent(getIndexOfChildComponent(cs[i]));
                            c->setVisible(false);
                        }
                        else
                        {
                            Component* c = getChildComponent(getIndexOfChildComponent(cs[i]));
                            c->setVisible(true);
                        }
                    };

                }
                isTracks = true;
               
            };
            addAndMakeVisible(seeArtists);

            seeSetup.setName("Setup");
            seeSetup.setButtonText("S\nE\nT\nU\nP");
            seeSetup.setRadioGroupId(1, dontSendNotification);
            seeSetup.onClick = [this] 
            {
                seeSetup.setToggleState(true, dontSendNotification);
                seeArtists.setToggleState(false, dontSendNotification);
                
                const Array<Component*> cs = getChildren();

                for (int i = 0; i < cs.size(); i++)
                {
                    String name = cs[i]->getName();
                    if (name == "Tracks" || name == "Setup") {}
                    else
                    {
                        if (name == "")
                        {
                            Component* c = getChildComponent(getIndexOfChildComponent(cs[i]));
                            c->setVisible(true);
                        }
                        else
                        {
                            Component* c = getChildComponent(getIndexOfChildComponent(cs[i]));
                            c->setVisible(false);
                        }
                    };
                    
                }
                
                isTracks = false;
                
            };
            addAndMakeVisible(seeSetup);

        }
        void paint(Graphics& g) override
        {
            g.setColour(Colours::lightgrey);
            g.drawRect(getLocalBounds());
            
            int W = getWidth()-30;
            int H = getHeight();
            seeArtists.setBounds(W, 0, 30, H / 2);
            seeSetup.setBounds(W, H / 2, 30, H / 2);

            elements = artists.size();

            if (isTracks)
            {
                for (int i = 0; i < artists.size(); i++)
                {
                    g.setColour(Colours::lightgrey);

                    if (elements <= 4) {
                        g.drawRect(0, i * (H / 4), W, H / 4);
                        g.setFont(15.0f);
                        g.drawText("AZ", (W - 20) / 4, i * (H / 4) + H / 8 - 10, (W - 20) / 4, 10, Justification::centred);
                        g.drawText("EL", 2 * (W - 20) / 4, i * (H / 4) + H / 8 - 10, (W - 20) / 4, 10, Justification::centred);
                        g.drawText("R", 3 * (W - 20) / 4, i * (H / 4) + H / 8 - 10, (W - 20) / 4, 10, Justification::centred);
                        g.drawImageWithin(artists[i]->getIcon(), 10, i * (H / 4) + 10, (W - 20) / 4, H / 4 - 20, 1, false);
                        g.setFont(20.0f);
                        g.setColour(artists[i]->getColour());
                        g.drawText(artists[i]->getName(), 0, i * (H / 4), W, 22, Justification::centred);
                    }
                    else
                    {
                        g.drawRect(0, i * (H / elements), W, H / elements);
                        g.setFont(60.0f / elements);
                        g.drawText("AZ", (W - 20) / 4, i * (H / elements) + H / (elements * 2) - 60 / elements, (W - 20) / 4, 10, Justification::centred);
                        g.drawText("EL", 2 * (W - 20) / 4, i * (H / elements) + H / (elements * 2) - 60 / elements, (W - 20) / 4, 10, Justification::centred);
                        g.drawText("R", 3 * (W - 20) / 4, i * (H / elements) + H / (elements * 2) - 60 / elements, (W - 20) / 4, 10, Justification::centred);
                        g.drawImageWithin(artists[i]->getIcon(), 10, i * H / elements + 10, (W - 20) / 4, H / elements - 20, 1, false);
                        g.setFont(20.0f);
                        g.setColour(artists[i]->getColour());
                        g.drawText(artists[i]->getName(), 0, i * (H / elements), W, 22, Justification::centred);
                    };
                };
            };
        }
        void resized() override
        {
        }
       
        TextButton seeArtists, seeSetup;
        Array<Artist*> artists;
        int elements = 1;
        bool isTracks = true;
    };

    struct Footer : public Component
    {
        Footer()
        {
        }
        void paint(Graphics& g) override
        {
            g.setColour(Colours::lightgrey);
            g.drawRect(getLocalBounds());
        }

    };

    //==============================================================================
    //================================= LISTAS =====================================
    //==============================================================================

    enum colourList
    {
        black = 1,
        blue,
        lightblue,
        brown,
        cyan,
        green,
        lightgreen,
        magenta,
        orange,
        pink,
        purple,
        red,
        violet,
        yellow,
        numberOfColours
    };

    enum State {
        playing,
        paused,
        stopped
    };

    enum OutMode {
        headphoneConfig,
        labConfig,
        sphereConfig
    };

    //==============================================================================
    //============================= PARTES DEL GRID ================================
    //==============================================================================

    Header header;
    MainPanel mainPanel;
    Demode demode;
    Footer footer;

    //==============================================================================
    //====================== SELECTOR DISPOSITIVO SALIDA ===========================
    //==============================================================================
    AudioDeviceSelectorComponent audioSetupComp;
    
    SpherePanner sphere;
    SphereBackground sphereBackground;

    AudioFormatManager formatManager;
    AudioSampleBuffer fileBuffer;
    AudioSampleBuffer sumBuffer;
    int position = 0;
    int elements = 1;
    int avaiableOutputs;

    ImageButton speakerButton;

    Array<Matrix<float>> decodingMatrixArray[2];
    int stateValue = 1;
    State state;
    OutMode outMode;
    int outputChannels = 2;
    int popUpSelection = 0;

    Array<Slider*> azimutSliders, elevationSliders, gainSliders;
    Array<TextButton*> soloButtons, muteButtons;
    Array<Artist*> newArtists;
    Array<int> colourIds;

    MidiKeyboardState keyboardState;
    MidiKeyboardComponent keyboardComponent;
    bool isAddingFromMidiInput = false;

    //==============================================================================
    //============================= BINAURALIZACIÓN ================================
    //==============================================================================

    std::atomic<float>* inputOrderSetting;
    std::atomic<float>* useSN3D;
    //std::atomic<float>* applyHeadphoneEq;
    //bool applyHeadphoneEq = false;

    //juce::dsp::Convolution EQ;
    int irLength = 236;
    int irLengthMinusOne = irLength-1;
    int fftLength = -1;
    float* in = nullptr;
    float* ifftOutputMid = nullptr;
    float* ifftOutputSide = nullptr;
    fftwf_complex* out = nullptr;
    fftwf_complex* accumMid = nullptr;
    fftwf_complex* accumSide = nullptr;
    fftwf_plan fftForward, fftBackwardMid, fftBackwardSide;
    bool fftwWasPlanned = false;

    AudioBuffer<float> stereoSum;
    AudioBuffer<float> overlapBuffer;
    AudioBuffer<float> irs[7];

    AudioBuffer<float> irsFrequencyDomain;
    double irsSampleRate = 44100.0;
    //mapping between mid-channel index and channel index
    int mix2cix[36] = { 0, 2, 3, 6, 7, 8, 12, 13, 14, 15, 20, 21, 22, 23, 24, 30, 31, 32, 33, 34, 35, 42, 43, 44, 45, 46, 47, 48, 56, 57, 58, 59, 60, 61, 62, 63 };
    //mapping between side-channel index and channel index
    int six2cix[28] = { 1, 4, 5, 9, 10, 11, 16, 17, 18, 19, 25, 26, 27, 28, 29, 36, 37, 38, 39, 40, 41, 49, 50, 51, 52, 53, 54, 55 };
    int nMidCh;
    int nSideCh;
        
    //============================================================================
    //============================================================================

    AudioSampleBuffer ambiBuffer;
    double sampleRate = 0.0;
    int expectedSamplesPerBlock = 0;

    std::atomic<float> azimuth[8];
    std::atomic<float> elevation[8];
    std::atomic<float> gain[8];

    float SH[8][16];
    float _SH[8][16];
    float _gain[8];

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};



//==============================================================================
//========================= CREACIÓN DE LA VENTANA =============================
//==============================================================================
class MainWindow : public DocumentWindow
{
public:
    MainWindow(String name, var info) : DocumentWindow(name,
        Desktop::getInstance().getDefaultLookAndFeel()
        .findColour(ResizableWindow::backgroundColourId),
        DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(info), true);

#if JUCE_IOS || JUCE_ANDROID
        setFullScreen(true);
#else
        setResizable(false, false);
        centreWithSize(getWidth(), getHeight());
#endif

        setVisible(true);
    }

    void closeButtonPressed() override
    {
        // This is called when the user tries to close this window. Here, we'll just
        // ask the app to quit when this happens, but you can change this to do
        // whatever you need.
        delete this;
        JUCEApplication::getInstance()->systemRequestedQuit();
    }

    /* Note: Be careful if you override any DocumentWindow methods - the base
       class uses a lot of them, so by overriding you might break its functionality.
       It's best to do all your work in your content component instead, but if
       you really have to override any DocumentWindow methods, make sure your
       subclass also calls the superclass's method.
    */

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow)
};
