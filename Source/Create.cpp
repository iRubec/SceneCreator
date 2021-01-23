#include "Create.h"

#include <stdio.h>
#include <string>
#include "Create.h"

//==============================================================================
//============================ CONSTRUCTORES ===================================
//==============================================================================
Create::Create()
{
    // Introducimos el tamaño de la ventana
    setSize(800, 700);

    // Creamos el primer contenedor de información.
    // Campo de texto para el nombre
    TextEditor* nameBox = new TextEditor();
    nameBox->setName("nameBox0");
    nameBox->setTextToShowWhenEmpty("Enter a name", Colours::grey);
    nameBox->setInputRestrictions(12);
    names.add(nameBox);
    addAndMakeVisible(nameBox);

    // Campo de desplegable para el color
    ComboBox* colourBox = new ComboBox();
    colourBox->setName("colourBox0");
    colourBox->addItem("Black", black);
    //if (enabledColours[0].data()) { colourBox->setItemEnabled(black, false); };
    colourBox->addItem("Blue", blue);
    //if (enabledColours[1].data()) { colourBox->setItemEnabled(blue, false); };
    colourBox->addItem("Light Blue", lightblue);
    //if (enabledColours[2].data()) { colourBox->setItemEnabled(lightblue, false); };
    colourBox->addItem("Brown", brown);
    //if (enabledColours[3].data()) { colourBox->setItemEnabled(brown, false); };
    colourBox->addItem("Cyan", cyan);
    //if (enabledColours[4].data()) { colourBox->setItemEnabled(cyan, false); };
    colourBox->addItem("Green", green);
    //if (enabledColours[5].data()) { colourBox->setItemEnabled(green, false); };
    colourBox->addItem("Light Green", lightgreen);
    //if (enabledColours[6].data()) { colourBox->setItemEnabled(lightgreen, false); };
    colourBox->addItem("Magenta", magenta);
    //if (enabledColours[7].data()) { colourBox->setItemEnabled(magenta, false); };
    colourBox->addItem("Orange", orange);
    //if (enabledColours[8].data()) { colourBox->setItemEnabled(orange, false); };
    colourBox->addItem("Pink", pink);
    //if (enabledColours[9].data()) { colourBox->setItemEnabled(pink, false); };
    colourBox->addItem("Purple", purple);
    //if (enabledColours[10].data()) { colourBox->setItemEnabled(purple, false); };
    colourBox->addItem("Red", red);
    //if (enabledColours[11].data()) { colourBox->setItemEnabled(red, false); };
    colourBox->addItem("Violet", violet);
    //if (enabledColours[12].data()) { colourBox->setItemEnabled(violet, false); };
    colourBox->addItem("Yellow", yellow);
    //if (enabledColours[13].data()) { colourBox->setItemEnabled(yellow, false); };
    coloursBoxes.add(colourBox);
    addAndMakeVisible(colourBox);
    colourBox->onChange = [this] { coloursMenuChanged(coloursBoxes[0]); };

    // Campo de texto para el acimut
    TextEditor* azimutBox = new TextEditor();
    azimutBox->setName("azimutBox0");
    azimutBox->setTextToShowWhenEmpty("Azimut", Colours::grey);
    azimutBox->setInputRestrictions(3);
    azimuts.add(azimutBox);
    addAndMakeVisible(azimutBox);

    // Campo de texto para la elevación
    TextEditor* elevationBox = new TextEditor();
    elevationBox->setName("elevationBox0");
    elevationBox->setTextToShowWhenEmpty("Elevation", Colours::grey);
    elevationBox->setInputRestrictions(3);
    elevations.add(elevationBox);
    addAndMakeVisible(elevationBox);

    // Campo de texto para la distancia
    TextEditor* gainBox = new TextEditor();
    gainBox->setName("gainBox0");
    gainBox->setTextToShowWhenEmpty("Gain", Colours::grey);
    gainBox->setInputRestrictions(3);
    gains.add(gainBox);
    addAndMakeVisible(gainBox);

    // Campo de texto para la ruta del sonido
    TextEditor* trackBox = new TextEditor();
    trackBox->setName("trackBox0");
    trackBox->setTextToShowWhenEmpty("Choose the path to the file", Colours::grey);
    trackBox->setReadOnly(true);
    tracks.add(trackBox);
    addAndMakeVisible(trackBox);

    // Campo de texto para la ruta del icono
    TextEditor* iconBox = new TextEditor();
    iconBox->setName("iconBox0");
    iconBox->setTextToShowWhenEmpty("Choose the path to the file", Colours::grey);
    iconBox->setReadOnly(true);
    icons.add(iconBox);
    addAndMakeVisible(iconBox);

    // Botón para buscar el sonido
    TextButton* trackBut = new TextButton();
    trackBut->setName("trackBut0");
    trackBut->setButtonText("Choose");
    trackBut->onClick = [this] { chooseButtonClicked(tracks[0]); };
    trackButtons.add(trackBut);
    addAndMakeVisible(trackBut);

    // Botón para buscar la imagen
    TextButton* iconBut = new TextButton();
    iconBut->setName("iconBut0");
    iconBut->setButtonText("Choose");
    iconBut->onClick = [this] { chooseButtonClicked(icons[0]); };
    iconButtons.add(iconBut);
    addAndMakeVisible(iconBut);

    // Añadimos los botones -/+
    minusBut.setName("Minus Button");
    minusBut.setButtonText("-");
    minusBut.setTooltip("Quit last font");
    minusBut.setEnabled(false);
    minusBut.onClick = [this] { buttonClicked(0); };
    addAndMakeVisible(minusBut);

    plusBut.setName("Plus Button");
    plusBut.setButtonText("+");
    plusBut.setTooltip("Add another font");
    plusBut.onClick = [this] { buttonClicked(1); };
    addAndMakeVisible(plusBut);

    // Añadimos el botón de crear escena
    createBut.setName("Create Button");
    createBut.setButtonText("Create");
    createBut.onClick = [this] { createJSON(); };
    addAndMakeVisible(createBut);

}

Create::~Create()
{

}

//==============================================================================
//==================================== PAINT ===================================
//==============================================================================
void Create::paint(Graphics& g)
{
    int W = getWidth();
    int H = getHeight();

    g.setColour(Colours::white);
    g.drawLine(10, 3, W - 20, 3);

    // Para cada contenedor existente, pintamos las etiquetas de cada componente
    // y les damos la posición
    for (int i = 0; i < elements; i++) {
        g.drawLine(10, 80 + i * 80, W - 20, 80 + i * 80);
        g.drawRoundedRectangle(10, 30 + i * 80, 20, 20, 20, 1.0f);
        g.drawText(to_string(i + 1), 10, 30 + i * 80, 20, 20, Justification::centred);

        g.drawText("Name:", 40, 6 + i * 80, 40, 20, dontSendNotification);
        names[i]->setBounds(80, 6 + i * 80, 100, 20);
        g.drawText("Colour:", 190, 6 + i * 80, 60, 20, dontSendNotification);
        coloursBoxes[i]->setBounds(240, 6 + i * 80, 180, 20);
        g.drawText("Azimut:", 430, 6 + i * 80, 60, 20, dontSendNotification);
        azimuts[i]->setBounds(480, 6 + i * 80, 40, 20);
        g.drawText("Elevation:", 530, 6 + i * 80, 60, 20, dontSendNotification);
        elevations[i]->setBounds(590, 6 + i * 80, 40, 20);
        g.drawText("Dist:", 640, 6 + i * 80, 60, 20, dontSendNotification);
        gains[i]->setBounds(680, 6 + i * 80, 40, 20);
        g.drawText("Track:", 40, 30 + i * 80, 40, 20, dontSendNotification);
        tracks[i]->setBounds(80, 30 + i * 80, W - 200, 20);
        trackButtons[i]->setBounds(W - 110, 32 + i * 80, 80, 20);
        g.drawText("Icon:", 40, 54 + i * 80, 40, 20, dontSendNotification);
        icons[i]->setBounds(80, 54 + i * 80, W - 200, 20);
        iconButtons[i]->setBounds(W - 110, 56 + i * 80, 80, 20);
    };

    //  Colocamos los botones -/+ y el de crear
    minusBut.setBounds(10, 10 + elements * 80, 20, 20);
    plusBut.setBounds(35, 10 + elements * 80, 20, 20);
    createBut.setBounds(getWidth() - 100, getHeight() - 50, 90, 40);

}

//==============================================================================
//======================== MANEJO BOTONES  -/+ =================================
//==============================================================================
void Create::buttonClicked(int num)
{
    // Dependiendo de que botón venga (- o +) quitamos elemento o añadimos
    // elemento y contenedor
    switch (num) {
        case 0:
            elements--;
            break;
        case 1:
            elements++;
            elementAdder();
            break;

        default:
            break;
    };

    // Depende de la cantidad de elementos que haya activamos y desactivamos
    // los botones: si hay 1 elemento, no se puede quitar y si hay 8 no se pueden
    // añadir
    if (elements <= 1) {
        minusBut.setEnabled(false);
        plusBut.setEnabled(true);
    }
    else if (elements > 1 && elements < 8) {
        minusBut.setEnabled(true);
        plusBut.setEnabled(true);
    }
    else if (elements >= 8) {
        minusBut.setEnabled(true);
        plusBut.setEnabled(false);
    };

    // Quitamos todos los contenedores por encima del número de elementos
    for (int i = elements; i <= 8; i++)
    {
        removeChildComponent(names[i]);
        removeChildComponent(coloursBoxes[i]);
        removeChildComponent(azimuts[i]);
        removeChildComponent(elevations[i]);
        removeChildComponent(gains[i]);
        removeChildComponent(tracks[i]);
        removeChildComponent(trackButtons[i]);
        removeChildComponent(icons[i]);
        removeChildComponent(iconButtons[i]);

        names.remove(i);
        coloursBoxes.remove(i);
        azimuts.remove(i);
        elevations.remove(i);
        gains.remove(i);
        tracks.remove(i);
        trackButtons.remove(i);
        icons.remove(i);
        iconButtons.remove(i);

    };

    // Repintamos para que aparezcan los cambios
    repaint();
}

//==============================================================================
//====================== BOTONES BUSQUEDA DE ACHIVOS ===========================
//==============================================================================
void Create::chooseButtonClicked(TextEditor* textBox)
{
    // Si se llama desde los componentes de búsqueda de sonidos, se abre un
    // buscador que solo permite cargar wavs
    // Si se llama desde los componentes de búsqueda de imágenes, se abre un
    // buscador que solo permite cargar pngs
    if (textBox->getName() == "trackBox0" || textBox->getName() == "trackBox1" || textBox->getName() == "trackBox2" || textBox->getName() == "trackBox3" || textBox->getName() == "trackBox4" || textBox->getName() == "trackBox5" || textBox->getName() == "trackBox6" || textBox->getName() == "trackBox7")
    {
        FileChooser chooser("Select a Wave file", {}, "*.wav");

        if (chooser.browseForFileToOpen())
        {
            auto file = chooser.getResult();
            String path = file.getFullPathName();
            textBox->setText(path);
        }
    }
    else if (textBox->getName() == "iconBox0" || textBox->getName() == "iconBox1" || textBox->getName() == "iconBox2" || textBox->getName() == "iconBox3" || textBox->getName() == "iconBox4" || textBox->getName() == "iconBox5" || textBox->getName() == "iconBox6" || textBox->getName() == "iconBox7")
    {
        FileChooser chooser("Select a PNG file", {}, "*.png");

        if (chooser.browseForFileToOpen())
        {
            auto file = chooser.getResult();
            String path = file.getFullPathName();
            textBox->setText(path);
        }
    }
}

//==============================================================================
//==================== CREADOR DE CONTENEDORES DE INFO =========================
//==============================================================================
void Create::elementAdder()
{
    // Esta función añadirá un nuevo contenedor de información, se crean de la
    // misma forma que se hace en el constructor
    TextEditor* nameBox = new TextEditor();
    nameBox->setName("nameBox" + to_string(elements - 1));
    nameBox->setTextToShowWhenEmpty("Enter a name", Colours::grey);
    nameBox->setInputRestrictions(12);
    names.add(nameBox);
    addAndMakeVisible(names[elements - 1]);

    ComboBox* colourBox = new ComboBox();
    colourBox->setName("colourBox" + to_string(elements - 1));
    colourBox->addItem("Black", black);
    if (enabledColours[0].data()) { colourBox->setItemEnabled(black, false); };
    colourBox->addItem("Blue", blue);
    if (enabledColours[1].data()) { colourBox->setItemEnabled(blue, false); };
    colourBox->addItem("Light Blue", lightblue);
    if (enabledColours[2].data()) { colourBox->setItemEnabled(lightblue, false); };
    colourBox->addItem("Brown", brown);
    if (enabledColours[3].data()) { colourBox->setItemEnabled(brown, false); };
    colourBox->addItem("Cyan", cyan);
    if (enabledColours[4].data()) { colourBox->setItemEnabled(cyan, false); };
    colourBox->addItem("Green", green);
    if (enabledColours[5].data()) { colourBox->setItemEnabled(green, false); };
    colourBox->addItem("Light Green", lightgreen);
    if (enabledColours[6].data()) { colourBox->setItemEnabled(lightgreen, false); };
    colourBox->addItem("Magenta", magenta);
    if (enabledColours[7].data()) { colourBox->setItemEnabled(magenta, false); };
    colourBox->addItem("Orange", orange);
    if (enabledColours[8].data()) { colourBox->setItemEnabled(orange, false); };
    colourBox->addItem("Pink", pink);
    if (enabledColours[9].data()) { colourBox->setItemEnabled(pink, false); };
    colourBox->addItem("Purple", purple);
    if (enabledColours[10].data()) { colourBox->setItemEnabled(purple, false); };
    colourBox->addItem("Red", red);
    if (enabledColours[11].data()) { colourBox->setItemEnabled(red, false); };
    colourBox->addItem("Violet", violet);
    if (enabledColours[12].data()) { colourBox->setItemEnabled(violet, false); };
    colourBox->addItem("Yellow", yellow);
    if (enabledColours[13].data()) { colourBox->setItemEnabled(yellow, false); };
    coloursBoxes.add(colourBox);
    addAndMakeVisible(coloursBoxes[elements - 1]);
    colourBox->onChange = [this] { coloursMenuChanged(coloursBoxes[elements - 1]); };

    TextEditor* azimutBox = new TextEditor();
    azimutBox->setName("azimutBox" + to_string(elements - 1));
    azimutBox->setTextToShowWhenEmpty("Azimut", Colours::grey);
    azimutBox->setInputRestrictions(3);
    azimuts.add(azimutBox);
    addAndMakeVisible(azimutBox);

    TextEditor* elevationBox = new TextEditor();
    elevationBox->setName("elevationBox" + to_string(elements - 1));
    elevationBox->setTextToShowWhenEmpty("Elevation", Colours::grey);
    elevationBox->setInputRestrictions(3);
    elevations.add(elevationBox);
    addAndMakeVisible(elevationBox);

    TextEditor* gainBox = new TextEditor();
    gainBox->setName("gainBox" + to_string(elements - 1));
    gainBox->setTextToShowWhenEmpty("Gain", Colours::grey);
    gainBox->setInputRestrictions(3);
    gains.add(gainBox);
    addAndMakeVisible(gainBox);

    TextEditor* trackBox = new TextEditor();
    trackBox->setName("trackBox" + to_string(elements - 1));
    trackBox->setTextToShowWhenEmpty("Choose the path to the file", Colours::grey);
    trackBox->setReadOnly(true);
    tracks.add(trackBox);
    addAndMakeVisible(tracks[elements - 1]);

    TextEditor* iconBox = new TextEditor();
    iconBox->setName("iconBox" + to_string(elements - 1));
    iconBox->setTextToShowWhenEmpty("Choose the path to the file", Colours::grey);
    iconBox->setReadOnly(true);
    icons.add(iconBox);
    addAndMakeVisible(icons[elements - 1]);

    TextButton* trackBut = new TextButton();
    trackBut->setName("trackBut" + to_string(elements - 1));
    trackBut->setButtonText("Choose");
    trackBut->onClick = [this] { chooseButtonClicked(tracks[elements - 1]); };
    trackButtons.add(trackBut);
    addAndMakeVisible(trackButtons[elements - 1]);

    TextButton* iconBut = new TextButton();
    iconBut->setName("iconBut" + to_string(elements - 1));
    iconBut->setButtonText("Choose");
    iconBut->onClick = [this] { chooseButtonClicked(icons[elements - 1]); };
    iconButtons.add(iconBut);
    addAndMakeVisible(iconButtons[elements - 1]);

}

//==============================================================================
//========================== SELECTOR COLORES ==================================
//==============================================================================
void Create::coloursMenuChanged(ComboBox* colourBox)
{
    // Se pondrá el color seleccionado como true en el array de enabledColours,
    // para que aparezca desactivado en el siguiente contenedor
    Colour boxColour;

    switch (colourBox->getSelectedId()) {
    case black:         enabledColours[0] = true; boxColour = Colours::black;     break;
    case blue:          enabledColours[1] = true; boxColour = Colours::blue;      break;
    case lightblue:     enabledColours[2] = true; boxColour = Colours::lightblue; break;
    case brown:         enabledColours[3] = true; boxColour = Colours::brown;     break;
    case cyan:          enabledColours[4] = true; boxColour = Colours::cyan;      break;
    case green:         enabledColours[5] = true; boxColour = Colours::green;     break;
    case lightgreen:    enabledColours[6] = true; boxColour = Colours::lightgreen; break;
    case magenta:       enabledColours[7] = true; boxColour = Colours::magenta;   break;
    case orange:        enabledColours[8] = true; boxColour = Colours::orange;    break;
    case pink:          enabledColours[9] = true; boxColour = Colours::pink;      break;
    case purple:        enabledColours[10] = true; boxColour = Colours::purple;    break;
    case red:           enabledColours[11] = true; boxColour = Colours::red;       break;
    case violet:        enabledColours[12] = true; boxColour = Colours::violet;    break;
    case yellow:        enabledColours[13] = true; boxColour = Colours::yellow;    break;

    default:
        break;
    }
}

//==============================================================================
//=============================== CREAR JSON ===================================
//==============================================================================
void Create::createJSON()
{
    // Crea un json con toda la información.  Primero, recorre todos los componentes
    // obligatorios y si no están rellenos lanza una alerta y no deja continuar.
    // Si los no obligatorios estan sin rellenar se inicializan y se crea el json
    int error = -1;
    DynamicObject* output = new DynamicObject();
    output->setProperty("Elements", elements);

    for (int i = 0; i < elements; i++) {
        if (names[i]->getTextValue().toString() == "") {
            cout << "Artist nº " + to_string(i + 1) << endl;
            AlertWindow* alert = new AlertWindow("ERROR", "Algo va mal", juce::AlertWindow::WarningIcon);
            alert->showOkCancelBox(juce::AlertWindow::WarningIcon, "Error", "Please enter name at artist nº " + to_string(i + 1));
            error = -1;
        }
        else if (coloursBoxes[i]->getSelectedId() == 0) {
            cout << "Colour nº " + to_string(i + 1) << endl;
            AlertWindow* alert = new AlertWindow("ERROR", "Algo va mal", juce::AlertWindow::WarningIcon);
            alert->showOkCancelBox(juce::AlertWindow::WarningIcon, "Error", "Please enter colour at artist nº " + to_string(i + 1));
            error = -1;
        }
        else if (tracks[i]->getTextValue().toString() == "") {
            cout << "Track nº " + to_string(i + 1) << endl;
            AlertWindow* alert = new AlertWindow("ERROR", "Algo va mal", juce::AlertWindow::WarningIcon);
            alert->showOkCancelBox(juce::AlertWindow::WarningIcon, "Error", "Please enter track at artist nº " + to_string(i + 1));
            error = -1;
        }
        else {
            if (icons[i]->getTextValue().toString() == "") { icons[i]->setText("default"); };
            if (azimuts[i]->getTextValue().toString() == "") { azimuts[i]->setText("0"); };
            if (elevations[i]->getTextValue().toString() == "") { elevations[i]->setText("0"); };
            if (gains[i]->getTextValue().toString() == "") { gains[i]->setText("1.5"); };

            DynamicObject* newElement = new DynamicObject();
            newElement->setProperty("Name", names[i]->getTextValue());
            newElement->setProperty("Colour", coloursBoxes[i]->getSelectedId());
            newElement->setProperty("Azimut", azimuts[i]->getTextValue());
            newElement->setProperty("Elevation", elevations[i]->getTextValue());
            newElement->setProperty("Gain", gains[i]->getTextValue());
            newElement->setProperty("Track", tracks[i]->getTextValue());
            newElement->setProperty("Icon", icons[i]->getTextValue());
            String label = "Element_" + to_string(i);
            output->setProperty(label, newElement);
            error = 1;
        };
    };

    // Si el archivo se ha creado correctamente, se crea una ventana MainWindow,
    // a la que se le pasa el json
    if (error == 1) {
        var json(output);
        String s = JSON::toString(json);
        new MainWindow("SONORIZART3 - Scene Creator", json);
        //mainWindow.reset(new MainWindow("Scene Creator", json));
        //delete mainWindow.get();
    };

}