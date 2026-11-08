#include "AppearanceWindow.h"
#include <SFML/Graphics.hpp>
#include "GameWindow.h"

using namespace sf;

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

        // Получаем координаты курсора мышки относительно окна нашего приложения
        Vector2i pos = Mouse::getPosition(window_);
        int x = pos.x / 32;
        int y = pos.y / 32;

        if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed) {
            GameWindow w(&window_);
            w.run();
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
    Font font("/Users/a1/CLionProjects/minesweeper/src/Monaco.ttf");
    Text startText(font);
    startText.setCharacterSize(32);
    startText.setFillColor(Color::Black);
    startText.setStyle(Text::Bold);
    startText.setPosition({ 192.f, 208.f });
    startText.setString("GO?");

    // Кнопка настройки
    CircleShape settingsButton(16.f);
    settingsButton.setFillColor(Color::Black);
    settingsButton.setPosition({ 10.f, 10.f });

    window_.draw(startWindow);
    window_.draw(startText);
    window_.draw(settingsButton);
    window_.display();
}
