#ifndef MINESWEEPER_APPEARANCEWINDOW_H
#define MINESWEEPER_APPEARANCEWINDOW_H

#include <SFML/Graphics.hpp>

class SettingsButton {
public:
    bool inSettingsButton(int x, int y);
    void setPosition(sf::Vector2f);
    void draw(sf::RenderWindow* window);

private:
    float x_{};
    float y_{};
    int width_{ 30 };
    int height_{ 30 };
};

class AppearanceWindow {
public:
    AppearanceWindow();
    void run();

private:
    void eventHandler();
    void render();

    sf::RenderWindow window_{};
    SettingsButton sButton_{};
    // bool gOpen { false }; to do
};

#endif //MINESWEEPER_APPEARANCEWINDOW_H
