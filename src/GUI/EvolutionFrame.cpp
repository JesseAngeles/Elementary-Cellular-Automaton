#include "GUI/EvolutionFrame.h"

// Constructor
EvolutionFrame::EvolutionFrame(int width, int height, Vector2f relative_pos, Color background_color, ElementaryCellularAutomaton &eca)
    : Frame(width, height, relative_pos, background_color), eca(eca), init_pos(0, 0)
{
    y_scale = x_scale = static_cast<float>(width) / static_cast<float>(eca.getSpace().size());

    // Init axes
    initAxes();

    // Init squares
    std::vector<std::pair<RectangleShape, bool>> first_line;
    for (int i = 0; i < eca.getSpace().size(); i++)
        first_line.push_back(std::make_pair(drawRectangle(0, i, Color{255, 255, 255}), false));
    evolution.push_back(first_line);
}

void EvolutionFrame::initAxes()
{
    for (int x = relative_pos.x; x <= (relative_pos.x + width); x += x_scale)
    {
        VertexArray line(Lines, 2);
        line[0].position = Vector2f(x, relative_pos.y);
        line[1].position = Vector2f(x, relative_pos.y + height);
        line[0].color = line[1].color = Color::Black;

        axes.push_back(line);
    }

    for (int y = relative_pos.y; y <= (relative_pos.y + height); y += y_scale)
    {
        VertexArray line(Lines, 2);
        line[0].position = Vector2f(relative_pos.x, y);
        line[1].position = Vector2f(relative_pos.x + width, y);
        line[0].color = line[1].color = Color::Black;

        axes.push_back(line);
    }
}

// Drawers
void EvolutionFrame::draw(RenderWindow &window)
{
    Frame::draw(window);

    // Dibujar los ejes
    if (draw_axes)
        for (const VertexArray &axis : axes)
            window.draw(axis);

    // Dibujar las figuras
    for (const RectangleShape &shape : shapes)
        window.draw(shape);
}

RectangleShape EvolutionFrame::drawRectangle(int y, int x, Color color)
{
    RectangleShape rectangle(Vector2f(x_scale, y_scale));
    rectangle.setPosition({x * x_scale + relative_pos.x, y * y_scale + relative_pos.y});
    rectangle.setFillColor(color);

    return rectangle;
}

void EvolutionFrame::insertLine(std::vector<bool> new_line)
{
    std::vector<std::pair<RectangleShape, bool>> line;
    for (int i = 0; i < new_line.size(); i++)
    {
        if (new_line[i])
        {
            shapes.push_back(drawRectangle(generation, i, Color(0, 0, 0)));
            line.push_back(std::make_pair(drawRectangle(generation, i, {0, 0, 0}), new_line[i]));
        }
        else
            line.push_back(std::make_pair(drawRectangle(generation, i, {255, 255, 255}), new_line[i]));
    }
    evolution.push_back(line);

    generation++;
}

void EvolutionFrame::moveVertical(bool down)
{
    float move = (down) ? y_scale : -y_scale;
    for (std::vector<std::pair<RectangleShape, bool>> &line : evolution)
        for (std::pair<RectangleShape, bool> &cell : line)
            cell.first.move({0, move});

    init_pos.y += move;
}

// Clicker function
void EvolutionFrame::clickEvent(Vector2i pos)
{
    if (pos.x <= relative_pos.x || pos.x >= relative_pos.x + width ||
        pos.y <= relative_pos.y || pos.y >= relative_pos.y + height)
        return;

    int x_pos = (pos.x - init_pos.x - relative_pos.x) / x_scale;
    int y_pos = (pos.y - init_pos.y - relative_pos.y) / y_scale;

    if (0 <= x_pos && x_pos <= eca.getSpace().size() - 1)
    {
        // Dibujar el cuadrado si se da click
        RectangleShape new_shape = drawRectangle(0, x_pos, Color(0, 0, 0));
        bool found = false;
        for (std::vector<RectangleShape>::iterator it = shapes.begin(); it != shapes.end();)
            if (it->getPosition() == new_shape.getPosition())
            {
                it = shapes.erase(it);
                found = true;
                break;
            }
            else
                ++it;

        if (!found)
            shapes.push_back(drawRectangle(0, x_pos, Color(0, 0, 0)));
    
        // Actualizar el espacio
        eca.switchCell(x_pos);
    }
}

std::vector<bool> EvolutionFrame::getEvolutionValues()
{
    std::vector<bool> init_space(evolution[generation - 1].size(), false);
    for (int i = 0; i < evolution[generation - 1].size(); i++)
        init_space[i] = evolution[generation - 1][i].second;

    return init_space;
}
