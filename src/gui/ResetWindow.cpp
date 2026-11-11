#include "ResetWindow.h"
#include <SFML/Graphics.hpp>

using namespace sf;

static const Font font{ "assets/fonts/Monaco.ttf" };

ResetWindow::ResetWindow(RenderWindow* window)
    : window_{ window }, yesText_{ font }, noText_{ font } {}

void ResetWindow::drawWindow() {
    RectangleShape resetWindow(Vector2f(200.f, 200.f));
    resetWindow.setFillColor(Color::White);
    resetWindow.setOutlineColor(Color::Black);
    resetWindow.setOutlineThickness(2.f);

    FloatRect windowBounds{ resetWindow.getLocalBounds() };
    float windowWidth { windowBounds.size.x };
    float windowHeight { windowBounds.size.y };
    Vector2u windowSize { window_->getSize() };
    float x{ static_cast<float>(windowSize.x) / 2 };
    float y{ static_cast<float>(windowSize.y) / 2 };
    resetWindow.setPosition({ x - windowWidth / 2, y - windowHeight / 2 });
    window_->draw(resetWindow);
}

void ResetWindow::drawText() {
    // Текст в окне подтверждения начала новой игры
    Text resetText(font);
    resetText.setCharacterSize(8);
    resetText.setFillColor(Color::Black);
    resetText.setStyle(Text::Bold);
    resetText.setString(L"Вы хотите прекратить текущую игру?");

    // to do
    Vector2u windowSize { window_->getSize() };
    float x{ static_cast<float>(windowSize.x) / 2 };
    float y{ static_cast<float>(windowSize.y) / 2 };
    FloatRect textBounds{ resetText.getLocalBounds() };
    float textWidth { textBounds.size.x };
    float textHeight { textBounds.size.y };
    resetText.setPosition({ x - textWidth / 2, y - textHeight / 2 });

    // да/нет
    yesText_.setCharacterSize(20);
    yesText_.setFillColor(Color::Black);
    yesText_.setString(L"Да");
    yesText_.setPosition({ resetText.getPosition().x , resetText.getPosition().y + 20.f });

    noText_.setCharacterSize(20);
    noText_.setFillColor(Color::Black);
    noText_.setString(L"Нет");
    noText_.setPosition({ resetText.getPosition().x + 100.f, resetText.getPosition().y + 20.f });

    window_->draw(resetText);
    window_->draw(yesText_);
    window_->draw(noText_);
}

bool ResetWindow::inYesButton(int x, int y) const {
    float xY{ yesText_.getPosition().x };
    float yY{ yesText_.getPosition().y };
    float width{ yesText_.getLocalBounds().size.x };
    float height{ yesText_.getLocalBounds().size.y };
    return xY <= x && x <= xY + width && yY <= y && y <= yY + height;
}

bool ResetWindow::inNoButton(int x, int y) const {
    float xY{ noText_.getPosition().x };
    float yY{ noText_.getPosition().y };
    float width{ noText_.getLocalBounds().size.x };
    float height{ noText_.getLocalBounds().size.y };
    return xY <= x && x <= xY + width && yY <= y && y <= yY + height;
}

void ResetWindow::draw() {
    drawWindow();
    drawText();
}
