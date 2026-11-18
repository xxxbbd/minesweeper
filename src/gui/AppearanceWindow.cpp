#include "AppearanceWindow.h"
#include <SFML/Graphics.hpp>
#include "GameWindow.h"
#include "SettingsWindow.h"

using namespace sf;

bool SettingsButton::inSettingsButton(int x, int y) {
    return x_ <= x && x <= x_ + width_
            && y_ <= y && y <= y_ + height_;
}

void SettingsButton::setPosition(Vector2f pos) {
    x_ = pos.x;
    y_ = pos.y;
}

void SettingsButton::draw(RenderWindow* window) {
    CircleShape shape(20.f);
    shape.setFillColor(Color::Black);
    shape.setPosition({ x_, y_ });
    window->draw(shape);
}

AppearanceWindow::AppearanceWindow()
    : window_{VideoMode({384, 384}), "Minesweeper"} {}

void AppearanceWindow::run() {
    while (window_.isOpen()) {
        eventHandler();
        render();
    }
}

void AppearanceWindow::eventHandler() {
    while (const std::optional event { window_.pollEvent() }) {
        if (event->is<Event::Closed>()) { window_.close(); }

        Vector2i pos = Mouse::getPosition(window_);
        if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed) {

            if (mouseButtonPressed->button == Mouse::Button::Left && sButton_.inSettingsButton(pos.x, pos.y)) {
                SettingsWindow sWindow(&window_);
                sWindow.run();
            }
            else {
                GameWindow w(&window_);
                w.run();
            }
        }
    }
}

void AppearanceWindow::render() {
    window_.clear(Color::White);
    // Окно при запуске программы
    RectangleShape startWindow(Vector2f(384.f, 384.f));
    startWindow.setFillColor(Color::White);
    startWindow.setPosition({ 0.f, 0.f });

    // Текст на главном экране
    Font font("assets/fonts/Monaco.ttf");
    Text startText(font);
    startText.setCharacterSize(32);
    startText.setFillColor(Color::Black);
    startText.setStyle(Text::Bold);
    startText.setString("GO?");

    FloatRect textBounds{ startText.getLocalBounds() };
    float textWidth { textBounds.size.x };
    float textHeight { textBounds.size.y };
    Vector2u windowSize { window_.getSize() };
    float x{ static_cast<float>(windowSize.x) / 2 - textWidth / 2 };
    float y{ static_cast<float>(windowSize.y) / 2 - textHeight / 2 };
    startText.setPosition({ x, y });

    // Кнопка настройки
    sButton_.setPosition({ 10.f, 10.f });

    window_.draw(startWindow);
    window_.draw(startText);
    sButton_.draw(&window_);
    window_.display();
}
