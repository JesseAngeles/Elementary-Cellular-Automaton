#include "GUI/Grapher.h"

// Constructor
Grapher::Grapher(int width, int height, std::string tittle, Color backgroundColor)
    : width(width), height(height), tittle(tittle), backgroundColor(backgroundColor),
      window(VideoMode(width, height), tittle, Style::Close),

      start_button(50, 50, Vector2f(10, 10), Color(0, 0, 0), START_ROUTE),
      increase_speed_button(20, 20, Vector2f(70, 10), {0, 0, 0}, INCREASE_ROUTE),
      decrease_speed_button(20, 20, Vector2f(70, 40), {0, 0, 0}, DECREASE_ROUTE),
      step_button(50, 50, Vector2f(100, 10), Color(0, 0, 0), STEP_ROUTE),
      reset_button(50, 50, Vector2f(160, 10), Color(0, 0, 0), RESET_ROUTE),
      random_button(50, 50, Vector2f(220, 10), Color(0, 0, 0), RANDOM_ROUTE),
      one_button(50, 50, Vector2f(280, 10), {0, 0, 0}, ONE_ROUTE)
{

    if (!this->font.loadFromFile(font_route))
        std::cout << "Error in Grapher.loadFont. Can´t load font from " << font_route << std::endl;

    // Function assignation
    start_button.setButtonFunction([this]()
                                   { startFunction(); });
    increase_speed_button.setButtonFunction([this]()
                                            { increaseSpeedFunction(); });
    decrease_speed_button.setButtonFunction([this]()
                                            { decreaseSpeedFunction(); });
    step_button.setButtonFunction([this]()
                                  { stepFunction(); });
    reset_button.setButtonFunction([this]()
                                   { resetFunction(); });
    random_button.setButtonFunction([this]()
                                    { randomFunction(); });
    one_button.setButtonFunction([this]()
                                 { oneFunction(); });
}

// Main Loop
void Grapher::mainLoop()
{
    Clock clock;

    // Board

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            // Manejar el clic del botón
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i mouse_pos(event.mouseButton.x, event.mouseButton.y);

                start_button.triggerFunction(mouse_pos);
                increase_speed_button.triggerFunction(mouse_pos);
                decrease_speed_button.triggerFunction(mouse_pos);
                step_button.triggerFunction(mouse_pos);
                reset_button.triggerFunction(mouse_pos);
                random_button.triggerFunction(mouse_pos);
                one_button.triggerFunction(mouse_pos);
            }
        }

        delta_time += clock.restart().asMilliseconds();

        window.clear(backgroundColor);

        // Dibujar elementos estaticos
        if (!axes.empty())
            for (const VertexArray &axis : axes)
                window.draw(axis);

        if (!lines.empty())
            for (const VertexArray &line : lines)
                window.draw(line);

        // Frames

        // Text

        // Buttons
        start_button.draw(window);
        increase_speed_button.draw(window);
        decrease_speed_button.draw(window);
        reset_button.draw(window);
        step_button.draw(window);
        random_button.draw(window);
        one_button.draw(window);

        window.display();
    }
}

// Drawers
void Grapher::drawLine(Vector2f pos_1, Vector2f pos_2, Color color)
{
    VertexArray line(Lines, 2);
    line[0].position = pos_1;
    line[1].position = pos_2;

    line[0].color = line[1].color = color;

    this->lines.push_back(line);
}

// Button functions
void Grapher::startFunction()
{
    // is_running = !is_running;
    // start_button.setTexture((is_running) ? PAUSE_ROUTE : START_ROUTE);
}

void Grapher::increaseSpeedFunction()
{
    speed /= 1.5;
}

void Grapher::decreaseSpeedFunction()
{
    speed *= 1.5;
}

void Grapher::stepFunction()
{
}

void Grapher::resetFunction()
{
    is_running = false;
    start_button.setTexture(START_ROUTE);
}

void Grapher::randomFunction()
{
}

void Grapher::oneFunction()
{
    std::cout << "sasas";
}
