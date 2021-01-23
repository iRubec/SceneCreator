#pragma once
#include <JuceHeader.h>
#include "MainComponent.h"

using namespace std;

class Create : public Component
{
public:
    //==============================================================================
    Create();
    ~Create();

    //==============================================================================
    void paint(Graphics& g) override;

    void closeButtonPressed()
    {
        delete this;
    }

    //==============================================================================
    void buttonClicked(int num);
    void chooseButtonClicked(TextEditor* textBox);
    void elementAdder();
    void coloursMenuChanged(ComboBox* colourBox);
    void createJSON();

private:
    //==============================================================================    
    TextButton createBut, minusBut, plusBut;
    Array<TextEditor*> names, azimuts, elevations, gains, tracks, icons;
    Array<TextButton*> trackButtons, iconButtons;
    Array<ComboBox*> coloursBoxes;
    Array<Colour*> colours;
    Array<bool> enabledColours[14];

    int elements = 1;

    // Lista de colores
    enum boxColours
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

    std::unique_ptr<MainWindow> mainWindow;

};


//==============================================================================
//========================= CREACIÓN DE LA VENTANA =============================
//==============================================================================
class CreateWindow : public DocumentWindow
{
public:
    CreateWindow(String name) : DocumentWindow(name,
        Desktop::getInstance().getDefaultLookAndFeel()
        .findColour(ResizableWindow::backgroundColourId),
        DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new Create(), true);

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
        delete this;
        JUCEApplication::getInstance()->systemRequestedQuit();
    }

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CreateWindow)
};
