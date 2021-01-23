#include "Welcome.h"
#include <stdio.h>

//==============================================================================
//============================ CONSTRUCTORES ===================================
//==============================================================================
Welcome::Welcome()
{
    // Introducimos el tamaño de la ventana
    setSize(400, 200);

    // Asignamos a los dos botones sus propiedades
    load.setName("load");
    load.setButtonText("Load scene");
    load.onClick = [this]
    {
        new LoadWindow("SONORIZART3 - Load scene configuration");
        //loadWindow.reset(new LoadWindow("Load scene configuration"));
    };
    addAndMakeVisible(load);

    create.setName("create");
    create.setButtonText("Create scene");
    create.onClick = [this]
    {
        new CreateWindow("SONORIZART3 - Create new scene configuration");
        //closeButtonPressed();
        //createWindow.reset(new CreateWindow("Create new scene configuration"));
    };
    addAndMakeVisible(create);
}

Welcome::~Welcome()
{
}

//==============================================================================
//==================================== PAINT ===================================
//==============================================================================
void Welcome::paint(Graphics& g)
{
    // Situamos los botones en la ventana. Como el tamaño de la ventana es fijo, 
    // ponemos valores concretos
    load.setBounds(100, 50, 200, 50);
    create.setBounds(100, 110, 200, 50);
}