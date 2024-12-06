#ifndef FRAME_H
#define FRAME_H

#include <SFML/Graphics.hpp>

using namespace sf;

class Frame
{
protected:
    // Frame
    int width;
    int height;

    Vector2f relative_pos;

    Color background_color;

    // Elements
    RectangleShape frame;

public:
    // Constructor
    Frame(int width, int height, Vector2f relative_pos, Color background_color);

    // Drawers
    void draw(RenderWindow &window);

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    Vector2i getSize() const { return Vector2i(width, height); }
    Vector2f getRelativePosition() const { return relative_pos; }
};

#endif // FRAME_H