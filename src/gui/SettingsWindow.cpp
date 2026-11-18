#include "SettingsWindow.h"
#include <SFML/Graphics.hpp>

using namespace sf;

SettingsWindow::SettingsWindow(RenderWindow* window)
    : window_{ window }, active_{ true } {}

void SettingsWindow::run() {
    while (active_) {
        eventHandler();
        render();
    }
}

void SettingsWindow::drawBackButton() {
    RectangleShape backButton(Vector2f(30.f, 30.f));
    backButton.setFillColor(Color::Black);
    backButton.setPosition({ 0.f, 0.f });
    window_->draw(backButton);
}

bool inBackButton(int x, int y) {
    return 0.f <= x && x <= 0.f + 30.f
            && 0.f <= y && y <= 0.f + 30.f;
}

void SettingsWindow::eventHandler() {
    while (const std::optional event{ window_->pollEvent() }) {
        if (event->is<Event::Closed>()) { window_->close(); }

        Vector2i pos = Mouse::getPosition(*window_);
        if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed) {

            if (mouseButtonPressed->button == Mouse::Button::Left && inBackButton(pos.x, pos.y)) {
                active_ = false;
            }
        }
    }
}

void SettingsWindow::render() {
    window_->clear(Color::White);
    RectangleShape settingsWindow(Vector2f(384.f, 384.f));
    settingsWindow.setFillColor(Color::White);
    settingsWindow.setPosition({ 0.f, 0.f });

    Font font("assets/fonts/Monaco.ttf");
    Text text(font);
    text.setCharacterSize(32);
    text.setFillColor(Color::Black);
    text.setStyle(Text::Bold);
    text.setString("difficulty");
    text.setPosition({ 100.f, 100.f });

    window_->draw(settingsWindow);
    window_->draw(text);
    drawBackButton();
    window_->display();
}