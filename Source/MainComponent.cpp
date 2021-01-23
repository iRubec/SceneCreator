/*
  ==============================================================================

    This file was auto-generated!

  ==============================================================================
*/

#include "MainComponent.h"

//==============================================================================
//================================ CONSTRUCTOR =================================
//==============================================================================
// Al inicializar MainComponent, inicializamos a su vez el keyBoarComponent para
// la lectura MIDI y elaudioSetupComponent para la selección de modo de salida
// del audio
MainComponent::MainComponent(var info)
    : keyboardComponent(keyboardState, MidiKeyboardComponent::horizontalKeyboard),
      audioSetupComp(deviceManager, 0, 256, 0,  256, false, false, false, true)
{
    // Le damos el tamaño de la pantalla del ordenador (un poco más pequeña de
    // altura) a la ventana
    Rectangle<int> r = Desktop::getInstance().getDisplays().getMainDisplay().userArea;
    centreWithSize(r.getWidth(), r.getHeight()-50);

    // Parseamos el json de llegada con los datos para obtener toda la info de la escena
    parser(info);

    // Cogemos el tamaño de algunas partes del grid para poner directamente aqui la 
    // situación de los objetos.  Como a la ventana no se le puede cambiarel tamaño, 
    // no tendremos problemas por hacerlo  aqui
    int dW = demode.getWidth()-30;
    int dH = demode.getHeight();
    int fW = footer.getWidth();
    int fH = footer.getHeight();

    // Para cada elemento (artista) habrá que crear todos los componentes necesarios:
    // slider de azimut, slider de elevación, slider de ganancia/distancia, botón de 
    // solo, botón de mute.  Finalmente crearemos el elemento correspondiente a la 
    // esfera
    for (int i = 0; i < elements; i++) {
        // Creamos el slider del azimut y le añadimos todas las características
        Slider* newAzimut = new Slider;
        newAzimut->setName(newArtists[i]->getName() + "_az");
        newAzimut->setColour(Slider::thumbColourId, Colours::blue);
        newAzimut->setSliderStyle(Slider::SliderStyle::Rotary);
        newAzimut->setRange(0, 360, 1);
        newAzimut->setNumDecimalPlacesToDisplay(0);
        newAzimut->setValue(newArtists[i]->getCoor().x);
        if (elements <= 4) {
            newAzimut->setBounds((dW - 20) / 4, i * (dH / 4) + 8, (dW - 20) / 4, dH / 4 - 10);
            newAzimut->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 60, 20);
        }
        else {
            newAzimut->setBounds((dW - 20) / 4, i * (dH / elements) + 8, (dW - 20) / 4, dH / elements - 10);
            newAzimut->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 240 / elements, 80 / elements);
        }
        newAzimut->addListener(this);
        azimutSliders.add(newAzimut);
        addAndMakeVisible(azimutSliders[i]);
        demode.addChildComponent(azimutSliders[i]);

        // Creamos el slider de la elevación y le añadimos todas las características
        Slider* newElevation = new Slider;
        newElevation->setName(newArtists[i]->getName() + "_el");
        newElevation->setColour(Slider::thumbColourId, Colours::red);
        newElevation->setSliderStyle(Slider::SliderStyle::Rotary);
        newElevation->setRange(0, 360, 1);
        newElevation->setNumDecimalPlacesToDisplay(0);
        newElevation->setValue(newArtists[i]->getCoor().y);
        if (elements <= 4) {
            newElevation->setBounds(2 * (dW - 20) / 4, i * (dH / 4) + 8, (dW - 20) / 4, dH / 4 - 10);
            newElevation->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 60, 20);
        }
        else {
            newElevation->setBounds(2 * (dW - 20) / 4, i * (dH / elements) + 8, (dW - 20) / 4, dH / elements - 10);
            newElevation->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 240 / elements, 80 / elements);
        }
        newElevation->addListener(this);
        elevationSliders.add(newElevation);
        addAndMakeVisible(elevationSliders[i]);
        demode.addChildComponent(elevationSliders[i]);

        // Creamos el slider de la ganancia y le añadimos todas las características
        Slider* newGain = new Slider;
        newGain->setName(newArtists[i]->getName() + "_g");
        newGain->setColour(Slider::thumbColourId, Colours::green);
        newGain->setSliderStyle(Slider::SliderStyle::Rotary);
        newGain->setRange(1.5, 12, 0.0);
        newGain->setNumDecimalPlacesToDisplay(1);
        newGain->setValue(newArtists[i]->getCoor().z);
        if (elements <= 4) {
            newGain->setBounds(3 * (dW - 20) / 4, i * (dH / 4) + 8, (dW - 20) / 4, dH / 4 - 10);
            newGain->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 60, 20);
        }
        else {
            newGain->setBounds(3 * (dW - 20) / 4, i * (dH / elements) + 8, (dW - 20) / 4, dH / elements - 10);
            newGain->setTextBoxStyle(Slider::TextEntryBoxPosition::TextBoxBelow, false, 240 / elements, 80 / elements);
        }
        newGain->addListener(this);
        gainSliders.add(newGain);
        addAndMakeVisible(gainSliders[i]);
        demode.addChildComponent(gainSliders[i]);

        // Creamos el botón de solo y le añadimos todas las características
        TextButton* newSolo = new TextButton;
        newSolo->setName(newArtists[i]->getName() + "_s");
        newSolo->setButtonText("S");
        newSolo->setRadioGroupId(i + 1, sendNotification);
        newSolo->setColour(TextButton::buttonColourId, Colours::red.withMultipliedAlpha(0.5f));
        newSolo->setColour(TextButton::buttonOnColourId, Colours::red);
        newSolo->setColour(TextButton::textColourOnId, Colours::black);
        if (elements <= 4) {
            int width = dW / 16;
            newSolo->setBounds((dW - 20) / 4 - width + 10, i * (dH / 4) + 38, width, width);
        }
        else {
            int width = dW / (elements * 4);
            newSolo->setBounds((dW - 20) / 4 - width + 10, i * (dH / elements) + width, width, width);
        }
        newSolo->addListener(this);
        soloButtons.add(newSolo);
        addAndMakeVisible(soloButtons[i]);
        demode.addChildComponent(soloButtons[i]);

        // Creamos el botón de mute y le añadimos todas las características
        TextButton* newMute = new TextButton;
        newMute->setName(newArtists[i]->getName() + "_m");
        newMute->setButtonText("M");
        newMute->setRadioGroupId(i + 1, sendNotification);
        newMute->setColour(TextButton::buttonColourId, Colours::yellow.withMultipliedAlpha(0.5f));
        newMute->setColour(TextButton::buttonOnColourId, Colours::yellow);
        newMute->setColour(TextButton::textColourOnId, Colours::black);
        if (elements <= 4) {
            int width = dW / 16;
            newMute->setBounds((dW - 20) / 4 - width + 10, i * (dH / 4) + 43 + width, width, width);
        }
        else {
            int width = dW / (elements * 4);
            newMute->setBounds((dW - 20) / 4 - width + 10, i * (dH / elements) + 2 * width + 5, width, width);
        }
        newMute->addListener(this);
        muteButtons.add(newMute);
        addAndMakeVisible(muteButtons[i]);
        demode.addChildComponent(muteButtons[i]);

        // Creamos el elemento en la esfera y le añadimos todas las características
        SpherePanner::MyElement* newElement = new SpherePanner::MyElement;
        newElement->setColour(newArtists[i]->getColour());
        newElement->setLabel(newArtists[i]->getName().substring(0, 1));
        newElement->setActive(true);
        newElement->setTextColour(Colours::black);
        newElement->setCoordinates(newArtists[i]->getCoor());
        sphere.addMyElement(newElement);
    };
       
    //==============================================================================
    //========================= BOTONES SAVE Y SPEAKER =============================
    //==============================================================================

    // Ceamos el botón para guardar la configuración y lo añadimos al header
    TextButton* saveButton = new TextButton;
    saveButton->setName("Save Button");
    saveButton->setButtonText("SAVE");
    saveButton->setBounds(header.getWidth() - 100, 10, 90, header.getHeight() - 20);
    saveButton->onClick = [this] { saveFile(); };

    addAndMakeVisible(saveButton);
    header.addChildComponent(saveButton);

    //  Ceamos el botón el de selección de tipo de reproducción. Al clickarlo se
    // desplegará el menú de selección con las tres opciones (auriculares,
    // 8 altavoces o la esfera)
    int hpSize;
    String hpName = "hp_png";
    auto* hpData = BinaryData::getNamedResource(hpName.toUTF8(), hpSize);
    Image speakerIcon = ImageFileFormat::loadFrom(hpData, hpSize);
    speakerButton.setImages(false, true, true, speakerIcon, 0.6f, {}, speakerIcon, 1.0f, {}, speakerIcon, 1.0f, {}, 0);
    speakerButton.setName("Setup");
    speakerButton.setBounds(header.getWidth() - 160, 10, header.getHeight() - 20, header.getHeight() - 20);
    speakerButton.onClick = [this] { openPopup(); };
    addAndMakeVisible(speakerButton);
    header.addChildComponent(speakerButton);

    //==============================================================================
    //===================== BOTONES PLAY, PAUSE Y STOP =============================
    //==============================================================================

    // Creamos los botones de play, pause y stop para el reproductor y los añadimos al footer
    ImageButton* play = new ImageButton;
    int playSize;
    String playName = "play_png";
    auto* playData = BinaryData::getNamedResource(playName.toUTF8(), playSize);
    Image playIcon = ImageFileFormat::loadFrom(playData, playSize);
    play->setImages(false, true, true, playIcon, 0.6f, {}, playIcon, 1.0f, {}, playIcon, 1.0f, {}, 0);
    play->setName("Play Button");
    play->setRadioGroupId(9, dontSendNotification);
    play->setBounds((fW / 2) - 3*(fH - 20) / 2 - 20, 10, (fH - 20), (fH - 20));
    play->setTooltip("PLAY");
    play->addListener(this);
    
    addAndMakeVisible(play);
    footer.addChildComponent(play);

    ImageButton* pause = new ImageButton;
    int pauseSize;
    String pauseName = "pause_png";
    auto* pauseData = BinaryData::getNamedResource(pauseName.toUTF8(), pauseSize);
    Image pauseIcon = ImageFileFormat::loadFrom(pauseData, pauseSize);
    pause->setImages(false, true, true, pauseIcon, 0.6f, {}, pauseIcon, 1.0f, {}, pauseIcon, 1.0f, {}, 0);
    pause->setName("Pause Button");
    pause->setRadioGroupId(9, dontSendNotification);
    pause->setBounds((fW / 2) - (fH - 20) / 2, 10 , (fH - 20), (fH - 20));
    pause->setTooltip("PAUSE");
    pause->addListener(this);
    
    addAndMakeVisible(pause);
    footer.addChildComponent(pause);

    ImageButton* stop = new ImageButton;
    int stopSize;
    String stopName = "stop_png";
    auto* stopData = BinaryData::getNamedResource(stopName.toUTF8(), stopSize);
    Image stopIcon = ImageFileFormat::loadFrom(stopData, stopSize);
    stop->setImages(false, true, true, stopIcon, 0.6f, {}, stopIcon, 1.0f, {}, stopIcon, 1.0f, {}, 0);
    stop->setName("Stop Button");
    stop->setRadioGroupId(9, dontSendNotification);
    stop->setBounds((fW / 2) + (fH - 20) / 2 + 20, 10, (fH - 20), (fH - 20));
    stop->setTooltip("STOP");
    stop->addListener(this);
    
    addAndMakeVisible(stop);
    footer.addChildComponent(stop);

    //==============================================================================
    //============================= PARTES DEL GRID ================================
    //==============================================================================

    // Añadimos a la ventana las cuatro partes del grid
    addAndMakeVisible(header);
    addAndMakeVisible(mainPanel);
    addAndMakeVisible(demode);
    addAndMakeVisible(footer);

    //==============================================================================
    //=============================== ESFERA =======================================
    //==============================================================================

    // Habrá que añadir también la esfera para dibujarla, está se añade en el mainPanel
    addAndMakeVisible(&sphere);
    mainPanel.addChildComponent(&sphere);

    //==============================================================================
    //================================= MIDI =======================================
    //==============================================================================

    // Miraremos si está conectado el MIDI Mix, y mandaremos la información al header
    // para que saque por patalla si está cnectado o no
    header.setInfo(2, "Not found");
    auto midiInputs = MidiInput::getAvailableDevices();
    for (int i = 0; i < midiInputs.size(); i++)
    {
        auto newInput = midiInputs[i];

        if (newInput.name == "MIDI Mix")
        {
            deviceManager.setMidiInputDeviceEnabled(newInput.identifier, true);
            deviceManager.addMidiInputDeviceCallback(newInput.identifier, this);
            header.setInfo(2, "Connected");
            break;
        }

    }

    //==============================================================================
    //======================== MATRICES DE DECODIFICACIÓN ==========================
    //==============================================================================
    
    // Leemos y creamos las matrices de decodificación de las salidas disponibles 
    // (ocho altavoces y la esfera de 24 altavoces).  Estas matrices son decodMatrixLab
    // y decodMatrixSphere
    Matrix<float> decodMatrixLab(8, 16);
    Matrix<float> decodMatrixSphere(24, 16);

    // La información está almacenada en el json decodingMatrix
    int decodSize;
    String decodName = "decodingMatrix_json";
    auto* decodData = BinaryData::getNamedResource(decodName.toUTF8(), decodSize);
    var matrixJson = JSON::parse(decodData);
    String data = JSON::toString(matrixJson);
    var parsedJson;

    if (JSON::parse(data, parsedJson).ok()) {

        // La matriz de los 8 altavoces está en la etiqute labMatrix
        if (auto matrix = parsedJson.getProperty("labMatrix", var()).getArray())
        {
            int i = 0;
            for (auto& m : *matrix)
            {
                for (int j = 0; j < m.size(); j++)
                    decodMatrixLab(i, j) = (float)m[j];
                i++;
            };
            
        };

        // La matriz de la esfera está en sphereMatrix
        if (auto matrix = parsedJson.getProperty("sphereMatrix", var()).getArray())
        {
            int i = 0;
            for (auto& m : *matrix)
            {
                for (int j = 0; j < m.size(); j++)
                    decodMatrixSphere(i, j) = (float)m[j];
                i++;
            };

        };

    };

    // Las dos matrices se añaden al array de matrices
    decodingMatrixArray->add(decodMatrixLab);
    decodingMatrixArray->add(decodMatrixSphere);

    //==============================================================================
    //============================= BINAURALIZACIÓN ================================
    //==============================================================================
    
    // Inicializamos  los datos necesarios para la binauralización y cargamos las
    // respuestas al impulso para la conversión
    AudioBuffer<float> resampledIRs;
    bool useResampled = false;
    irLength = 236;
    irLengthMinusOne = irLength - 1;
    overlapBuffer.setSize(2, irLengthMinusOne);
    overlapBuffer.clear();

    // Cargamos las IRs
    formatManager.registerBasicFormats();
    WavAudioFormat wavFormat;

    MemoryInputStream* mis[7];
    mis[0] = new MemoryInputStream(BinaryData::irsOrd1_wav, BinaryData::irsOrd1_wavSize, false);
    mis[1] = new MemoryInputStream(BinaryData::irsOrd2_wav, BinaryData::irsOrd2_wavSize, false);
    mis[2] = new MemoryInputStream(BinaryData::irsOrd3_wav, BinaryData::irsOrd3_wavSize, false);
    mis[3] = new MemoryInputStream(BinaryData::irsOrd4_wav, BinaryData::irsOrd4_wavSize, false);
    mis[4] = new MemoryInputStream(BinaryData::irsOrd5_wav, BinaryData::irsOrd5_wavSize, false);
    mis[5] = new MemoryInputStream(BinaryData::irsOrd6_wav, BinaryData::irsOrd6_wavSize, false);
    mis[6] = new MemoryInputStream(BinaryData::irsOrd7_wav, BinaryData::irsOrd7_wavSize, false);

    for (int i = 0; i < 7; ++i)
    {
        irs[i].setSize(square(i + 2), irLength);
        std::unique_ptr<AudioFormatReader> reader(wavFormat.createReaderFor(mis[i], true));
        reader->read(&irs[i], 0, irLength, 0, true, false);
        irs[i].applyGain(0.3f);
    }

    //==============================================================================
    //=============================== BUFFERS ======================================
    //==============================================================================

    // Llenamos los buffers con los caminos a las canciones cargadas en el json.
    // Leemos el track del primer elemento (este siempre existirá).  Con el marcaremos
    // el tamaño de nuestro buffer general fileBuffer, donde se guardaran cada track 
    // en un canal diferente.
    File file(newArtists[0]->getTrack());
    AudioSampleBuffer firstBuffer;
    std::unique_ptr<AudioFormatReader> reader(formatManager.createReaderFor(file));
    fileBuffer.setSize(elements, (int)reader->lengthInSamples);
    firstBuffer.setSize((int)reader->numChannels, (int)reader->lengthInSamples);
    reader->read(&firstBuffer, 0, (int)reader->lengthInSamples, 0, true, true);
    
    // Si es stereo (tiene dos canales), lo convertiremos a mono; si ya es mono,
    // lo copiaremos directamente a nuestro buffer general
    if (reader->numChannels == 2) {
        for (int sample = 0; sample < firstBuffer.getNumSamples(); sample++) {
            float sampleLeft = firstBuffer.getSample(0, sample);
            float sampleRight = firstBuffer.getSample(1, sample);
            float monoSummed = sampleLeft + sampleRight;
            fileBuffer.setSample(0, sample, monoSummed);
        };
    };
    

    // Ahora haremos lo mismo para los demás elementos que tengamos en la
    // configuración, saltándonos el primero
    for (int i = 1; i < elements; i++) {
        File file(newArtists[i]->getTrack());
        AudioSampleBuffer newBuffer;
        std::unique_ptr<AudioFormatReader> reader(formatManager.createReaderFor(file));
        newBuffer.setSize((int)reader->numChannels, (int)reader->lengthInSamples);
        reader->read(&newBuffer, 0, (int)reader->lengthInSamples, 0, true, true);

        // Si es stereo (tiene dos canales), lo convertiremos a mono; si ya es mono,
        // lo copiaremos directamente a nuestro buffer general
        if (reader->numChannels == 2) {
            for (int sample = 0; sample < newBuffer.getNumSamples(); sample++) {
                float sampleLeft = newBuffer.getSample(0, sample);
                float sampleRight = newBuffer.getSample(1, sample);
                float monoSummed = sampleLeft + sampleRight;
                fileBuffer.setSample(i, sample, monoSummed);
            };
        };
        
    };

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired(RuntimePermissions::recordAudio)
        && !RuntimePermissions::isGranted(RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request(RuntimePermissions::recordAudio,
            [&](bool granted) { if (granted)  setAudioChannels(0, 8); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels(0, 8);
    }

    //==============================================================================
    //=========================== TARJETA DE SONIDO ================================
    //==============================================================================

    // Leemos la tarjeta da sonido que se está usando y se la pasamos al header
    // para que la saque por pantalla
    // deviceManager.getAudioDeviceSetup();
    auto* device = deviceManager.getCurrentAudioDevice();
    String deviceName = device->getName();
    auto activeOutputChannels = device->getActiveOutputChannels();
    avaiableOutputs = activeOutputChannels.countNumberOfSetBits();
    header.setInfo(1, deviceName);

    // Le dcimos que use los drivers ASIO para la salida de audio
    if (deviceName == "Focusrite USB (Focusrite USB Audio)")
        deviceManager.setCurrentAudioDeviceType("ASIO", true);

    // Añadimos el panel de control de las salidas de audios a la parte del grid
    // demode
    audioSetupComp.setBounds(0, 0, dW, dH);
    demode.addChildComponent(audioSetupComp, 1);

    // Inicialmente la aplicación se abrirá reproduciendo el audio y para dos canales de salida (auriculares)
    state = playing;
    outMode = headphoneConfig;

    // Iniciamos el timer de lectura del gasto de CPU y de dispositivo utilizado
    startTimer(500);

}

MainComponent::~MainComponent()
{
    // Apaga el dispositivo de audio y impia la fuente de audio
    if (fftwWasPlanned)
    {
        fftwf_destroy_plan(fftForward);
        fftwf_destroy_plan(fftBackwardMid);
        fftwf_destroy_plan(fftBackwardSide);
    }

    if (in != nullptr)
        fftwf_free(in);
    if (out != nullptr)
        fftwf_free(out);
    if (accumMid != nullptr)
        fftwf_free(accumMid);
    if (accumSide != nullptr)
        fftwf_free(accumSide);
    if (ifftOutputMid != nullptr)
        fftwf_free(ifftOutputMid);
    if (ifftOutputSide != nullptr)
        fftwf_free(ifftOutputSide);
    shutdownAudio();
}

//==============================================================================

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double newSampleRate)
{
    // Marcamos la velocidad de bits y  el número de samples esperados por cada bloque    
    sampleRate = newSampleRate;
    expectedSamplesPerBlock = samplesPerBlockExpected;

    ambiBuffer.setSize(16, samplesPerBlockExpected);

    update();
}

void MainComponent::update()
{
    //==============================================================================
    //========================== ACTUALIZACIÓN BUFFERS =============================
    //============================================================================== 
    // En esta función se actualizan los buffers y las fft necesarias para binauralizar
    // la señal Ambisonics

    // Marcamos la velocidad de bit y eltamaño del bloque de audio en muestras
    const double sampleRate = ambiBuffer.getNumSamples();
    const int blockSize = expectedSamplesPerBlock;

    // Usamos Ambisonics de orden 3, lo cual tendrá siempre 16 canales
    int order = 3;
    const int nCh = 16;
    
    // Cogemos el número de canales mid- y side-
    nSideCh = order * (order + 1) / 2;
    nMidCh = square(order + 1) - nSideCh;

    AudioBuffer<float> resampledIRs;
    bool useResampled = false;
    irLength = 236;

    if (sampleRate != irsSampleRate) // do resampling!
    {
        useResampled = true;
        double factorReading = irsSampleRate / sampleRate;
        irLength = roundToInt (irLength / factorReading + 0.49);

        MemoryAudioSource memorySource (irs[order - 1], false);
        ResamplingAudioSource resamplingSource (&memorySource, false, nCh);

        resamplingSource.setResamplingRatio (factorReading);
        resamplingSource.prepareToPlay (irLength, sampleRate);

        resampledIRs.setSize(nCh, irLength);
        AudioSourceChannelInfo info;
        info.startSample = 0;
        info.numSamples = irLength;
        info.buffer = &resampledIRs;

        resamplingSource.getNextAudioBlock (info);

        // compensate for more (correlated) samples contributing to output signal
        resampledIRs.applyGain (irsSampleRate / sampleRate);
    }

    irLengthMinusOne = irLength - 1;

    const int prevFftLength = fftLength;

    const int ergL = blockSize + irLength - 1; //max number of nonzero output samples
    fftLength = nextPowerOfTwo(ergL);          //fftLength >= ergL

    overlapBuffer.setSize(2, irLengthMinusOne);
    overlapBuffer.clear();

    if (prevFftLength != fftLength)
    {
        if (fftwWasPlanned)
        {
            fftwf_destroy_plan(fftForward);
            fftwf_destroy_plan(fftBackwardMid);
            fftwf_destroy_plan(fftBackwardSide);
        }

        if (in != nullptr)
            fftwf_free(in);
        if (out != nullptr)
            fftwf_free(out);
        if (accumMid != nullptr)
            fftwf_free(accumMid);
        if (accumSide != nullptr)
            fftwf_free(accumSide);
        if (ifftOutputMid != nullptr)
            fftwf_free(ifftOutputMid);
        if (ifftOutputSide != nullptr)
            fftwf_free(ifftOutputSide);

        in = (float*) fftwf_malloc(sizeof(float) * fftLength);
        out = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * (fftLength / 2 + 1));
        accumMid = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * (fftLength / 2 + 1));
        accumSide = (fftwf_complex*) fftwf_malloc(sizeof(fftwf_complex) * (fftLength / 2 + 1));
        ifftOutputMid = (float*) fftwf_malloc(sizeof(float) * fftLength);
        ifftOutputSide = (float*) fftwf_malloc(sizeof(float) * fftLength);

        fftForward = fftwf_plan_dft_r2c_1d(fftLength, in, out, FFTW_MEASURE);
        fftBackwardMid = fftwf_plan_dft_c2r_1d(fftLength, accumMid, ifftOutputMid, FFTW_MEASURE);
        fftBackwardSide = fftwf_plan_dft_c2r_1d(fftLength, accumSide, ifftOutputSide, FFTW_MEASURE);
        fftwWasPlanned = true;
    }

    FloatVectorOperations::clear((float*) in, fftLength); // clear (after plan creation!)

    irsFrequencyDomain.setSize(nCh, 2 * (fftLength / 2 + 1));
    irsFrequencyDomain.clear();

    for (int i = 0; i < nCh; ++i)
    {
        const float* src = useResampled ? resampledIRs.getReadPointer(i) : irs[order - 1].getReadPointer(i);
        FloatVectorOperations::multiply((float*)in, src, 1.0 / fftLength, irLength);
        FloatVectorOperations::clear(&in[irLength], fftLength - irLength); // zero padding
        fftwf_execute(fftForward);
        FloatVectorOperations::copy(irsFrequencyDomain.getWritePointer(i), (float*)out, 2 * (fftLength / 2 + 1));
    }
    
}

void MainComponent::getNextAudioBlock(const AudioSourceChannelInfo& bufferToFill)
{
    // Limpiamos el buffer de salida para poder utilizarlo
    bufferToFill.clearActiveBufferRegion();

    //auto numInputChannels = fileBuffer.getNumChannels();
    //auto numOutputChannels = bufferToFill.buffer->getNumChannels();
             
    //==============================================================================
    //================================= CREAR AUDIO ================================
    //==============================================================================

    if (state == playing)
    {
        // Cogemos los elementos para poder leer sus datos de posiciones
        Array<SpherePanner::MyElement*> myElements = sphere.getMyElements();

        // Guardamos las posiciones de los elementos en nuestros arrays de acimut, elevación y ganancia
        for (int i = 0; i < elements; i++)
        {
            Vector3D<float> coor = myElements[i]->getCoordinates();
            azimuth[i] = degreesToRadians(coor.x);
            elevation[i] = degreesToRadians(coor.y);
            gain[i] = coor.z * -0.0893 + 1.1339;
         };

        // Dependiendo del modo de salida, se binauralizará o se creará la señal Ambisonics
        if (outMode == headphoneConfig)
        {

            //==============================================================================
            //============================== CREAR AMBISONICS ==============================
            //==============================================================================

            // Creamos las variables de canales de entradas, salida, samples... y le marcamos
            // la longitud al buffer con la señal Ambisoncis
            const int nChOut = outputChannels;
            const int nChIn = elements;
            auto outputSamplesOffset = bufferToFill.startSample;
            auto bufferSamplesRemaining = fileBuffer.getNumSamples() - position;
            auto outputSamplesRemaining = bufferToFill.numSamples;
            auto samplesThisTime = jmin(outputSamplesRemaining, bufferSamplesRemaining);
            
            // Comenzamos a coger los datos de cada canal de entrada y crearemos las coordenadas esféricas
            for (int i = 0; i < nChIn; i++) {

                // Dependiendo si está activado el solo o el mute, habrá que quitarle el sonido o no
                float currGain = 0.0f;
                if (myElements[i]->getActive())
                {
                    currGain = gain[i].load();
                }
                else
                {
                    currGain = Decibels::decibelsToGain(-100);
                }

                // Cogemos el azimut y elevación ya convertidos a radianes y las pasamos a esféricas
                const float azimuthInRad = azimuth[i].load();
                const float elevationInRad = elevation[i].load();
                const Vector3D<float> pos{ Conversions<float>::sphericalToCartesian(azimuthInRad, elevationInRad) };

                // Para terminar, conseguimos las coordenadas esféricas y los metemos al buffer para reproducirlos
                SHEval3(pos.x, pos.y, pos.z, SH[i]);
                //FloatVectorOperations::multiply(SH[i], SH[i], n3d2sn3d, nChOut);

                // Multiplicamos los armónicos esféricos y la matriz de decodificación
                // Para ello, rellenamos la matriz de armónicos con los SH (trasponer el vector)
                for (int ch = 0; ch < 16; ++ch)
                {
                    ambiBuffer.addFrom(ch, 0, fileBuffer, i, position, samplesThisTime, SH[i][ch] * currGain);
                };

            };

            outputSamplesRemaining -= samplesThisTime;
            //outputSamplesOffset += samplesThisTime;
            position += samplesThisTime;

            if (position == fileBuffer.getNumSamples())
                position = 0;
            
            //==============================================================================
            //============================== BINAURALIZACIÓN ===============================
            //==============================================================================

            ScopedNoDenormals noDenormals;

            if (bufferToFill.buffer->getNumChannels() < 2)
            {
                bufferToFill.buffer->clear();
                return;
            }

            const int nCh = 16;
            const int L = ambiBuffer.getNumSamples();
            const int ergL = overlapBuffer.getNumSamples();
            const int overlap = irLengthMinusOne;
            const int copyL = jmin(L, overlap); // copy max L samples of the overlap data

            for (int ch = 1; ch < nCh; ++ch)
                ambiBuffer.applyGain(ch, 0, ambiBuffer.getNumSamples(), sn3d2n3d[ch]);

            FloatVectorOperations::clear((float*)accumMid, fftLength + 2);
            FloatVectorOperations::clear((float*)accumSide, fftLength + 2);

            const int nZeros = fftLength - L;

            //compute mid signal in frequency domain
            for (int midix = 0; midix < nMidCh; ++midix)
            {
                int ch = mix2cix[midix];
                FloatVectorOperations::clear(&in[L], nZeros); // TODO: only last part
                FloatVectorOperations::copy(in, ambiBuffer.getReadPointer(ch), L);
                fftwf_execute(fftForward);

                fftwf_complex* tfMid = (fftwf_complex*)irsFrequencyDomain.getReadPointer(ch);

                for (int i = 0; i < fftLength / 2 + 1; ++i)
                {
                    accumMid[i][0] += out[i][0] * tfMid[i][0] - out[i][1] * tfMid[i][1]; //real part
                    accumMid[i][1] += out[i][1] * tfMid[i][0] + out[i][0] * tfMid[i][1]; //imag part
                }

            }

            //compute side signal in frequency domain
            for (int sidix = 0; sidix < nSideCh; ++sidix)
            {
                int ch = six2cix[sidix];

                FloatVectorOperations::clear(&in[L], nZeros); // TODO: only last part
                FloatVectorOperations::copy(in, ambiBuffer.getReadPointer(ch), L);
                fftwf_execute(fftForward);

                fftwf_complex* tfSide = (fftwf_complex*)irsFrequencyDomain.getReadPointer(ch);

                for (int i = 0; i < fftLength / 2 + 1; ++i)
                {
                    accumSide[i][0] += out[i][0] * tfSide[i][0] - out[i][1] * tfSide[i][1];
                    accumSide[i][1] += out[i][1] * tfSide[i][0] + out[i][0] * tfSide[i][1];
                }

            }

            fftwf_execute(fftBackwardMid);
            fftwf_execute(fftBackwardSide);

            /// MS -> LR
            FloatVectorOperations::copy(bufferToFill.buffer->getWritePointer(1), ifftOutputMid, L);
            FloatVectorOperations::copy(bufferToFill.buffer->getWritePointer(0), ifftOutputMid, L);
            FloatVectorOperations::add(bufferToFill.buffer->getWritePointer(1), ifftOutputSide, L);
            FloatVectorOperations::subtract(bufferToFill.buffer->getWritePointer(0), ifftOutputSide, L);

            FloatVectorOperations::add(bufferToFill.buffer->getWritePointer(1), overlapBuffer.getWritePointer(0), copyL);
            FloatVectorOperations::add(bufferToFill.buffer->getWritePointer(0), overlapBuffer.getWritePointer(1), copyL);

            if (copyL < overlap) // there is some overlap left, want some?
            {
                const int howManyAreLeft = overlap - L;

                //shift the overlap buffer to the left
                FloatVectorOperations::copy(overlapBuffer.getWritePointer(0), overlapBuffer.getReadPointer(0, L), howManyAreLeft);
                FloatVectorOperations::copy(overlapBuffer.getWritePointer(1), overlapBuffer.getReadPointer(1, L), howManyAreLeft);

                //clear the tail
                FloatVectorOperations::clear(overlapBuffer.getWritePointer(0, howManyAreLeft), ergL - howManyAreLeft);
                FloatVectorOperations::clear(overlapBuffer.getWritePointer(1, howManyAreLeft), ergL - howManyAreLeft);

                //MS -> LR
                FloatVectorOperations::add(overlapBuffer.getWritePointer(0), &ifftOutputMid[L], irLengthMinusOne);
                FloatVectorOperations::add(overlapBuffer.getWritePointer(1), &ifftOutputMid[L], irLengthMinusOne);
                FloatVectorOperations::add(overlapBuffer.getWritePointer(0), &ifftOutputSide[L], irLengthMinusOne);
                FloatVectorOperations::subtract(overlapBuffer.getWritePointer(1), &ifftOutputSide[L], irLengthMinusOne);
            }
            else
            {
                // MS -> LR
                FloatVectorOperations::copy(overlapBuffer.getWritePointer(0), &ifftOutputMid[L], irLengthMinusOne);
                FloatVectorOperations::copy(overlapBuffer.getWritePointer(1), &ifftOutputMid[L], irLengthMinusOne);
                FloatVectorOperations::add(overlapBuffer.getWritePointer(0), &ifftOutputSide[L], irLengthMinusOne);
                FloatVectorOperations::subtract(overlapBuffer.getWritePointer(1), &ifftOutputSide[L], irLengthMinusOne);
            }
            
            for (int ch = 2; ch < bufferToFill.buffer->getNumChannels(); ++ch)
               bufferToFill.buffer->clear(ch, 0, bufferToFill.buffer->getNumSamples());
            
            for (int ch =0; ch < ambiBuffer.getNumChannels(); ++ch)
                ambiBuffer.clear(ch, 0, ambiBuffer.getNumSamples());
                      
        }
        else if( outMode == labConfig && avaiableOutputs >= 8)
        {
            //==============================================================================
            //============================== CREAR AMBISONICS ==============================
            //==============================================================================

            // Creamos las variables de canales de entradas, salida, orden ambisonics, samples...
            const int nChOut = outputChannels;
            const int nChIn = elements;

            auto outputSamplesOffset = bufferToFill.startSample;
            //auto outputSamplesRemaining = bufferToFill.numSamples;
            auto outputSamplesRemaining = bufferToFill.numSamples;
            auto bufferSamplesRemaining = fileBuffer.getNumSamples() - position;
            auto samplesThisTime = jmin(outputSamplesRemaining, bufferSamplesRemaining);
            //auto numOutputChannels = bufferToFill.buffer->getNumChannels();
            
            // Cargamos la matriz de decodificación y creamos la de los armónicos
            Matrix <float> decodingMatrix(nChOut, 16);
            Matrix<float> harmonicsMatrix(16, 1);

            switch (outMode)
            {
                case labConfig:
                    decodingMatrix = decodingMatrixArray->getUnchecked(0);
                    break;
                case sphereConfig:
                    decodingMatrix = decodingMatrixArray->getUnchecked(1);
                    break;
                default:
                    break;
            };

            // Comenzamos a coger los datos de cada canal de entrada y crearemoslas coordenadas esféricas
            for (int i = 0; i < nChIn; i++) {

                //FloatVectorOperations::copy(_SH[i], SH[i], nChOut);

                // Dependiendo si está activado el solo o el mute, habrá que quitarle el sonido o no
                float currGain = 0.0f;
                if (myElements[i]->getActive())
                {
                    currGain = gain[i].load();
                }
                else
                {
                    currGain = Decibels::decibelsToGain(-100);
                }

                // Cogemos el azimut y elevación ya convertidos a radianes y las pasamos a esféricas
                const float azimuthInRad = azimuth[i].load();
                const float elevationInRad = elevation[i].load();
                const Vector3D<float> pos{ Conversions<float>::sphericalToCartesian(azimuthInRad, elevationInRad) };

                // Para terminar, conseguimos las coordenadas esféricas y los metemos al buffer para reproducirlos
                SHEval3(pos.x, pos.y, pos.z, SH[i]);
                FloatVectorOperations::multiply(SH[i], SH[i], n3d2sn3d, nChOut);

                // Multiplicamos los armónicos esféricos y la matriz de decodificación
                // Para ello, rellenamos la matriz de armónicos con los SH (trasponer el vector)
                for (int ch = 0; ch < 16; ++ch)
                    harmonicsMatrix(ch, 0) = SH[i][ch];

                Matrix<float> outMatrix = decodingMatrix * harmonicsMatrix;

                for (int ch = 0; ch < nChOut; ++ch)
                    bufferToFill.buffer->addFrom(ch, outputSamplesOffset, fileBuffer, i, position, samplesThisTime, outMatrix(ch, 0) * currGain);

            };

            outputSamplesRemaining -= samplesThisTime;
            outputSamplesOffset += samplesThisTime;
            position += samplesThisTime;

            if (position == fileBuffer.getNumSamples())
                position = 0;

        };
    }
    else if (state == paused)
    {
        cout << "Pause" << endl;
    }
    else if (state == stopped)
    {
        position = 0;
    };

}


void MainComponent::releaseResources()
{
    // This will be called when the audio device stops, or when it is being
    // restarted due to a setting change.

    // For more details, see the help for AudioProcessor::releaseResources()

}

//==============================================================================
//============================= PAINT Y RESIZED ================================
//==============================================================================
void MainComponent::paint(Graphics& g)
{
    g.fillAll(getLookAndFeel().findColour(ResizableWindow::backgroundColourId));
}

void MainComponent::resized()
{
    // La ventana está dividida en cuatro contenedores, creados con un grid
    Grid grid;
    using Track = Grid::TrackInfo;

    // Tiene tres filas y dos columnas
    grid.templateRows = { Track(1_fr), Track(8_fr), Track(1_fr) };
    grid.templateColumns = { Track(6_fr), Track(4_fr) };

    // El header y el footer usan las dos columnas, por lo que se expanden
    grid.items = { GridItem(header).withArea({},GridItem::Span(2)), GridItem(mainPanel), GridItem(demode), GridItem(footer).withArea({},GridItem::Span(2)) };

    grid.performLayout(getLocalBounds());

    // Le damos el tamaño  del mainPanel a la esfera
    sphere.setBounds(mainPanel.getLocalBounds().reduced(10, 10));
}


//==============================================================================
//================================ SLIDERS =====================================
//==============================================================================
// Cada vez que un slider sea modificado, llegrá a esta función.  Aqui se mira
// cual es para poder actualizar los valores, al final se repinta la esfera
// con los nuevos valores
void MainComponent::sliderValueChanged(Slider* slider)
{
    // Cogemos la información de los elementos para guardar la nueva posición
    Array<SpherePanner::MyElement*> sphereArtists = sphere.getMyElements();

    // Por cada grupo de sliders, miraremos si se corresponden con el que se ha
    // movido y se guarda en el vector pos, el cual se pone como nueva posición
    // de los elementos en elemento de la esfera y en el de MainComponent
    for (int i = 0; i < elements; i++) {
        String name = newArtists[i]->getName();
        Vector3D<float> pos = sphereArtists[i]->getCoordinates();
        if (slider->getName() == name + "_az") {
            pos.x = slider->getValue();
        }
        else if (slider->getName() == name + "_el") {
            pos.y = slider->getValue();
        }
        else if (slider->getName() == name + "_g") {
            pos.z = slider->getValue();
        }
        sphereArtists[i]->setCoordinates(pos);
        newArtists[i]->setCoor(pos);
    };

    // Finalmente seredibuja la esfera para actualizar las posiciones
    sphere.repaint();
}

//==============================================================================
//============ ACTIVAR/DESACTIVAR BOTONES MUTE, SOLO, PLAY, PUASE ==============
//==============================================================================
// Esta función se encarga de los botones. Si se llega por medio de un botón solo
// o mute cambia el estado de los elementos. Si se llega por los botones play,
// pause o stop se cambia el estado de reproducción
void MainComponent::buttonClicked(Button* button)
{
    // Cambiamos el estado del botón
    button->setToggleState(!button->getToggleState(), dontSendNotification);

    // Este if mira si el botón es del tipo solo/mute o play/pause/stop
    if (button->getRadioGroupId() != 9)
    {
        // Cogemos los elementos de la esfera para poder modificar su estado
        Array<SpherePanner::MyElement*> myElements = sphere.getMyElements();

        for (int i = 0; i < elements; i++) {
            // Si  el botón es de solo, activamos el elemento correspondiente y
            // desactivamos el resto, es decir, los ponemos a mute
            if (button->getName() == (newArtists[i]->getName() + "_s")) {
                if (button->getToggleState())
                {
                    myElements[i]->setActive(button->getToggleState());
                };
                for (int j = 0; j < elements; j++) {
                    if (j != i) {
                        muteButtons[j]->setToggleState(button->getToggleState(), dontSendNotification);
                        myElements[j]->setActive(!button->getToggleState());
                    }
                }
            }
            // Si  el botón es de mute, desactivamos su elemento correspondiente
            if (button->getName() == (newArtists[i]->getName() + "_m")) {
                myElements[i]->setActive(!button->getToggleState());
            }
        };
    }
    else
    {
        // Si se ha llegado aqui es porque se han presionado los botones 
        // play/pause/stop.  Dependiendo de cual haya sido, se cmabia el estado
        // de reproducción del programa
        if (button->getName() == "Play Button")
        {
            state = playing;
        }
        else if (button->getName() == "Pause Button")
        {
            state = paused;
        }
        else if (button->getName() == "Stop Button")
        {
             state = stopped;
        };
    };

    // Finalmente seredibuja la esfera para actualizar los botones
    sphere.repaint();

}

void MainComponent::buttonStateChanged(Button* button) {};

//==============================================================================
//=========================== PARSEAR INFORMACIÓN ==============================
//==============================================================================
// Esta función es la encargada de coger toda la información de la escena, la 
//cual llega como un json
void MainComponent::parser(var info)
{
    // Cogemos el json y o pasamos a String, para poder meterlo en la variable
    // parsedJson
    String data = JSON::toString(info);
    var parsedJson;

    // Si el json es correcto, se procede a leerlo
    if (JSON::parse(data, parsedJson).ok()) {
        
        // Lo primero  es coger el número de elementos que tiene la escena, este
        // está almacenado en la etiqueta 'Elements'
        elements = parsedJson["Elements"];

        // Elementoa elemento, se cogen los datos de nombre, color, posición, pista
        // de sonido e imagen.  Con esa información, se crea un nuevo artista. Si
        // la información es nula, es decir, no existe dicho elemento, no se creará
        // el artista nuevo

        // ELEMENTO 1
        String name_0 = parsedJson["Element_0"]["Name"];
        int colour_0 = parsedJson["Element_0"]["Colour"];
        int azimut_0 = parsedJson["Element_0"]["Azimut"];
        int elevation_0 = parsedJson["Element_0"]["Elevation"];
        float gain_0 = parsedJson["Element_0"]["Gain"];
        String track_0 = parsedJson["Element_0"]["Track"];
        String icon_0 = parsedJson["Element_0"]["Icon"];

        if (name_0 != "")
        {
            if (azimut_0 <= 0) { azimut_0 = 0; };
            if (azimut_0 >= 360) { azimut_0 = 360; };
            if (elevation_0 <= 0) { elevation_0 = 0; };
            if (elevation_0 >= 360) { elevation_0 = 360; };
            if (gain_0 <= 1.5) { gain_0 = 1.5; };
            if (gain_0 >= 12.0) { gain_0 = 12.0; };
            Artist* newArtist = new Artist(name_0, icon_0, track_0, Vector3D<float>(azimut_0, elevation_0, gain_0), colourSelector(colour_0));
            newArtists.add(newArtist);
            colourIds.add(colour_0);
        };

        // ELEMENTO 2
        String name_1 = parsedJson["Element_1"]["Name"];
        int colour_1 = parsedJson["Element_1"]["Colour"];
        int azimut_1 = parsedJson["Element_1"]["Azimut"];
        int elevation_1 = parsedJson["Element_1"]["Elevation"];
        float gain_1 = parsedJson["Element_1"]["Gain"];
        String track_1 = parsedJson["Element_1"]["Track"];
        String icon_1 = parsedJson["Element_1"]["Icon"];

        if (name_1 != "")
        {
            if (azimut_1 <= 0) { azimut_1 = 0; };
            if (azimut_1 >= 360) { azimut_1 = 360; };
            if (elevation_1 <= 0) { elevation_1 = 0; };
            if (elevation_1 >= 360) { elevation_1 = 360; };
            if (gain_1 <= 1.5) { gain_1 = 1.5; };
            if (gain_1 >= 12.0) { gain_1 = 12.0; };
            Artist* newArtist = new Artist(name_1, icon_1, track_1, Vector3D<float>(azimut_1, elevation_1, gain_1), colourSelector(colour_1));
            newArtists.add(newArtist);
            colourIds.add(colour_1);
        };

        // ELEMENTO 3
        String name_2 = parsedJson["Element_2"]["Name"];
        int colour_2 = parsedJson["Element_2"]["Colour"];
        int azimut_2 = parsedJson["Element_2"]["Azimut"];
        int elevation_2 = parsedJson["Element_2"]["Elevation"];
        float gain_2 = parsedJson["Element_2"]["Gain"];
        String track_2 = parsedJson["Element_2"]["Track"];
        String icon_2 = parsedJson["Element_2"]["Icon"];

        if (name_2 != "")
        {
            if (azimut_2 <= 0) { azimut_2 = 0; };
            if (azimut_2 >= 360) { azimut_2 = 360; };
            if (elevation_2 <= 0) { elevation_2 = 0; };
            if (elevation_2 >= 360) { elevation_2 = 360; };
            if (gain_2 <= 1.5) { gain_2 = 1.5; };
            if (gain_2 >= 12.0) { gain_2 = 12.0; };
            Artist* newArtist = new Artist(name_2, icon_2, track_2, Vector3D<float>(elevation_2, azimut_2, gain_2), colourSelector(colour_2));
            newArtists.add(newArtist);
            colourIds.add(colour_2);
        };

        // ELEMENTO 4
        String name_3 = parsedJson["Element_3"]["Name"];
        int colour_3 = parsedJson["Element_3"]["Colour"];
        int azimut_3 = parsedJson["Element_3"]["Azimut"];
        int elevation_3 = parsedJson["Element_3"]["Elevation"];
        float gain_3 = parsedJson["Element_3"]["Gain"];
        String track_3 = parsedJson["Element_3"]["Track"];
        String icon_3 = parsedJson["Element_3"]["Icon"];

        if (name_3 != "")
        {
            if (azimut_3 <= 0) { azimut_3 = 0; };
            if (azimut_3 >= 360) { azimut_3 = 360; };
            if (elevation_3 <= 0) { elevation_3 = 0; };
            if (elevation_3 >= 360) { elevation_3 = 360; };
            if (gain_3 <= 1.5) { gain_3 = 1.5; };
            if (gain_3 >= 12.0) { gain_3 = 12.0; };
            Artist* newArtist = new Artist(name_3, icon_3, track_3, Vector3D<float>(azimut_3, elevation_3, gain_3), colourSelector(colour_3));
            newArtists.add(newArtist);
            colourIds.add(colour_3);
        };

        // ELEMENTO 5
        String name_4 = parsedJson["Element_4"]["Name"];
        int colour_4 = parsedJson["Element_4"]["Colour"];
        int azimut_4 = parsedJson["Element_4"]["Azimut"];
        int elevation_4 = parsedJson["Element_4"]["Elevation"];
        float gain_4 = parsedJson["Element_4"]["Gain"];
        String track_4 = parsedJson["Element_4"]["Track"];
        String icon_4 = parsedJson["Element_4"]["Icon"];

        if (name_4 != "")
        {
            if (azimut_4 <= 0) { azimut_4 = 0; };
            if (azimut_4 >= 360) { azimut_4 = 360; };
            if (elevation_4 <= 0) { elevation_4 = 0; };
            if (elevation_4 >= 360) { elevation_4 = 360; };
            if (gain_4 <= 1.5) { gain_4 = 1.5; };
            if (gain_4 >= 12.0) { gain_4 = 12.0; };
            Artist* newArtist = new Artist(name_4, icon_4, track_4, Vector3D<float>(azimut_4, elevation_4, gain_4), colourSelector(colour_4));
            newArtists.add(newArtist);
            colourIds.add(colour_4);
        };

        // ELEMENTO 6
        String name_5 = parsedJson["Element_5"]["Name"];
        int colour_5 = parsedJson["Element_5"]["Colour"];
        int azimut_5 = parsedJson["Element_5"]["Azimut"];
        int elevation_5 = parsedJson["Element_5"]["Elevation"];
        float gain_5 = parsedJson["Element_5"]["Gain"];
        String track_5 = parsedJson["Element_5"]["Track"];
        String icon_5 = parsedJson["Element_5"]["Icon"];

        if (name_5 != "")
        {
            if (azimut_5 <= 0) { azimut_5 = 0; };
            if (azimut_5 >= 360) { azimut_5 = 360; };
            if (elevation_5 <= 0) { elevation_5 = 0; };
            if (elevation_5 >= 360) { elevation_5 = 360; };
            if (gain_5 <= 1.5) { gain_5 = 1.5; };
            if (gain_5 >= 12.0) { gain_5 = 12.0; };
            Artist* newArtist = new Artist(name_5, icon_5, track_5, Vector3D<float>(azimut_5, elevation_5, gain_5), colourSelector(colour_5));
            newArtists.add(newArtist);
            colourIds.add(colour_5);
        };

        // ELEMENTO 7
        String name_6 = parsedJson["Element_6"]["Name"];
        int colour_6 = parsedJson["Element_6"]["Colour"];
        int azimut_6 = parsedJson["Element_6"]["Azimut"];
        int elevation_6 = parsedJson["Element_6"]["Elevation"];
        float gain_6 = parsedJson["Element_6"]["Gain"];
        String track_6 = parsedJson["Element_6"]["Track"];
        String icon_6 = parsedJson["Element_6"]["Icon"];

        if (name_6 != "")
        {
            if (azimut_6 <= 0) { azimut_6 = 0; };
            if (azimut_6 >= 360) { azimut_6 = 360; };
            if (elevation_6 <= 0) { elevation_6 = 0; };
            if (elevation_6 >= 360) { elevation_6 = 360; };
            if (gain_6 <= 1.5 / 4) { gain_6 = 1.5; };
            if (gain_6 >= 12.0) { gain_6 = 12.0; };
            Artist* newArtist = new Artist(name_6, icon_6, track_6, Vector3D<float>(azimut_6, elevation_6, gain_6), colourSelector(colour_6));
            newArtists.add(newArtist);
            colourIds.add(colour_6);
        };

        // ELEMENTO 8
        String name_7 = parsedJson["Element_7"]["Name"];
        int colour_7 = parsedJson["Element_7"]["Colour"];
        int azimut_7 = parsedJson["Element_7"]["Azimut"];
        int elevation_7 = parsedJson["Element_7"]["Elevation"];
        float gain_7 = parsedJson["Element_7"]["Gain"];
        String track_7 = parsedJson["Element_7"]["Track"];
        String icon_7 = parsedJson["Element_7"]["Icon"];

        if (name_7 != "")
        {
            if (azimut_7 <= 0) { azimut_7 = 0; };
            if (azimut_7 >= 360) { azimut_7 = 360; };
            if (elevation_7 <= 0) { elevation_7 = 0; };
            if (elevation_7 >= 360) { elevation_7 = 360; };
            if (gain_7 <= 1.5) { gain_7 = 1.5; };
            if (gain_7 >= 12.0) { gain_7 = 12.0; };
            Artist* newArtist = new Artist(name_7, icon_7, track_7, Vector3D<float>(azimut_7, elevation_7, gain_7), colourSelector(colour_7));
            newArtists.add(newArtist);
            colourIds.add(colour_7);
        };

        // En este punto, repintams toda la ventana para que aparezcan los artistas
        header.repaint();
        sphere.repaint();
        demode.artists = newArtists;
        demode.repaint();
        footer.repaint();

    }
    else {
        // Si ha habido algún error de lectura saldrá una ventana de alerta
        AlertWindow* alert = new AlertWindow("ERROR", "Algo va mal", juce::AlertWindow::WarningIcon);
        alert->showOkCancelBox(juce::AlertWindow::WarningIcon, "Error", "Lectura escena fallida");
    };


}

//==============================================================================
//=========================== SELECTOR DE COLORES ==============================
//==============================================================================
// Esta función es la encargada de devolver el color correspondiente al número que
// se le introduce
Colour MainComponent::colourSelector(int colourId)
{
    Colour outColour;

    switch (colourId) {
    case black:         outColour = Colours::black;         break;
    case blue:          outColour = Colours::blue;          break;
    case lightblue:     outColour = Colours::lightblue;     break;
    case brown:         outColour = Colours::brown;         break;
    case cyan:          outColour = Colours::cyan;          break;
    case green:         outColour = Colours::green;         break;
    case lightgreen:    outColour = Colours::lightgreen;    break;
    case magenta:       outColour = Colours::magenta;       break;
    case orange:        outColour = Colours::orange;        break;
    case pink:          outColour = Colours::pink;          break;
    case purple:        outColour = Colours::purple;        break;
    case red:           outColour = Colours::red;           break;
    case violet:        outColour = Colours::violet;        break;
    case yellow:        outColour = Colours::yellow;        break;

    default:
        break;
    }

    return outColour;
}

//==============================================================================
//=========================== CREAR Y GUARDAR JSON =============================
//==============================================================================
// Esta función crea un json con la escena actual  y lo guarda en la dirección 
// que se marque
void MainComponent::saveFile()
{
    // Creamos un DynamicObject, que será el json, donde le introducimos todos
    // los datos
    DynamicObject* output = new DynamicObject();
    output->setProperty("Elements", elements);

    for (int i = 0; i < elements; i++) {
        Vector3D<float> pos = newArtists[i]->getCoor();
        DynamicObject* newElement = new DynamicObject();
        newElement->setProperty("Name", newArtists[i]->getName());
        newElement->setProperty("Colour", colourIds[i]);
        newElement->setProperty("Azimut", (int)pos.x);
        newElement->setProperty("Elevation", (int)pos.y);
        newElement->setProperty("Gain", pos.z);
        newElement->setProperty("Track", newArtists[i]->getTrack());
        newElement->setProperty("Icon", newArtists[i]->getIconPath());
        String label = "Element_" + to_string(i);
        output->setProperty(label, newElement);
    };

    // Creamos el json y abrimos una ventana para la selección de carpeta y el
    // nombre que tendrá el archivo
    var json(output);
    FileChooser folderChooser("Save configuration", {}, "*.json");
    folderChooser.browseForFileToSave(true);
    File newFile(folderChooser.getResult());
    newFile.appendText(JSON::toString(json));

}

//==============================================================================
//============================ MENÚ SELECCIÓN SALIDA ===========================
//==============================================================================
// Esta función crea un menú desplegable con lasopciones de salida de audio:
// auriculares, 8 altavoces o esfera. En los auriculares se permite seleccionar
// el tipo que se usa
void MainComponent::openPopup()
{
    // Primero consegumos el número de salidas disponibles, ya que si son menos
    // de 8 no se dejará seleccionar los 8 altavoces y si es menor de 24 la esfera
    deviceManager.getAudioDeviceSetup();
    auto* device = deviceManager.getCurrentAudioDevice();
    auto activeOutputChannels = device->getActiveOutputChannels();
    auto maxOutputChannels = activeOutputChannels.countNumberOfSetBits();
    avaiableOutputs = (int)maxOutputChannels;

    // Creamos las variable que nose dejarán cambiar la foto del botón
    int speakerSize;
    String speakerName;
    Image speakerIcon;

    // Creamos el mainMenu que tiene tres apartados: Headphones (altavoces),
    // 8 loudspeakrs y Sphere
    PopupMenu mainMenu;
    mainMenu.addItem(1, "Headphones", avaiableOutputs >= 2, popUpSelection == 1);
    mainMenu.addItem(2, "8 loudspeakers", avaiableOutputs >= 8, popUpSelection == 2);
    mainMenu.addItem(3, "Sphere", avaiableOutputs >= 24, popUpSelection == 3);
   
    // Se muestra el menú y recoge la selección
    int selection = mainMenu.show();
    popUpSelection = selection;

    // Dependiendo cual sea se modifica el modo de salida del programa (outMode)
    // y se se ponen las salidas que se han seleccionado
    if (selection == 1)
    {
        // Cambiamos a modo auriculares, con 2 salidas
        outMode = headphoneConfig;
        outputChannels = 2;

        // Le decimos a la esfera que los iconos deben ser con auriculares
        // y ponemos el icono del auricular como botón
        sphere.setHp(true);
        speakerName = "hp_png";
        auto* speakerData = BinaryData::getNamedResource(speakerName.toUTF8(), speakerSize);
        speakerIcon = ImageFileFormat::loadFrom(speakerData, speakerSize);
    }
    else if (selection == 2)
    {        
        // Cambiamos a modo laboratorio, con 8 salidas
        outMode = labConfig;
        outputChannels = 8;

        // Le decimos a la esfera que los iconos deben ser sin auriculares
        // y ponemos el icono del monitor como botón
        sphere.setHp(false);
        speakerName = "speaker_png";
        auto* speakerData = BinaryData::getNamedResource(speakerName.toUTF8(), speakerSize);
        speakerIcon = ImageFileFormat::loadFrom(speakerData, speakerSize);
    }
    else if (selection == 3)
    {
        // Cambiamos a modo esfera, con 24 salidas
        outMode = sphereConfig;
        outputChannels = 24;

        // Le decimos a la esfera que los iconos deben ser sin auriculares
        // y ponemos el icono de la esfera como botón
        sphere.setHp(false);
        speakerName = "sphere_png";
        auto* speakerData = BinaryData::getNamedResource(speakerName.toUTF8(), speakerSize);
        speakerIcon = ImageFileFormat::loadFrom(speakerData, speakerSize);
        
    };

    // Le damos el icono correspondientre y repintamos el header para que cambie
    speakerButton.setImages(false, true, true, speakerIcon, 0.6f, {}, speakerIcon, 1.0f, {}, speakerIcon, 1.0f, {}, 0);
    header.repaint();
   
}

//==============================================================================
//======================= USO DE CPU Y DISPOSITIVO SALIDA ======================
//==============================================================================
// Esta función leera el estado de carga de la cpu y también el dispositivo que
// se está usando para la salida de audio. Se lellama cada medio segundo con el
// Timer
void MainComponent::timerCallback()
{
    // Leemos el dispositivo que se está usando y le pasamos la info al header
    deviceManager.getAudioDeviceSetup();
    auto* device = deviceManager.getCurrentAudioDevice();
    String deviceName = device->getName();
    auto activeOutputChannels = device->getActiveOutputChannels();
    avaiableOutputs = activeOutputChannels.countNumberOfSetBits();
    header.setInfo(1, deviceName);

    // Leemos cuanta cpu que se está usando y le pasamos la info al header
    auto cpu = deviceManager.getCpuUsage() * 100;
    header.setInfo(3, String(cpu, 2) + "%");
    
}
