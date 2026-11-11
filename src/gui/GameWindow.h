#ifndef MINESWEEPER_GAMEWINDOW_H
#define MINESWEEPER_GAMEWINDOW_H

#include "../game/Field.h"
#include "../game/Difficulty.h"
#include "ResetWindow.h"
#include <SFML/Graphics.hpp>

namespace sf {
    class RenderWindow;
}

class GameWindow {
public:
    explicit GameWindow(sf::RenderWindow*);
    void run();

private:
    void eventHandler();
    void drawField();
    void drawTimer();
    void drawResetButton();
    void render();

    Difficulty difficulty_{ Difficulties::Beginner };
    Field field_{ 0, 0, 0 };
    sf::RenderWindow* window_{};
    sf::Clock clock_{};
    ResetWindow rWindow_;
    sf::Texture cellTexture_{};
    sf::Texture resetTexture_{};
    int seconds_{ 0 };
    bool resetWindowOpen_{ false };
};

#endif //MINESWEEPER_GAMEWINDOW_H