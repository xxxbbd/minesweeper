#ifndef MINESWEEPER_SETTINGSWINDOW_H
#define MINESWEEPER_SETTINGSWINDOW_H

namespace sf {
    class RenderWindow;
}

class SettingsWindow {
public:
    SettingsWindow(sf::RenderWindow*);
    void run();

private:
    void eventHandler();
    void drawBackButton();
    void render();

    sf::RenderWindow* window_{};
    bool active_{ false };
};


#endif //MINESWEEPER_SETTINGSWINDOW_H
