#include "GameWindow.h"
#include <SFML/Graphics.hpp>

using namespace sf;

static constexpr int CELL_SIZE{ 32 };

GameWindow::GameWindow(RenderWindow* window)
    : field_{ difficulty_.rows, difficulty_.cols, difficulty_.mines }, window_{ window }, rWindow_{ window }, rButton_{ window }, active_{ true } {
    // меняем размер окна при переключении с начального
    window_->setSize({static_cast<unsigned int>(field_.rows()) * CELL_SIZE, static_cast<unsigned int>(field_.cols()) * CELL_SIZE + CELL_SIZE});
    FloatRect visibleArea({0.f, 0.f}, {static_cast<float>(field_.rows() * CELL_SIZE), static_cast<float>(field_.cols() * CELL_SIZE + CELL_SIZE)});
    window_->setView(View(visibleArea));
    if (!cellTexture_.loadFromFile("assets/textures/Minesweeper.jpg")) {
        // to do
    }
    cellTexture_.setSmooth(true);
}

void GameWindow::run() {
    // начинаем новую игру
    field_.restart();
    while (active_) {
        eventHandler();
        render();
    }
}

void GameWindow::eventHandler() {
    while (const std::optional event{ window_->pollEvent() }) {
        if (event->is<Event::Closed>()) {
            // to do
            active_ = false;
            window_->close();
        }
        if (event->is<Event::Resized>()) {
            // to do
        }

        // Получаем координаты курсора мышки относительно окна нашего приложения
        Vector2i pos = Mouse::getPosition(*window_);
        int x = pos.x / CELL_SIZE;
        int y = pos.y / CELL_SIZE - 1; // -1 так как y = 0 под таймер

        // Определяем, была ли нажата кнопка мыши (на клетку)?
        if (const auto* mouseButtonPressed{ event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed != nullptr) {

            // Перезапуск игры
            if (resetWindowOpen_) {
                if (mouseButtonPressed->button == Mouse::Button::Left) {
                    if (rWindow_.inYesButton(pos.x, pos.y)) {
                        resetWindowOpen_ = false;
                        field_.restart();
                        seconds_ = 0;
                        clock_.reset();
                        clock_.start();
                    }
                    if (rWindow_.inNoButton(pos.x, pos.y)) {
                        resetWindowOpen_ = false;;
                    }
                }
                return;
            }

            // Перезапуск игры
            if (field_.state() == Field::State::lost) {
                if (mouseButtonPressed->button == Mouse::Button::Left && rButton_.in(pos.x, pos.y)) {
                    field_.restart();
                    seconds_ = 0;
                    clock_.reset();
                    clock_.start();
                }
                return;
            }

            if (rButton_.in(pos.x, pos.y)) {
                if (mouseButtonPressed->button == Mouse::Button::Left) {
                    resetWindowOpen_ = true;
                }
            }

            if (y >= 0) {
                // Если была нажата правая кнопка мыши, то открываем клетку или применяем аккорд
                if (mouseButtonPressed->button == Mouse::Button::Right) {
                    field_.reveal(x, y);
                }
                // Если была нажата левая кнопка мыши, то отображаем флажок или убираем его
                else if (mouseButtonPressed->button == Mouse::Button::Left) {
                    field_.flag(x, y);
                }
            }
        }
    }
}

void GameWindow::drawField() {
    Sprite cellSprite{ cellTexture_ };
    for (int x { 0 }; x < field_.rows(); ++x) {
        for (int y { 0 }; y < field_.cols(); ++y) {
            int cellId { 10 };
            if (field_.at(x, y).open()) {
                cellId = field_.at(x, y).mine() ? 9 : field_.at(x, y).minesAround();
            } else if (field_.at(x, y).flagged()) {
                cellId = 11;
            }
            cellSprite.setTextureRect(IntRect({cellId * CELL_SIZE, 0}, {CELL_SIZE, CELL_SIZE}));
            cellSprite.setPosition({ static_cast<float>(x * CELL_SIZE), static_cast<float>((y * CELL_SIZE) + CELL_SIZE)});
            window_->draw(cellSprite);
        }
    }
}

void GameWindow::drawTimer() {
    Font font("assets/fonts/Monaco.ttf");
    Text timeText(font);
    timeText.setCharacterSize(CELL_SIZE);       // Размер текста в пикселях
    timeText.setFillColor(Color::Black);        // Цвет текста
    timeText.setStyle(Text::Bold);

    if (seconds_ < 10) { timeText.setString("00" + std::to_string(seconds_)); }
    else if (seconds_ < 100) { timeText.setString("0" + std::to_string(seconds_)); }
    else if (seconds_ < 1000) { timeText.setString(std::to_string(seconds_)); }
    else { timeText.setString("999"); }

    FloatRect textBounds{ timeText.getLocalBounds() };
    float textWidth { textBounds.size.x };
    float textHeight { textBounds.size.y };
    Vector2u windowSize { window_->getSize() };
    float x{ static_cast<float>(windowSize.x) - textWidth - 10};
    float y{ 0 };
    timeText.setPosition({x, y});  // Позиция на экране

    if (clock_.getElapsedTime().asSeconds() >= 1.0f && field_.state() != Field::State::lost) {
        ++seconds_;
        clock_.restart(); // Перезапускаем таймер
    }
    window_->draw(timeText);
}

void GameWindow::render() {
    window_->clear(Color::White);
    drawField();
    drawTimer();
    rButton_.draw();
    if (resetWindowOpen_) {
        rWindow_.draw();
    }
    window_->display();
}