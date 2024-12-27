#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SFML/Graphics.hpp>
#include <functional>

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

    // Function
    std::function<void()> textBoxFunction;

public:
    // Constructor
    TextBox(int width, int height, Vector2f relative_pos, Color background_color);

    // Drawers
    void draw(RenderWindow &window);

    // Trigger
    void triggerFunction(Vector2i position);

    // Getters
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    Vector2i getSize() const { return Vector2i(width, height); }
    Vector2f getRelativePosition() const { return relative_pos; }
    Text &getText() { return text; }

    // Setters
    void setFont(Font font) { this->font = font; }
    void setTextBoxFunction(std::function<void()> textBoxFunction) { this->textBoxFunction = textBoxFunction; }
    void setText(std::string text) { this->text.setString(text); }
};

#endif // TEXT_BOX_H