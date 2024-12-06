#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SFML/Graphics.hpp>

using namespace sf;

class TextBox
{
private:
    // TextBox
    int width;
    int height;

    bool is_selected;

    // Figure
    Vector2f relative_pos;
    Color background_color;
    RectangleShape text_box;
    
    // Text
    Font font;
    Text text;


public:
    // Constructor
    TextBox(Vector2f relative_pos, int width, int height, Color background_color, Font font);

    // Drawers
    void draw(Window &window);

    // Trigger
    void triggerFunction(Vector2i position);
    
    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    Vector2i getSize() const { return Vector2i(width, height); }
    Vector2f getRelativePosition() const { return relative_pos; }

    // Setters

};


#endif // TEXT_BOX_H