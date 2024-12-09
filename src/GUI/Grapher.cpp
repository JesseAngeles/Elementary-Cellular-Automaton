#include "GUI/Grapher.h"

// Constructor
Grapher::Grapher(int width, int height, std::string tittle, Color backgroundColor, ElementaryCellularAutomaton &eca)
    : width(width), height(height), tittle(tittle), backgroundColor(backgroundColor), eca(eca),
      window(VideoMode(width, height), tittle, Style::Close),
      evolution(1900, 920, Vector2f(10, 70), Color(240, 240, 240), eca),

      start_button(50, 50, Vector2f(10, 10), Color(0, 0, 0), START_ROUTE),
      increase_speed_button(20, 20, Vector2f(70, 10), {0, 0, 0}, INCREASE_ROUTE),
      decrease_speed_button(20, 20, Vector2f(70, 40), {0, 0, 0}, DECREASE_ROUTE),
      step_button(50, 50, Vector2f(100, 10), Color(0, 0, 0), STEP_ROUTE),
      reset_button(50, 50, Vector2f(160, 10), Color(0, 0, 0), RESET_ROUTE),
      random_button(50, 50, Vector2f(220, 10), Color(0, 0, 0), RANDOM_ROUTE),
      one_button(50, 50, Vector2f(280, 10), {0, 0, 0}, ONE_ROUTE),
      axes_button(50, 50, Vector2f(340, 10), Color(0, 0, 0), AXES_ON),
      rule_text_box(100, 50, Vector2f(400, 10), Color(210, 210, 210))
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
    black[0].setPosition(510, 10);
    black[1].setPosition(540, 10);
    black[2].setPosition(570, 10);

    black[3].setPosition(610, 10);
    black[4].setPosition(640, 10);
    white[0].setPosition(670, 10);

    black[5].setPosition(710, 10);
    white[1].setPosition(740, 10);
    black[6].setPosition(770, 10);

    black[7].setPosition(810, 10);
    white[2].setPosition(840, 10);
    white[3].setPosition(870, 10);

    white[4].setPosition(910, 10);
    black[8].setPosition(940, 10);
    black[9].setPosition(970, 10);

    white[5].setPosition(1010, 10);
    black[10].setPosition(1040, 10);
    white[6].setPosition(1070, 10);

    white[7].setPosition(1110, 10);
    white[8].setPosition(1140, 10);
    black[11].setPosition(1170, 10);

    white[9].setPosition(1210, 10);
    white[10].setPosition(1240, 10);
    white[11].setPosition(1270, 10);

    for (int i = 0; i < 8; i++)
        squares.push_back(Button(20, 20, Vector2f(540 + i * 100, 40), Color::White, " "));

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
    axes_button.setButtonFunction([this]()
                                  { drawAxesFunction(); });

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

    // Init generation count
    generation_count.setString("Generation: 0");
    generation_count.setPosition(Vector2f(1310, 10));
    generation_count.setFont(font);
    generation_count.setFillColor(Color::Black);
    generation_count.setCharacterSize(20);


    oneFunction();

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

                // Click event
                evolution.clickEvent(mouse_pos);

                start_button.triggerFunction(mouse_pos);
                increase_speed_button.triggerFunction(mouse_pos);
                decrease_speed_button.triggerFunction(mouse_pos);
                step_button.triggerFunction(mouse_pos);
                reset_button.triggerFunction(mouse_pos);
                random_button.triggerFunction(mouse_pos);
                one_button.triggerFunction(mouse_pos);
                axes_button.triggerFunction(mouse_pos);

                rule_text_box.triggerFunction(mouse_pos);

                for (Button &square : squares)
                    square.triggerFunction(mouse_pos);
            }

            if (is_rule_text_box_selected && event.type == sf::Event::KeyPressed)
            {
                std::string rule_string = rule_text_box.getText().getString().toAnsiString();
                if (event.key.code >= 26 && event.key.code <= 36 && rule_string.size() < 3)
                    rule_text_box.getText().setString(rule_string + std::to_string((event.key.code - 26) % 10));

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
                    std::string rule_string = rule_text_box.getText().getString().toAnsiString();
                    if (rule_string.empty())
                        rule_string += '0';
                    int rule = std::stoi(rule_string);
                    if (rule > 255)
                        rule = 255;

                    rule_text_box.getText().setString(std::to_string(rule));
                    is_rule_text_box_selected = false;

                    eca.setRule(getBinary(rule, 8));
                    std::vector<bool> eca_rule = eca.getRule();
                    for (int i = 0; i < 8; i++)
                        if (eca_rule[i])
                            squares[i].setColor(Color::Black);
                        else
                            squares[i].setColor(Color::White);
                }
            }

            if (event.type == Event::MouseWheelScrolled && !is_running)
                if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
                    if (event.mouseWheelScroll.delta > 0)
                        evolution.moveVertical(true);
                    else if (event.mouseWheelScroll.delta < 0)
                        evolution.moveVertical(false);
        }

        delta_time += clock.restart().asMilliseconds();
        if (is_running && delta_time >= speed)
        {
            stepFunction();
            delta_time = 0;
        }

        window.clear(backgroundColor);

        // Dibujar elementos estaticos
        if (!axes.empty())
            for (const VertexArray &axis : axes)
                window.draw(axis);

        if (!lines.empty())
            for (const VertexArray &line : lines)
                window.draw(line);

        // Frames
        evolution.draw(window);

        // TextBox
        rule_text_box.draw(window);

        // Texts
        window.draw(generation_count);

        // Buttons
        start_button.draw(window);
        increase_speed_button.draw(window);
        decrease_speed_button.draw(window);
        reset_button.draw(window);
        step_button.draw(window);
        random_button.draw(window);
        one_button.draw(window);
        axes_button.draw(window);

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

// Button functions
void Grapher::startFunction()
{
    is_running = !is_running;
    start_button.setTexture((is_running) ? PAUSE_ROUTE : START_ROUTE);
}

void Grapher::increaseSpeedFunction()
{
    speed -= 250;
}

void Grapher::decreaseSpeedFunction()
{
    speed += 250;
}

void Grapher::stepFunction()
{
    evolution.step();
    generation_count.setString("Generation: " + std::to_string(evolution.getGenerationCount()));
}

void Grapher::resetFunction()
{
    is_running = false;
    start_button.setTexture(START_ROUTE);
    evolution.resetSpace();

    generation_count.setString("Generation: 1");
}

void Grapher::randomFunction()
{
    evolution.randomSpace();
}

void Grapher::oneFunction()
{
    evolution.oneSpace();
}

void Grapher::setRuleFunction()
{
    is_rule_text_box_selected = true;
}

void Grapher::drawAxesFunction()
{
    bool draw_axes = !evolution.getDrawAxis();
    evolution.setDrawAxis(draw_axes);

    axes_button.setTexture((draw_axes) ? AXES_ON : AXES_OFF);
}

void Grapher::switchRule1()
{
    std::string rule_string = rule_text_box.getText().getString().toAnsiString();
    int rule = std::stoi(rule_string);

    std::vector<bool> rule_eca = eca.getRule();
    rule_eca[0] = !rule_eca[0];
    eca.setRule(rule_eca);

    if (squares[0].getColor() == Color::White)
    {
        squares[0].setColor(Color::Black);
        rule_text_box.setText(std::to_string(rule + 128));
    }
    else
    {
        squares[0].setColor(Color::White);
        rule_text_box.setText(std::to_string(rule - 128));
    }
}
void Grapher::switchRule2()
{
    std::string rule_string = rule_text_box.getText().getString().toAnsiString();
    int rule = std::stoi(rule_string);

    std::vector<bool> rule_eca = eca.getRule();
    rule_eca[1] = !rule_eca[1];
    eca.setRule(rule_eca);

    if (squares[1].getColor() == Color::White)
    {
        squares[1].setColor(Color::Black);
        rule_text_box.setText(std::to_string(rule + 64));
    }
    else
    {
        squares[1].setColor(Color::White);
        rule_text_box.setText(std::to_string(rule - 64));
    }
}
void Grapher::switchRule3()
{
    std::string rule_string = rule_text_box.getText().getString().toAnsiString();
    int rule = std::stoi(rule_string);

    std::vector<bool> rule_eca = eca.getRule();
    rule_eca[2] = !rule_eca[2];
    eca.setRule(rule_eca);

    if (squares[2].getColor() == Color::White)
    {
        squares[2].setColor(Color::Black);
        rule_text_box.setText(std::to_string(rule + 32));
    }
    else
    {
        squares[2].setColor(Color::White);
        rule_text_box.setText(std::to_string(rule - 32));
    }
}
void Grapher::switchRule4()
{
    std::string rule_string = rule_text_box.getText().getString().toAnsiString();
    int rule = std::stoi(rule_string);

    std::vector<bool> rule_eca = eca.getRule();
    rule_eca[3] = !rule_eca[3];
    eca.setRule(rule_eca);

    if (squares[3].getColor() == Color::White)
    {
        squares[3].setColor(Color::Black);
        rule_text_box.setText(std::to_string(rule + 16));
    }
    else
    {
        squares[3].setColor(Color::White);
        rule_text_box.setText(std::to_string(rule - 16));
    }
}
void Grapher::switchRule5()
{
    std::string rule_string = rule_text_box.getText().getString().toAnsiString();
    int rule = std::stoi(rule_string);

    std::vector<bool> rule_eca = eca.getRule();
    rule_eca[4] = !rule_eca[4];
    eca.setRule(rule_eca);

    if (squares[4].getColor() == Color::White)
    {
        squares[4].setColor(Color::Black);
        rule_text_box.setText(std::to_string(rule + 8));
    }
    else
    {
        squares[4].setColor(Color::White);
        rule_text_box.setText(std::to_string(rule - 8));
    }
}
void Grapher::switchRule6()
{
    std::string rule_string = rule_text_box.getText().getString().toAnsiString();
    int rule = std::stoi(rule_string);

    std::vector<bool> rule_eca = eca.getRule();
    rule_eca[5] = !rule_eca[5];
    eca.setRule(rule_eca);

    if (squares[5].getColor() == Color::White)
    {
        squares[5].setColor(Color::Black);
        rule_text_box.setText(std::to_string(rule + 4));
    }
    else
    {
        squares[5].setColor(Color::White);
        rule_text_box.setText(std::to_string(rule - 4));
    }
}
void Grapher::switchRule7()
{
    std::string rule_string = rule_text_box.getText().getString().toAnsiString();
    int rule = std::stoi(rule_string);

    std::vector<bool> rule_eca = eca.getRule();
    rule_eca[6] = !rule_eca[6];
    eca.setRule(rule_eca);

    if (squares[6].getColor() == Color::White)
    {
        squares[6].setColor(Color::Black);
        rule_text_box.setText(std::to_string(rule + 2));
    }
    else
    {
        squares[6].setColor(Color::White);
        rule_text_box.setText(std::to_string(rule - 2));
    }
}
void Grapher::switchRule8()
{
    std::string rule_string = rule_text_box.getText().getString().toAnsiString();
    int rule = std::stoi(rule_string);

    std::vector<bool> rule_eca = eca.getRule();
    rule_eca[7] = !rule_eca[7];
    eca.setRule(rule_eca);

    if (squares[7].getColor() == Color::White)
    {
        squares[7].setColor(Color::Black);
        rule_text_box.setText(std::to_string(rule + 1));
    }
    else
    {
        squares[7].setColor(Color::White);
        rule_text_box.setText(std::to_string(rule - 1));
    }
}