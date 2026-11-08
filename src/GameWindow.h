#ifndef MINESWEEPER_GAMEWINDOW_H
#define MINESWEEPER_GAMEWINDOW_H

#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Difficulty.h"

class GameWindow {
public:
    GameWindow(sf::RenderWindow* window);
    void run();

private:
    void eventHandler();
    void drawField() const;
    void drawTimer();
    void render();

    Difficulty difficulty_{ Difficulties::Beginner };
    Field field_{ 0, 0, 0 };
    sf::RenderWindow* window_{};
    sf::Clock clock_{};
    int seconds_{ 0 };
};

#endif //MINESWEEPER_GAMEWINDOW_H