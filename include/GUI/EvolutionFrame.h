#ifndef EVOLUTION_FRAME_H
#define EVOLUTION_FRAME_H

#include "GUI/Frame.h"
#include "ECA/ElementaryCellularAutomaton.hpp"

class EvolutionFrame : public Frame
{
private:
    // Frame
    float x_scale;
    float y_scale;

    Vector2f init_pos;

    // Elements
    int generation = 1;
    std::vector<RectangleShape> shapes;

    std::vector<std::vector<std::pair<RectangleShape, bool>>> evolution;

    // Classes
    ElementaryCellularAutomaton &eca;

    // Axes
    bool draw_axes = true;
    std::vector<VertexArray> axes;

public:
    // Constructor
    EvolutionFrame(int width, int height, Vector2f position, Color background_color, ElementaryCellularAutomaton &eca);

    void initAxes();

    // Functions
    void insertLine(std::vector<bool> new_line);

    // Drawers
    void draw(RenderWindow &window);
    RectangleShape drawRectangle(int y, int x, Color color);
    void changeColor(int y, int x);

    // Redraws
    void zoom(bool in);
    void moveHorizontal(bool right);
    void moveVertical(bool down);

    // Clicker functions
    void clickEvent(Vector2i position);

    // Getters
    Vector2f getInitPos() const { return init_pos; }
    std::vector<bool> getEvolutionValues();
    int getGenerationCount() const { return generation; }
    bool getDrawAxis() const { return draw_axes; }

    // Setters
    void setInitPos(Vector2f init_pos);
    void setDrawAxis(bool draw_axes) { this->draw_axes = draw_axes; }
};

#endif // EVOLUTION_FRAME_H