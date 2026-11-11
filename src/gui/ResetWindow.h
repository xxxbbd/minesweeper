#ifndef MINESWEEPER_RESETWINDOW_H
#define MINESWEEPER_RESETWINDOW_H

#include "SFML/Graphics/Text.hpp"

namespace sf {
    class RenderWindow;
}

class ResetWindow {
public:
    explicit ResetWindow(sf::RenderWindow*);
    void draw();
    bool inYesButton(int x, int y) const;
    bool inNoButton(int x, int y) const;

private:
    void drawWindow();
    void drawText();

    sf::RenderWindow* window_{};
    sf::Text noText_;
    sf::Text yesText_;
};

#endif //MINESWEEPER_RESETWINDOW_H