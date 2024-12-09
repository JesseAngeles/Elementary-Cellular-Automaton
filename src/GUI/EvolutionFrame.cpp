#include "GUI/EvolutionFrame.h"

// Constructor
EvolutionFrame::EvolutionFrame(int width, int height, Vector2f relative_pos, Color background_color, ElementaryCellularAutomaton &eca)
    : Frame(width, height, relative_pos, background_color), eca(eca)
{
    y_scale = x_scale = static_cast<float>(width) / static_cast<float>(eca.getSpace().size());

    // Init axes
    initAxes();
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

// Private functions

bool EvolutionFrame::shapeInFrame(const RectangleShape &shape)
{
    Vector2f shape_position = shape.getPosition();
    if (relative_pos.x <= shape_position.x && shape_position.x <= relative_pos.x + width &&
        relative_pos.y <= shape_position.y && shape_position.y < relative_pos.y + height - y_scale)
        return true;

    return false;
}

void EvolutionFrame::insertShape(const RectangleShape &shape)
{
    shapes.push_back(shape);
    if (shapeInFrame(shape))
        drawable_shapes.push_back(std::make_shared<RectangleShape>(shape));
}

// Public functions
void EvolutionFrame::step()
{
    eca.step();
    std::vector<bool> eca_space = eca.getSpace();

    for (int i = 0; i < eca_space.size(); i++)
        if (eca_space[i])
            insertShape(drawRectangle(generation, i, color));

    if (shapes.back().getPosition().y > relative_pos.y + height)
        moveVertical(false);

    generation++;
}

void EvolutionFrame::resetSpace()
{
    generation = 0;
    shapes.clear();
    drawable_shapes.clear();
    eca.setSpace(std::vector<bool>(eca.getSpace().size(), false));

    init_pos = Vector2f(0, 0);
}

void EvolutionFrame::randomSpace()
{
    eca.initRandom();
    for (int i = 0; i < eca.getSpace().size(); i++)
        if (eca.getSpace()[i])
            insertShape(drawRectangle(generation, i, color));

    generation++;
}

void EvolutionFrame::oneSpace()
{
    insertShape(drawRectangle(generation, eca.initOne(), color));

    generation++;
}

// Drawers
void EvolutionFrame::draw(RenderWindow &window)
{
    Frame::draw(window);

    // Dibujar los ejes
    if (draw_axes)
        for (const VertexArray &axis : axes)
            window.draw(axis);

    // Dibujar las figuras dentro del frame
    for (const std::shared_ptr<RectangleShape> &shape : drawable_shapes)
        window.draw(*shape);
}

RectangleShape EvolutionFrame::drawRectangle(int y, int x, Color color)
{
    RectangleShape rectangle(Vector2f(x_scale, y_scale));
    rectangle.setPosition({x * x_scale + relative_pos.x, y * y_scale + relative_pos.y + init_pos.y});
    rectangle.setFillColor(color);

    return rectangle;
}

void EvolutionFrame::moveVertical(bool down)
{
    drawable_shapes.clear();
    float move = (down) ? y_scale : -y_scale;

    for (RectangleShape &shape : shapes)
    {
        shape.move({0, move});
        if (shapeInFrame(shape))
            drawable_shapes.push_back(std::make_shared<RectangleShape>(shape));
    }

    init_pos.y += move;
}

// Clicker function
void EvolutionFrame::clickEvent(sf::Vector2i pos)
{
    if(generation == 0)
        generation = 1;

    // Verificar si el clic está dentro del marco
    if (pos.x <= relative_pos.x || pos.x >= relative_pos.x + width ||
        pos.y <= relative_pos.y || pos.y >= relative_pos.y + height)
        return;

    // Calcular la posición en términos del espacio del autómata
    int x_pos = (pos.x - init_pos.x - relative_pos.x) / x_scale;
    int y_pos = (pos.y - init_pos.y - relative_pos.y) / y_scale;

    if (0 <= x_pos && x_pos < eca.getSpace().size())
    {
        // Dibujar el cuadrado si se da clic
        RectangleShape new_shape = drawRectangle(generation - 1, x_pos, color);
        bool found = false;

        // Buscar si la posición ya está ocupada
        for (auto it = shapes.begin(); it != shapes.end();)

            if (it->getPosition() == new_shape.getPosition())
            {
                // Eliminar el elemento de `shapes` y sus referencias en `drawable_shapes`
                auto drawable_it = std::find_if(drawable_shapes.begin(), drawable_shapes.end(),
                                                [&it](const std::shared_ptr<RectangleShape> &ptr)
                                                { return ptr->getPosition() == it->getPosition();});

                if (drawable_it != drawable_shapes.end())
                    drawable_shapes.erase(drawable_it);

                it = shapes.erase(it); // Eliminar de `shapes`
                found = true;
                break;
            }

            else
                ++it;

        // Si no se encontró, insertar la nueva forma
        if (!found)
            insertShape(new_shape);

        // Actualizar el espacio en el autómata
        eca.switchCell(x_pos);
    }

    if(generation == 1)
        generation = 0;
}
