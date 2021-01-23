#pragma once
#include <JuceHeader.h>
#include "resources/Conversions.h"
#include "resources/Quaternion.h"


//==============================================================================
//============================= FONDO DE LA ESFERA =============================
//==============================================================================
class SphereBackground : public Component
{
public:
    SphereBackground() : Component()
    {
        setBufferedToImage(true);     
    };
    ~SphereBackground() {};

    //==============================================================================
    //============================== SELECCIÓN TEXTO ===============================
    //==============================================================================
    // Dependiendo de la vista en la que se este se pintan los textos correspondientes
    // alrededor de la esfera
    void selectOwl(int owlNumber)
    {
        switch (owlNumber) {
        case 1:
            upText = "OVER";
            downText = "UNDER";
            rightText = "R\nI\nG\nH\nT";
            leftText = "L\nE\nF\nT";
            break;
        case 2:
            upText = "FRONT";
            downText = "BACK";
            rightText = "R\nI\nG\nH\nT";
            leftText = "L\nE\nF\nT";
            break;
        case 3:
            upText = "OVER";
            downText = "UNDER";
            rightText = "F\nR\nO\nN\nT";
            leftText = "B\nA\nC\nK";
            break;
        default:
            break;
        }
        repaint();
    };

    //==============================================================================
    //============================ PAINT Y RESIZED =================================
    //==============================================================================
    void resized() override
    {
        const Rectangle<float> sphere(getLocalBounds().reduced(10, 10).toFloat());

        radius = 0.5f * jmin(sphere.getWidth() - 10, sphere.getHeight() - 10);
        centre = getLocalBounds().getCentre();
        sphereArea.setBounds(0, 0, 2 * radius, 2 * radius);
        sphereArea.setCentre(centre.toFloat());
    };

    void paint(Graphics& g) override
    {
        // Dibujamos la esfera
        const Rectangle<float> bounds = getLocalBounds().toFloat();
        const float centreX = bounds.getCentreX();
        const float centreY = bounds.getCentreY();

        g.setColour(Colours::white);
        g.drawEllipse(centreX - radius, centreY - radius, 2.0f * radius, 2.0f * radius, 1.0f);

        g.setFont(getLookAndFeel().getTypefaceForFont(Font(12.0f, 1)));
        g.setFont(15.0f);
        g.drawText(upText, centreX - 30, centreY - radius - 15, 60, 12, Justification::centred);
        g.drawText(downText, centreX - 30, centreY + radius + 2, 60, 12, Justification::centred);
        g.drawFittedText(leftText, sphereArea.getX() - 20, centreY - 40, 10, 80, Justification::centred, 4);
        g.drawFittedText(rightText, sphereArea.getRight() + 10, centreY - 40, 10, 80, Justification::centred, 5);

        // El primer círculo será verde, imitando el espacio de la esfera real
        g.setColour(Colours::lime);
        Path circles;

        float rCirc = radius * (90 - 75) / 90;
        circles.addEllipse(centreX - rCirc, centreY - rCirc, 2.0f * rCirc, 2.0f * rCirc);
        g.fillPath(circles);

        // El resto de círculos serán blancos y se degradarán conforme aumenta el radio
        g.setColour(Colours::white.withMultipliedAlpha(0.2f));
        for (int deg = 60; deg >= 0; deg -= 15)
        {
            float rCirc = radius * (90 - deg) / 90;
            circles.addEllipse(centreX - rCirc, centreY - rCirc, 2.0f * rCirc, 2.0f * rCirc);
            g.fillPath(circles);
        }

        g.setColour(Colours::grey.withMultipliedAlpha(0.7f));
        g.strokePath(circles, PathStrokeType(.5f));

        ColourGradient gradient(Colours::grey.withMultipliedAlpha(0.7f), centreX, centreY, Colours::black.withMultipliedAlpha(0.1f), 0, 0, true);
        g.setGradientFill(gradient);

        Path line;
        line.startNewSubPath(centreX, centreY - radius);
        line.lineTo(centreX, centreY + radius);

        Path path;
        path.addPath(line);
        path.addPath(line, AffineTransform().rotation(0.25f * MathConstants<float>::pi, centreX, centreY));
        path.addPath(line, AffineTransform().rotation(0.5f * MathConstants<float>::pi, centreX, centreY));
        path.addPath(line, AffineTransform().rotation(0.75f * MathConstants<float>::pi, centreX, centreY));

        g.strokePath(path, PathStrokeType(0.5f));

    }

private:
    float radius = 1.0f;
    Rectangle<float> sphereArea;
    juce::Point<int> centre;
    String upText, downText, rightText, leftText;
    ImageButton frontView, upView, sideView;
};


//==============================================================================
//========================== ELEMENTOS DE LA ESFERA ============================
//==============================================================================
class SpherePanner : public Component
{
public:
    //==============================================================================
    //================================ CONSTRUCTOR =================================
    //==============================================================================
    SpherePanner() : Component()
    {
        setBufferedToImage(true);

        // Ponemos el fondo 
        addAndMakeVisible(background);

        // Creamos los botones para cmabiar de vista
        Image nullImg;

        int frontSize;
        String frontName = "owl_back_hp_png";
        auto* frontData = BinaryData::getNamedResource(frontName.toUTF8(), frontSize);
        Image frontOwl = ImageFileFormat::loadFrom(frontData, frontSize);
        frontView.setName("Front Button");
        frontView.setButtonText("Front");
        frontView.setImages(false, true, true, frontOwl, 0.6f, {}, frontOwl, 1.0f, {}, frontOwl, 1.0f, {}, 0);
        frontView.setTooltip("Switch to front view");
        frontView.setRadioGroupId(5, sendNotification);
        frontView.onClick = [this]() { selectOwl(1); frontView.setToggleState(!frontView.getToggleState(), dontSendNotification); };

        int upSize;
        String upName = "owl_plan_hp_png";
        auto* upData = BinaryData::getNamedResource(upName.toUTF8(), upSize);
        Image upOwl = ImageFileFormat::loadFrom(upData, upSize);
        upView.setName("Up Button");
        upView.setButtonText("Up");
        upView.setImages(false, true, true, upOwl, 0.6f, {}, upOwl, 1.0f, {}, upOwl, 1.0f, {}, 0);
        upView.setTooltip("Switch to up view");
        upView.setRadioGroupId(5, sendNotification);
        upView.setToggleState(true, dontSendNotification);
        upView.onClick = [this]() { selectOwl(2); upView.setToggleState(!upView.getToggleState(), dontSendNotification); };

        int sideSize;
        String sideName = "owl_profile_hp_png";
        auto* sideData = BinaryData::getNamedResource(sideName.toUTF8(), sideSize);
        Image sideOwl = ImageFileFormat::loadFrom(sideData, sideSize);
        sideView.setName("Side Button");
        sideView.setButtonText("Side");
        sideView.setImages(false, true, true, sideOwl, 0.6f, {}, sideOwl, 1.0f, {}, sideOwl, 1.0f, {}, 0);
        sideView.setTooltip("Switch to side view");
        sideView.setRadioGroupId(5, sendNotification);
        sideView.onClick = [this]() { selectOwl(3); sideView.setToggleState(!sideView.getToggleState(), dontSendNotification); };

        addAndMakeVisible(frontView);
        addAndMakeVisible(upView);
        addAndMakeVisible(sideView);

        // Inicializamos en vista de arriba, búho 2
        selectOwl(2);
    };

    ~SpherePanner() {};

    //==============================================================================
    //================================ ELEMENTOS ===================================
    //==============================================================================
    // Esta clase se usa para crear cada elemento de la escena
    class MyElement
    {
    public:
        MyElement() {}
        ~MyElement() {}

        void setColour(Colour newColour) { colour = newColour; }
        Colour getColour() { return colour; }

        void setTextColour(Colour newColour) { textColour = newColour; }
        Colour getTextColour() { return textColour; }

        void setCoordinates(Vector3D<float> newCoordinates) { coordinates = newCoordinates; }
        Vector3D<float> getCoordinates() { return coordinates; }

        void setActive(bool isActive) { active = isActive; }
        bool getActive() { return active; }

        void setLabel(String newLabel) { label = newLabel; }
        String getLabel() { return label; }

        void setGrabPriority(int newPriority) { grabPriority = newPriority; }
        int getGrabPriority() { return grabPriority; }

        void setGrabRadius(float newRadius) { grabRadius = newRadius; }
        float getGrabRadius() { return grabRadius; }

    private:
        Colour colour;
        Colour textColour;
        String label;
        Vector3D<float> coordinates;
        bool active;
        float grabRadius = 0.123f;
        int grabPriority = 0;
    };

    //==============================================================================
    //============================ AÑADIR ELEMENTO =================================
    //==============================================================================
    void addMyElement(MyElement* newElement)
    {
        myElements.add(newElement);
    }

    //==============================================================================
    //============================ GETTER ELEMENTOS ================================
    //==============================================================================
    Array<MyElement*> getMyElements()
    {
        return myElements;
    }

    //==============================================================================
    //============================ CAMBIO DE VISTA =================================
    //==============================================================================
    // Dependiendo de la vista, se pinta el búho correspondiente en el centro de la
    // esfera
    void selectOwl(int newOwl) {
        owlNumber = newOwl;
        int frontSize, upSize, sideSize;
        String frontName, upName, sideName;
        if (hp)
        {
            frontName = "owl_back_hp_png";
            upName = "owl_plan_hp_png";
            sideName = "owl_profile_hp_png";
        }
        else
        {
            frontName = "owl_back_png";
            upName = "owl_plan_png";
            sideName = "owl_profile_png";
        };

        auto* frontData = BinaryData::getNamedResource(frontName.toUTF8(), frontSize);
        auto* upData = BinaryData::getNamedResource(upName.toUTF8(), upSize);
        auto* sideData = BinaryData::getNamedResource(sideName.toUTF8(), sideSize);

        switch (newOwl) {
            case 1:
                owl = ImageFileFormat::loadFrom(frontData, frontSize);
                break;
            case 2:
                owl = ImageFileFormat::loadFrom(upData, upSize);
                break;
            case 3:
                owl = ImageFileFormat::loadFrom(sideData, sideSize);
                break;
            default:
                break;
        };
        background.selectOwl(newOwl);
        repaint();
    };
    
    void setHp(bool isHp) {
        hp = isHp;

        int frontSize, upSize, sideSize;
        String frontName, upName, sideName;
        if (isHp)
        {
            frontName = "owl_back_hp_png";
            upName = "owl_plan_hp_png";
            sideName = "owl_profile_hp_png";
        }
        else
        {
            frontName = "owl_back_png";
            upName = "owl_plan_png";
            sideName = "owl_profile_png";
        };

        auto* frontData = BinaryData::getNamedResource(frontName.toUTF8(), frontSize);
        auto* upData = BinaryData::getNamedResource(upName.toUTF8(), upSize);
        auto* sideData = BinaryData::getNamedResource(sideName.toUTF8(), sideSize);
        Image frontOwl = ImageFileFormat::loadFrom(frontData, frontSize);
        Image upOwl = ImageFileFormat::loadFrom(upData, upSize);
        Image sideOwl = ImageFileFormat::loadFrom(sideData, sideSize);

        frontView.setImages(false, true, true, frontOwl, 0.6f, {}, frontOwl, 1.0f, {},frontOwl, 1.0f, {}, 0);
        upView.setImages(false, true, true, upOwl, 0.6f, {}, upOwl, 1.0f, {}, upOwl, 1.0f, {}, 0);
        sideView.setImages(false, true, true, sideOwl, 0.6f, {}, sideOwl, 1.0f, {}, sideOwl, 1.0f, {}, 0);

        selectOwl(owlNumber);
    }

    //==============================================================================
    //============================ PAINT Y RESIZED =================================
    //==============================================================================
    void resized() override {
        background.setBounds(getLocalBounds());
        const Rectangle<float> sphere(getLocalBounds().reduced(10, 10).toFloat());

        radius = 0.5f * jmin(sphere.getWidth(), sphere.getHeight());
        centre = getLocalBounds().getCentre();
        sphereArea.setBounds(0, 0, 2 * radius, 2 * radius);
        sphereArea.setCentre(centre.toFloat());
    }

    void paintOverChildren(Graphics& g) override
    {
        // Cogemos el centro de la esfera e inicializamos pi y la fuente
        const Rectangle<float> bounds = getLocalBounds().toFloat();
        const float centreX = bounds.getCentreX();
        const float centreY = bounds.getCentreY();
        float pi = MathConstants<float>::pi;
        g.setFont(getLookAndFeel().getTypefaceForFont(Font(12.0f, 1)));

        // Dibujamos los botones de las vistas
        g.setColour(Colours::lightgrey);
        g.drawText("VIEW", 0, getHeight() - 50, 124, 10, Justification::centred);
        frontView.setBounds(0, getHeight() - 40, 40, 40);
        upView.setBounds(42, getHeight() - 40, 40, 40);
        sideView.setBounds(84, getHeight() - 40, 40, 40);

        // Recorremos los elementos para dibujarlos. Dependiendo si están por encima
        // o por debajo se pintarán antes o despues del búho
        for (int i = 0; i < myElements.size(); ++i)
        {
            // Cogemos el elemento y su posición
            SpherePanner::MyElement* handle = myElements.getUnchecked(i);
            Vector3D<float> pos = handle->getCoordinates();
            float posZ = ( (pos.z - 1.5) / 10.5) * (radius - radius / 4) + radius / 4;
            pos.z = posZ;

            const Colour colour = handle->getActive() ? handle->getColour() : Colours::grey;
            g.setColour(colour);
            
            // Creamos una serie de booleanos para saber en que posición se encuentra
            // cada elemento en la esfera y poder así crear un efecto 3D pintándolos 
            // debajo o encima del búho
            bool isBehindFrontX = pos.x <= 90 || pos.x >= 270;
            bool isBehindFrontY = pos.y <= 90 || pos.y >= 270;
            bool isBehindFront = isBehindFrontX && isBehindFrontY;
            bool isBehindSideY = pos.y <= 90 || pos.y >= 270;
            bool isBehindSide = pos.x <= 180 && isBehindSideY;

            // Dibujamos los puntos que se veran por debajo del búho
            if (owlNumber == 1 && isBehindFront) // Vista frontal
            {
                // Calculamos el diámetro, que cambiará dependiendo de la posiciíon para 
                // dar sensación de profundidad
                const float diam = 20.0f + 6.0f * -cos(pos.y * pi / 180) * cos(pos.x * pi / 180);
                
                // Calculamos el área de dibujo del punto (x,y,ancho,alto)
                const Rectangle<float> circleArea(centreX + pos.z * sin((pos.x + 180) * pi / 180) * cos((pos.y) * pi / 180) - diam / 2, centreY + pos.z * cos((pos.y + 90) * pi / 180) - diam / 2, diam, diam);
                Path panPos;
                panPos.addEllipse(circleArea);
                panPos.addEllipse(circleArea);
                g.strokePath(panPos, PathStrokeType(1.0f));
                if (pos.x != 90 && pos.x != 270)
                {
                    g.setColour(colour.withAlpha(0.3f));
                    g.drawEllipse(circleArea.withSizeKeepingCentre(1.3f * diam, 1.3f * diam), 0.9f);
                };
                g.fillPath(panPos);
                g.setColour(handle->getTextColour());
                g.setFont(10.0f);
                g.drawText(handle->getLabel(), circleArea.toNearestInt(), Justification::centred, false);
            }
            else if (owlNumber == 2 && pos.y > 180) // Vista desde arriba
            {
                // Calculamos el diámetro del punto, que cambiará dependiendo de la posiciíon 
                // para dar sensación de profundidad
                const float diam = 20.0f + 6.0f * sin(pos.y * pi / 180);
                // Calculamos el área de dibujo del punto (x,y,ancho,alto)
                const Rectangle<float> circleArea(centreX + pos.z * sin((pos.x + 180) * pi / 180) * cos((pos.y) * pi / 180) - diam / 2, centreY + pos.z * cos((pos.x + 180) * pi / 180) * cos((pos.y) * pi / 180) - diam / 2, diam, diam);
                Path panPos;
                panPos.addEllipse(circleArea);
                g.strokePath(panPos, PathStrokeType(1.0f));

                g.setColour(colour.withAlpha(0.3f));
                g.drawEllipse(circleArea.withSizeKeepingCentre(1.3f * diam, 1.3f * diam), 0.9f);

                g.fillPath(panPos);
                g.setColour(handle->getTextColour());
                g.setFont(10.0f);
                g.drawText(handle->getLabel(), circleArea.toNearestInt(), Justification::centred, false);
            }
            else if (owlNumber == 3 && isBehindSide) // Vista lateral
            {
                // Calculamos el diámetro del punto, que cambiará dependiendo de la posiciíon
                // para dar sensación de profundidad
                const float diam = 20.0f + 6.0f * -cos(pos.y * pi / 180) * sin(pos.x * pi / 180);
                
                // Calculamos el área de dibujo del punto (x,y,ancho,alto)
                const Rectangle<float> circleArea(centreX + pos.z * sin((pos.x + 90) * pi / 180) * cos((pos.y) * pi / 180) - diam / 2, centreY + pos.z * cos((pos.y + 90) * pi / 180) - diam / 2, diam, diam);
                Path panPos;
                panPos.addEllipse(circleArea);
                g.strokePath(panPos, PathStrokeType(1.0f));
                if (pos.x != 0 && pos.x != 180)
                {
                    g.setColour(colour.withAlpha(0.3f));
                    g.drawEllipse(circleArea.withSizeKeepingCentre(1.3f * diam, 1.3f * diam), 0.9f);
                };
                g.fillPath(panPos);
                g.setColour(handle->getTextColour());
                g.setFont(10.0f);
                g.drawText(handle->getLabel(), circleArea.toNearestInt(), Justification::centred, false);
            };

        }

        // Dibujamos el búho
        g.drawImageWithin(owl, centreX - 30, centreY - 30, 60, 60, true);

        // Dibujamos los puntos que se verán por encima del búho
        for (int i = 0; i < myElements.size(); ++i)
        {
            // Cogemos el elemento y su posición
            SpherePanner::MyElement* handle = myElements.getUnchecked(i);
            Vector3D<float> pos = handle->getCoordinates();
            float posZ = ((pos.z - 1.5) / 10.5) * (radius - radius / 4) + radius / 4;            pos.z = posZ;
            pos.z = posZ;

            const Colour colour = handle->getActive() ? handle->getColour() : Colours::grey;
            g.setColour(colour);
           
            // Creamos una serie de booleanos para saber en que posición se encuentra
            // cada elemento en la esfera y poder así crear un efecto 3D pintándolos 
            //  debajo o encima del búho
            bool isBehindFrontX = pos.x < 90 || pos.x > 270;
            bool isBehindFrontY = pos.y < 90 || pos.y > 270;
            bool isBehindFront = isBehindFrontX && isBehindFrontY;
            bool isBehindSideY = pos.y <= 90 || pos.y >= 270;
            bool isBehindSide = pos.x <= 180 && isBehindSideY;

            if (owlNumber == 1 && !isBehindFront) // Vista frontal
            {
                // Calculamos diámetro del punto, que cambiará dependiendo de la posiciíon 
                // para dar sensación de profundidad
                const float diam = 20.0f + 6.0f * -cos(pos.y * pi / 180) * cos(pos.x * pi / 180);

                // Calculamos el área de dibujo del punto (x,y,ancho,alto)
                const Rectangle<float> circleArea(centreX + pos.z * sin((pos.x + 180) * pi / 180) * cos((pos.y) * pi / 180) - diam / 2, centreY + pos.z * cos((pos.y + 90) * pi / 180) - diam / 2, diam, diam);
                Path panPos;
                panPos.addEllipse(circleArea);
                panPos.addEllipse(circleArea);
                g.strokePath(panPos, PathStrokeType(1.0f));
                g.fillPath(panPos);
                g.setColour(handle->getTextColour());
                g.setFont(15.0f);
                g.drawText(handle->getLabel(), circleArea.toNearestInt(), Justification::centred, false);
            }
            else if (owlNumber == 2 && pos.y <= 180) // Vista desde arriba
            {
                // Calculamos diámetro del punto, que cambiará dependiendo de la posiciíon 
                // para dar sensación de profundidad
                const float diam = 20.0f + 6.0f * sin(pos.y * pi / 180);
                // Calculamos el área de dibujo del punto (x,y,ancho,alto)
                const Rectangle<float> circleArea(centreX + pos.z * sin((pos.x + 180) * pi / 180) * cos((pos.y) * pi / 180) - diam / 2, centreY + pos.z * cos((pos.x + 180) * pi / 180) * cos((pos.y) * pi / 180) - diam / 2, diam, diam);
                Path panPos;
                panPos.addEllipse(circleArea);
                g.strokePath(panPos, PathStrokeType(1.0f));
                g.fillPath(panPos);
                g.setColour(handle->getTextColour());
                g.setFont(15.0f);
                g.drawText(handle->getLabel(), circleArea.toNearestInt(), Justification::centred, false);
            }
            else if (owlNumber == 3 && !isBehindSide) // Vista lateral
            {
                // Calculamos diámetro del punto, que cambiará dependiendo de la posiciíon
                // para dar sensación de profundidad
                const float diam = 20.0f + 6.0f * -cos(pos.y * pi / 180) * sin(pos.x * pi / 180);
                // Calculamos el área de dibujo del punto (x,y,ancho,alto)
                const Rectangle<float> circleArea(centreX + pos.z * sin((pos.x + 90) * pi / 180) * cos((pos.y) * pi / 180) - diam / 2, centreY + pos.z * cos((pos.y + 90) * pi / 180) - diam / 2, diam, diam);
                Path panPos;
                panPos.addEllipse(circleArea);
                g.strokePath(panPos, PathStrokeType(1.0f));
                bool transprent = pos.y >= 90 && pos.y <= 270;
                if (pos.x > 180 && transprent)
                {
                    g.setColour(colour.withAlpha(0.3f));
                    g.drawEllipse(circleArea.withSizeKeepingCentre(1.3f * diam, 1.3f * diam), 0.9f);
                };

                g.fillPath(panPos);
                g.setColour(handle->getTextColour());
                g.setFont(15.0f);
                g.drawText(handle->getLabel(), circleArea.toNearestInt(), Justification::centred, false);
            };
        };
    };
    
private:
    float radius = 1.0f;
    Rectangle<float> sphereArea;
    juce::Point<int> centre;
    int activeElem = -1;
    bool activeElemWasUpBeforeDrag;
    bool hp = true;
    Array<MyElement*> myElements;
    SphereBackground background;
    Image owl;
    int owlNumber;
    ImageButton frontView, upView, sideView;
};
