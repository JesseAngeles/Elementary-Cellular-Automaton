#ifndef GRAPHER_H
#define GRAPHER_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Button.h"

#define FONT_ROUTE "./resources/fonts/Roboto-Medium.ttf"

#define START_ROUTE "./resources/images/start.png"
#define INCREASE_ROUTE "./resources/images/increase.png"
#define DECREASE_ROUTE "./resources/images/decrease.png"
#define PAUSE_ROUTE "./resources/images/pause.png"
#define STEP_ROUTE "./resources/images/step.png"
#define RESET_ROUTE "./resources/images/reset.png"
#define RANDOM_ROUTE "./resources/images/random.png"
#define ONE_ROUTE "./resources/images/one.png"

using namespace sf;

class Grapher
{
private:
    // Window
    int width;
    int height;
    std::string tittle;
    Color backgroundColor;
    Font font;
    std::string font_route = FONT_ROUTE;

    bool is_running = false;
    float delta_time = 0.0;
    float speed = 500;

    std::vector<int> population;

    // Frames

    // Classes
    
    // Lines
    std::vector<VertexArray> axes;
    std::vector<VertexArray> lines;

    // Text

    // Buttons
    Button start_button;
    Button increase_speed_button;
    Button decrease_speed_button;
    Button step_button;
    Button reset_button;
    Button random_button;
    Button one_button;

    // Functions
    void startFunction();
    void increaseSpeedFunction();
    void decreaseSpeedFunction();
    void stepFunction();
    void resetFunction();
    void randomFunction();
    void oneFunction();

    // Rectangles (alive cells)
    std::vector<std::pair<RectangleShape, Vector2i>> rectangles;

    // Functions
    void loadFont();

public:
    // Constructor
    Grapher(int width, int height, std::string tittle, Color background);
    void drawAxis();

    RenderWindow window;

    // Functions
    void mainLoop();

    // Drawers
    void drawLine(Vector2f pos_1, Vector2f pos_2, Color color);
    void drawRectangle(Vector2i position, Color color);

    // Getters

    // Settters
};

#endif // GRAPHER_H