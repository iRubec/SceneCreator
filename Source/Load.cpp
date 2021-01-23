#include "Load.h"

//==============================================================================
//============================ CONSTRUCTORES ===================================
//==============================================================================
Load::Load()
{
    // Introducimos el tamaño de la ventana
    setSize(800, 400);

    // Creamos los componentes de la ventana
    pathBox.setName("Path box");
    pathBox.setTextToShowWhenEmpty("Choose your json file", Colours::grey);
    pathBox.setReadOnly(true);
    pathBox.setBounds(10, 10, getWidth() - 100, 20);
    addAndMakeVisible(pathBox);

    searchBut.setName("Search button");
    searchBut.setButtonText("Search");
    searchBut.setBounds(getWidth() - 80, 10, 70, 20);
    searchBut.onClick = [this] { openBrowser(); };
    addAndMakeVisible(searchBut);

    descriptor.setName("Description box");
    descriptor.setTextToShowWhenEmpty("No file choosed", Colours::grey);
    descriptor.setReadOnly(true);
    descriptor.setMultiLine(true);
    descriptor.setScrollbarsShown(true);
    descriptor.setSelectAllWhenFocused(true);
    descriptor.setBounds(10, 40, getWidth() - 20, getHeight() - 80);
    addAndMakeVisible(descriptor);

    loadBut.setName("Load button");
    loadBut.setButtonText("Load");
    loadBut.setBounds(getRight() - 100, getBottom() - 30, 90, 20);
    loadBut.setEnabled(false);
    loadBut.onClick = [this]
    {
        new MainWindow("SONORIZART3 - Scene Creator", parsedJson);
        //mainWindow.reset(new MainWindow("SONORIZART3 - Scene Creator", parsedJson));
    };
    addAndMakeVisible(loadBut);

}

Load::~Load()
{

}
/*
void Load::paint(Graphics& g)
{
}
void Load::resized()
{
}
*/

//==============================================================================
//============================ BUSCAR ARCHIVO ==================================
//==============================================================================
void Load::openBrowser()
{
    // Abrimos un buscador de archivos que solo permita cargar jsons
    FileChooser chooser("Select a json file", {}, "*.json");

    if (chooser.browseForFileToOpen())
    {
        auto filePath = chooser.getResult();
        String path = filePath.getFullPathName();
        pathBox.setText(path);

        File file(path);
        parsedJson = JSON::parse(file);
        parser(parsedJson);

    }
}

//==============================================================================
//=========================== SELECTOR COLORES =================================
//==============================================================================
String Load::getColourName(int numColour)
{
    // Devolvemos el color seleccionado como un string
    String colour;
    switch (numColour) {
    case black:         colour = "Black";         break;
    case blue:          colour = "Blue";          break;
    case lightblue:     colour = "Light blue";    break;
    case brown:         colour = "Brown";         break;
    case cyan:          colour = "Cyan";          break;
    case green:         colour = "Green";         break;
    case lightgreen:    colour = "Light green";   break;
    case magenta:       colour = "Magenta";       break;
    case orange:        colour = "Orange";        break;
    case pink:          colour = "Pink";          break;
    case purple:        colour = "Purple";        break;
    case red:           colour = "Red";           break;
    case violet:        colour = "Violet";        break;
    case yellow:        colour = "Yellow";        break;

    default:
        break;
    }
    return colour;
}

//==============================================================================
//============================ PARSEADOR JSON ==================================
//==============================================================================
void Load::parser(var info)
{
    // Leemos el json con la información.  La información se va añadiendo al 
    // string descriptor y al acabar se escribe en el campo de descripción
    // Si se detecta que no hay campo 'Elements' se da el archivo por corrupto
    // y se para la lectura
    String data = JSON::toString(info);
    var parsedJson;

    if (JSON::parse(data, parsedJson).ok()) {
        
        int elements = parsedJson["Elements"];
        description = "Number of voices: " + to_string(elements);

        if (elements == 0) {
            cout << "JSON CORRUPTO" << endl;
            AlertWindow* alert = new AlertWindow("ERROR", "Algo va mal", juce::AlertWindow::WarningIcon);
            alert->showOkCancelBox(juce::AlertWindow::WarningIcon, "Error", "El archivo escogido no parece correcto");
        }
        else {

            // ELEMENTO 1
            String name_0 = parsedJson["Element_0"]["Name"];
            int colour_0 = parsedJson["Element_0"]["Colour"];
            String azimut_0 = parsedJson["Element_0"]["Azimut"];
            String elevation_0 = parsedJson["Element_0"]["Elevation"];
            String gain_0 = parsedJson["Element_0"]["Gain"];
            String track_0 = parsedJson["Element_0"]["Track"];
            String icon_0 = parsedJson["Element_0"]["Icon"];

            if (name_0 != "")
            {
                String element = "\n\nElement n1\n   Name: " + name_0 + "\n   Colour: " + getColourName(colour_0) + "\n   Position: " + azimut_0 + ", " + elevation_0 + ", " + gain_0 + " (az,el,dist)\n   Track: " + track_0 + "\n   Icon: " + icon_0;
                description = description + element;
            };

            // ELEMENTO 2
            String name_1 = parsedJson["Element_1"]["Name"];
            int colour_1 = parsedJson["Element_1"]["Colour"];
            String azimut_1 = parsedJson["Element_1"]["Azimut"];
            String elevation_1 = parsedJson["Element_1"]["Elevation"];
            String gain_1 = parsedJson["Element_1"]["Gain"];
            String track_1 = parsedJson["Element_1"]["Track"];
            String icon_1 = parsedJson["Element_1"]["Icon"];

            if (name_1 != "")
            {
                String element = "\n\nElement n2\n   Name: " + name_1 + "\n   Colour: " + getColourName(colour_1) + "\n   Position: " + azimut_1 + ", " + elevation_1 + ", " + gain_1 + " (az,el,dist)\n   Track: " + track_1 + "\n   Icon: " + icon_1;
                description = description + element;
            };

            // ELEMENTO 3
            String name_2 = parsedJson["Element_2"]["Name"];
            int colour_2 = parsedJson["Element_2"]["Colour"];
            String azimut_2 = parsedJson["Element_2"]["Azimut"];
            String elevation_2 = parsedJson["Element_2"]["Elevation"];
            String gain_2 = parsedJson["Element_2"]["Gain"];
            String track_2 = parsedJson["Element_2"]["Track"];
            String icon_2 = parsedJson["Element_2"]["Icon"];

            if (name_2 != "")
            {
                String element = "\n\nElement n3\n   Name: " + name_2 + "\n   Colour: " + getColourName(colour_2) + "\n   Position: " + azimut_2 + ", " + elevation_2 + ", " + gain_2 + " (az,el,dist)\n   Track: " + track_2 + "\n   Icon: " + icon_2;
                description = description + element;
            };

            // ELEMENTO 4
            String name_3 = parsedJson["Element_3"]["Name"];
            int colour_3 = parsedJson["Element_3"]["Colour"];
            String azimut_3 = parsedJson["Element_3"]["Azimut"];
            String elevation_3 = parsedJson["Element_3"]["Elevation"];
            String gain_3 = parsedJson["Element_3"]["Gain"];
            String track_3 = parsedJson["Element_3"]["Track"];
            String icon_3 = parsedJson["Element_3"]["Icon"];

            if (name_3 != "")
            {
                String element = "\n\nElement n4\n   Name: " + name_3 + "\n   Colour: " + getColourName(colour_3) + "\n   Position: " + azimut_3 + ", " + elevation_3 + ", " + gain_3 + " (az,el,dist)\n   Track: " + track_3 + "\n   Icon: " + icon_3;
                description = description + element;
            };

            // ELEMENTO 5
            String name_4 = parsedJson["Element_4"]["Name"];
            int colour_4 = parsedJson["Element_4"]["Colour"];
            String azimut_4 = parsedJson["Element_4"]["Azimut"];
            String elevation_4 = parsedJson["Element_4"]["Elevation"];
            String gain_4 = parsedJson["Element_4"]["Gain"];
            String track_4 = parsedJson["Element_4"]["Track"];
            String icon_4 = parsedJson["Element_4"]["Icon"];

            if (name_4 != "")
            {
                String element = "\n\nElement n5\n   Name: " + name_4 + "\n   Colour: " + getColourName(colour_4) + "\n   Position: " + azimut_4 + ", " + elevation_4 + ", " + gain_4 + " (az,el,dist)\n   Track: " + track_4 + "\n   Icon: " + icon_4;
                description = description + element;
            };

            // ELEMENTO 6
            String name_5 = parsedJson["Element_5"]["Name"];
            int colour_5 = parsedJson["Element_5"]["Colour"];
            String azimut_5 = parsedJson["Element_5"]["Azimut"];
            String elevation_5 = parsedJson["Element_5"]["Elevation"];
            String gain_5 = parsedJson["Element_5"]["Gain"];
            String track_5 = parsedJson["Element_5"]["Track"];
            String icon_5 = parsedJson["Element_5"]["Icon"];

            if (name_5 != "")
            {
                String element = "\n\nElement n6\n   Name: " + name_5 + "\n   Colour: " + getColourName(colour_5) + "\n   Position: " + azimut_5 + ", " + elevation_5 + ", " + gain_5 + " (az,el,dist)\n   Track: " + track_5 + "\n   Icon: " + icon_5;
                description = description + element;
            };

            // ELEMENTO 7
            String name_6 = parsedJson["Element_6"]["Name"];
            int colour_6 = parsedJson["Element_6"]["Colour"];
            String azimut_6 = parsedJson["Element_6"]["Azimut"];
            String elevation_6 = parsedJson["Element_6"]["Elevation"];
            String gain_6 = parsedJson["Element_6"]["Gain"];
            String track_6 = parsedJson["Element_6"]["Track"];
            String icon_6 = parsedJson["Element_6"]["Icon"];

            if (name_6 != "")
            {
                String element = "\n\nElement n7\n   Name: " + name_6 + "\n   Colour: " + getColourName(colour_6) + "\n   Position: " + azimut_6 + ", " + elevation_6 + ", " + gain_6 + " (az,el,dist)\n   Track: " + track_6 + "\n   Icon: " + icon_6;
                description = description + element;
            };

            // ELEMENTO 8
            String name_7 = parsedJson["Element_7"]["Name"];
            int colour_7 = parsedJson["Element_7"]["Colour"];
            String azimut_7 = parsedJson["Element_7"]["Azimut"];
            String elevation_7 = parsedJson["Element_7"]["Elevation"];
            String gain_7 = parsedJson["Element_7"]["Gain"];
            String track_7 = parsedJson["Element_7"]["Track"];
            String icon_7 = parsedJson["Element_7"]["Icon"];

            if (name_7 != "")
            {
                String element = "\n\nElement n8\n   Name: " + name_7 + "\n   Colour: " + getColourName(colour_7) + "\n   Position: " + azimut_7 + ", " + elevation_7 + ", " + gain_7 + " (az,el,dist)\n   Track: " + track_7 + "\n   Icon: " + icon_7;
                description = description + element;
            };

            descriptor.setText(description);
        };

        loadBut.setEnabled(true);

    }
    else {
        cout << "ERROR JSON LECTURE" << endl;

        AlertWindow* alert = new AlertWindow("ERROR", "Algo va mal", juce::AlertWindow::WarningIcon);
        alert->showOkCancelBox(juce::AlertWindow::WarningIcon, "Error", "Error en la lectura del archivo json");
    };
} 