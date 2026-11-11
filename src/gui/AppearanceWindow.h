#ifndef MINESWEEPER_APPEARANCEWINDOW_H
#define MINESWEEPER_APPEARANCEWINDOW_H

#include <SFML/Graphics.hpp>

class AppearanceWindow {
public:
    AppearanceWindow();
    void run();
private:
    void eventHandler();
    void render();

    sf::RenderWindow window_{};
    // bool gOpen { false }; to do
};

#endif //MINESWEEPER_APPEARANCEWINDOW_H
