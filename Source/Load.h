#pragma once

#include <JuceHeader.h>
#include "MainComponent.h"

using namespace std;

class Load : public Component
{
public:
    //==============================================================================
    Load();
    ~Load();

    //==============================================================================
    void paint(Graphics& g) override {};
    void resized() override {};

    //==============================================================================
    void openBrowser();
    String getColourName(int numColour);
    void parser(var info);

    void closeButtonPressed()
    {
        delete this;
    }

private:
    //=============================================================================
    TextEditor pathBox, descriptor;
    TextButton searchBut, loadBut;
    String description;
    var parsedJson;

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

    std::unique_ptr<MainWindow> mainWindow;

};


//==============================================================================
//========================= CREACIÓN DE LA VENTANA =============================
//==============================================================================
class LoadWindow : public DocumentWindow
{
public:
    LoadWindow(String name) : DocumentWindow(name,
        Desktop::getInstance().getDefaultLookAndFeel()
        .findColour(ResizableWindow::backgroundColourId),
        DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new Load(), true);

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
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(LoadWindow)
};
