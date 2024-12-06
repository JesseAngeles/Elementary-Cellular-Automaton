#include "GUI/Frame.h"

Frame::Frame(int width, int height, Vector2f relative_pos, Color background_color)
    : width(width), height(height), relative_pos(relative_pos), background_color(background_color)
{
    // Draw background
    frame = RectangleShape(Vector2f(width, height));
    frame.setPosition(relative_pos);
    frame.setOutlineThickness(0);
    frame.setFillColor(background_color);
}

void Frame::draw(RenderWindow &window)
{
    window.draw(frame);
}