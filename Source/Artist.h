#pragma once
#include <JuceHeader.h>

using namespace std;

class Artist
{
public:

    Artist(String name, String pathIcon, String pathTrack, Vector3D<float> coor, Colour colour);
    ~Artist();

    void setName(String name);
    void setIcon(String path);
    void setTrack(String path);
    void setCoor(Vector3D<float> coor);
    void setColour(Colour colour);

    Image getIcon();
    String getIconPath();
    String getTrack();
    String getName();
    Vector3D<float> getCoor();
    Colour getColour();

private:

    String name;
    String pathIcon;
    String track;
    Image icon;
    Colour colour;
    Vector3D<float> coor;
};