#ifndef MINESWEEPER_RESETBUTTON_H
#define MINESWEEPER_RESETBUTTON_H

#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Texture.hpp"

namespace sf {
    class RenderWindow;
}

class ResetButton {
public:
    explicit ResetButton(sf::RenderWindow*);
    void draw();
    bool in(int x, int y);

private:
    sf::RenderWindow* window_{};
    sf::CircleShape button_{};
    sf::Texture resetTexture_{};
};

#endif //MINESWEEPER_RESETBUTTON_H