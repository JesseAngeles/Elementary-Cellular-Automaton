#include "GUI/TextBox.h"

TextBox::TextBox(int width, int height, Vector2f relative_pos, Color background_color)
    : relative_pos(relative_pos), width(width), height(height), background_color(background_color)
{
    // Draw background
    text_box = RectangleShape(Vector2f(width, height));
    text_box.setPosition(relative_pos);
    text_box.setOutlineThickness(2);
    text_box.setOutlineColor(background_color);
    text_box.setFillColor(background_color);

    // Text
    text.setString("0");
    text.setFont(font);
    text.setCharacterSize(height / 2);
    text.setFillColor({0, 0, 0});
    text.setPosition(
        relative_pos.x + 10,  // Centra el texto horizontalmente
        relative_pos.y + 10 // Centra el texto verticalmente
    );
}

void TextBox::triggerFunction(Vector2i pos)
{
    if (relative_pos.x <= pos.x && pos.x <= relative_pos.x + width &&
        relative_pos.y <= pos.y && pos.y <= relative_pos.y + height)
        if (textBoxFunction)
            textBoxFunction();
}

void TextBox::draw(RenderWindow &window)
{
    window.draw(text_box);
    window.draw(text);
}
