#include "ResetButton.h"
#include <SFML/Graphics/RenderWindow.hpp>

ResetButton::ResetButton(sf::RenderWindow* window)
    : window_(window), button_{ 16.f } {
    if (!resetTexture_.loadFromFile("assets/textures/Reset.png")) {
        // to do
    }
    resetTexture_.setSmooth(true);
}

bool ResetButton::in(int x, int y) {
    float xX{ button_.getPosition().x };
    float yY{ button_.getPosition().y };
    float width{ button_.getLocalBounds().size.x };
    float height{ button_.getLocalBounds().size.y };
    return xX <= x && x <= xX + width && yY <= y && y <= yY + height;
}

void ResetButton::draw() {
    button_.setTexture(&resetTexture_);
    float x{ static_cast<float>(window_->getSize().x) / 2 - button_.getLocalBounds().size.x / 2};
    float y{ 0.f };
    button_.setPosition({ x, y });
    window_->draw(button_);
}