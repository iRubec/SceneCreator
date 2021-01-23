#pragma once

#include <JuceHeader.h>
#include "Load.h"
#include "Create.h"

class Welcome : public Component
{
public:
    //==============================================================================
    Welcome();
    ~Welcome();

    //==============================================================================
    void paint(Graphics& g) override;
    /*
    void closeButtonPressed()
    {
        delete this;
    }
    */
private:
    //==============================================================================
    TextButton load, create;

    std::unique_ptr<LoadWindow> loadWindow;
    std::unique_ptr<CreateWindow> createWindow;

};


