#ifndef EVOLUTION_FRAME_H
#define EVOLUTION_FRAME_H

#include "GUI/Frame.h"
#include "ECA/ElementaryCellularAutomaton.hpp"

#include "memory"

class EvolutionFrame : public Frame
{
private:
    // Frame
    float x_scale;
    float y_scale;

    Vector2f init_pos = Vector2f(0, 0);

    // Elements
    int generation = 0;
    std::vector<RectangleShape> shapes;
    std::vector<std::shared_ptr<RectangleShape>> drawable_shapes;
    Color color = Color(0, 0, 0);

    // Classes
    ElementaryCellularAutomaton &eca;

    // Axes
    bool draw_axes = true;
    std::vector<VertexArray> axes;

    // Functions
    bool shapeInFrame(const RectangleShape &shape);
    void insertShape(const RectangleShape &shape);

public:
    // Constructor
    EvolutionFrame(int width, int height, Vector2f position, Color background_color, ElementaryCellularAutomaton &eca);

    void initAxes();

    // Functions
    void step();
    void resetSpace();
    void randomSpace();
    void oneSpace();

    // Drawers
    void draw(RenderWindow &window);
    RectangleShape drawRectangle(int y, int x, Color color);

    void moveVertical(bool down);
    void zoom(bool in);
    void moveHorizontal(bool right);

    // Clicker functions
    void clickEvent(Vector2i position);

    // Getters
    Vector2f getInitPos() const { return init_pos; }
    int getGenerationCount() const { return generation; }
    bool getDrawAxis() const { return draw_axes; }

    // Setters
    void setInitPos(Vector2f init_pos);
    void setDrawAxis(bool draw_axes) { this->draw_axes = draw_axes; }
    void setColor(Color color) { this->color = color; }
};

#endif // EVOLUTION_FRAME_H