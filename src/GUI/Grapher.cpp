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
      one_button(50, 50, Vector2f(280, 10), {0, 0, 0}, ONE_ROUTE),

      rule_text_box(100, 50, Vector2f(340, 10), Color(210, 210, 210))
{

    if (!this->font.loadFromFile(font_route))
        std::cout << "Error in Grapher.loadFont. Can´t load font from " << font_route << std::endl;

    rule_text_box.setFont(font);

    // init squares
    black.resize(12);
    white.resize(12);
    for (int i = 0; i < 12; i++)
    {
        black[i].setFillColor({0, 0, 0});
        black[i].setSize(Vector2f(20, 20));
        black[i].setOutlineThickness(2);
        black[i].setOutlineColor({0, 0, 0});

        white[i].setFillColor({255, 255, 255});
        white[i].setSize(Vector2f(20, 20));
        white[i].setOutlineThickness(2);
        white[i].setOutlineColor({0, 0, 0});
    }
    black[0].setPosition(450, 10);
    black[1].setPosition(480, 10);
    black[2].setPosition(510, 10);

    black[3].setPosition(550, 10);
    black[4].setPosition(580, 10);
    white[0].setPosition(610, 10);

    black[5].setPosition(650, 10);
    white[1].setPosition(680, 10);
    black[6].setPosition(710, 10);

    black[7].setPosition(750, 10);
    white[2].setPosition(780, 10);
    white[3].setPosition(810, 10);

    white[4].setPosition(850, 10);
    black[8].setPosition(880, 10);
    black[9].setPosition(910, 10);

    white[5].setPosition(950, 10);
    black[10].setPosition(980, 10);
    white[6].setPosition(1010, 10);

    white[7].setPosition(1050, 10);
    white[8].setPosition(1080, 10);
    black[11].setPosition(1110, 10);

    white[9].setPosition(1150, 10);
    white[10].setPosition(1180, 10);
    white[11].setPosition(1210, 10);

    for (int i = 0; i < 8; i++)
        squares.push_back(Button(20, 20, Vector2f(480 + i * 100, 40), Color::White, " "));

    // Function assignation
    rule_text_box.setTextBoxFunction([this]()
                                     { setRuleFunction(); });

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

    squares[0].setButtonFunction([this]()
                                 { switchRule1(); });
    squares[1].setButtonFunction([this]()
                                 { switchRule2(); });
    squares[2].setButtonFunction([this]()
                                 { switchRule3(); });
    squares[3].setButtonFunction([this]()
                                 { switchRule4(); });
    squares[4].setButtonFunction([this]()
                                 { switchRule5(); });
    squares[5].setButtonFunction([this]()
                                 { switchRule6(); });
    squares[6].setButtonFunction([this]()
                                 { switchRule7(); });
    squares[7].setButtonFunction([this]()
                                 { switchRule8(); });
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

                rule_text_box.triggerFunction(mouse_pos);

                for (Button &square : squares)
                    square.triggerFunction(mouse_pos);
            }

            if (is_rule_text_box_selected && event.type == sf::Event::KeyPressed)
            {
                if (event.key.code >= 26 && event.key.code <= 36)
                    rule_text_box.getText().setString(rule_text_box.getText().getString() + std::to_string((event.key.code - 26) % 10));

                // backspace
                if (event.key.code == 59)
                {
                    std::string new_string = rule_text_box.getText().getString().toAnsiString();
                    if (new_string.size())
                        new_string.pop_back();
                    rule_text_box.getText().setString(new_string);
                }

                // Enter
                if (event.key.code == 58)
                {
                    int rule = std::stoi(rule_text_box.getText().getString().toAnsiString());
                    if (rule > 255)
                        rule = 255;

                    rule_text_box.getText().setString(std::to_string(rule));
                    is_rule_text_box_selected = false;
                }
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

        // TextBox
        rule_text_box.draw(window);

        // Buttons
        start_button.draw(window);
        increase_speed_button.draw(window);
        decrease_speed_button.draw(window);
        reset_button.draw(window);
        step_button.draw(window);
        random_button.draw(window);
        one_button.draw(window);

        // Squares
        for (int i = 0; i < 12; i++)
        {
            window.draw(white[i]);
            window.draw(black[i]);
        }

        for (int i = 0; i < 8; i++)
            squares[i].draw(window);

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

void Grapher::setRuleFunction()
{
    is_rule_text_box_selected = true;
}

void Grapher::switchRule1()
{
    if (squares[0].getColor() == Color::White)
        squares[0].setColor(Color::Black);
    else
        squares[0].setColor(Color::White);
}

void Grapher::switchRule2()
{
    if (squares[1].getColor() == Color::White)
        squares[1].setColor(Color::Black);
    else
        squares[1].setColor(Color::White);
}
void Grapher::switchRule3()
{
    if (squares[2].getColor() == Color::White)
        squares[2].setColor(Color::Black);
    else
        squares[2].setColor(Color::White);
}
void Grapher::switchRule4()
{
    if (squares[3].getColor() == Color::White)
        squares[3].setColor(Color::Black);
    else
        squares[3].setColor(Color::White);
}
void Grapher::switchRule5()
{
    if (squares[4].getColor() == Color::White)
        squares[4].setColor(Color::Black);
    else
        squares[4].setColor(Color::White);
}
void Grapher::switchRule6()
{
    if (squares[5].getColor() == Color::White)
        squares[5].setColor(Color::Black);
    else
        squares[5].setColor(Color::White);
}
void Grapher::switchRule7()
{
    if (squares[6].getColor() == Color::White)
        squares[6].setColor(Color::Black);
    else
        squares[6].setColor(Color::White);
}
void Grapher::switchRule8()
{
    if (squares[7].getColor() == Color::White)
        squares[7].setColor(Color::Black);
    else
        squares[7].setColor(Color::White);
}