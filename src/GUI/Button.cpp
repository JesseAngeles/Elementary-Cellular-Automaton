#include "GUI/Button.h"

Button::Button(int width, int height, Vector2f relative_pos, Color background_color, std::string content)
    : width(width), height(height), relative_pos(relative_pos), background_color(background_color)
{
    // Draw background
    button = RectangleShape(Vector2f(width, height));
    button.setPosition(relative_pos);
    button.setOutlineThickness(2);
    button.setOutlineColor(background_color);
    button.setFillColor(background_color);

    if (texture.loadFromFile(content))
    {
        // Asignar la textura al RectangleShape
        button.setTexture(&texture);

        // Obtener el tamaño de la textura cargada
        Vector2u textureSize = texture.getSize();

        // Ajustar la textura al tamaño del RectangleShape
        button.setTextureRect(IntRect(0, 0, textureSize.x, textureSize.y));
    }
    else
    {
        // Configuración del texto si no se cargó la textura
        if (font.loadFromFile(font_route)) // Asegura que la fuente cargue correctamente
        {
            text.setString(content);
            text.setFont(font);
            text.setCharacterSize(24);
            text.setFillColor({200, 200, 200});
            text.setPosition(
                relative_pos.x + (width - text.getLocalBounds().width) / 2,  // Centra el texto horizontalmente
                relative_pos.y + (height - text.getLocalBounds().height) / 2 // Centra el texto verticalmente
            );
        }
    }
}

#include <iostream>
void Button::triggerFunction(Vector2i pos)
{
    if (relative_pos.x <= pos.x && pos.x <= relative_pos.x + width &&
        relative_pos.y <= pos.y && pos.y <= relative_pos.y + height)
        if (buttonFunction)
            buttonFunction();
}

void Button::draw(RenderWindow &window)
{
    window.draw(button);
    if (!button.getTexture())
        window.draw(text);
}

void Button::setTexture(std::string content)
{
    if (texture.loadFromFile(content))
    {
        // Asignar la textura al RectangleShape
        button.setTexture(&texture);

        // Obtener el tamaño de la textura cargada
        Vector2u textureSize = texture.getSize();

        // Ajustar la textura al tamaño del RectangleShape
        button.setTextureRect(IntRect(0, 0, textureSize.x, textureSize.y));
    }
}