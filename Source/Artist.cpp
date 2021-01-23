#include "Artist.h"

//==============================================================================
//================================== CONSTRUCCIÓN ==============================
//==============================================================================
Artist::Artist(String name, String pathIcon, String pathTrack, Vector3D<float> coor, Colour colour)
{
    // Si la ruta de la imagen es default, cargamos el icono como el búho
    // si es una ruta correcta cargamos esa imagen como icono
    Image newIcon;
    if (pathIcon == "default")
    {
        int dataSize;
        String dataName = "owl_front_hp_png";
        auto* data = BinaryData::getNamedResource(dataName.toUTF8(), dataSize);
        newIcon = ImageFileFormat::loadFrom(data, dataSize);
    }
    else
    {
        newIcon = ImageFileFormat::loadFrom(pathIcon);
    };

    // Añadimos todos los datos al objeto
    this->name = name;
    this->icon = newIcon;
    this->pathIcon = pathIcon;
    this->track = pathTrack;
    this->coor = coor;
    this->colour = colour;
}

Artist::~Artist()
{
}

//==============================================================================
//============================ GETTERS Y SETTERS ===============================
//==============================================================================
void Artist::setName(String name) {
    this->name = name;
}

String Artist::getName() {
    return name;
}

void Artist::setIcon(String path) {
    Image newIcon;
    if (path == "default")
    {
        int dataSize;
        String dataName = "owl_front_hp_png";
        auto* data = BinaryData::getNamedResource(dataName.toUTF8(), dataSize);
        newIcon = ImageFileFormat::loadFrom(data, dataSize);
    }
    else
    {
        newIcon = ImageFileFormat::loadFrom(path);
    };

    this->icon = newIcon;
    this->pathIcon = path;
}

Image Artist::getIcon() {
    return icon;
}

String Artist::getIconPath() {
    return pathIcon;
}

void Artist::setCoor(Vector3D<float> coor) {
    this->coor = coor;
}

Vector3D<float> Artist::getCoor() {
    return coor;
}

void Artist::setTrack(String path) {
    this->track = path;
}

String Artist::getTrack() {
    return track;
}

void Artist::setColour(Colour colour) {
    this->colour = colour;
}

Colour Artist::getColour() {
    return colour;
}