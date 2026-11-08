#include "GameWindow.h"
#include <SFML/Graphics.hpp>
#include "Cell.h"

using namespace sf;

static constexpr int CELL_SIZE{ 32 };

GameWindow::GameWindow(RenderWindow* window)
    : field_{ difficulty_.rows, difficulty_.cols, difficulty_.mines }, window_(window) {
    // меняем размер окна при переключении с начального
    window_->setSize({static_cast<unsigned int>(field_.rows()) * CELL_SIZE, static_cast<unsigned int>(field_.cols()) * CELL_SIZE + CELL_SIZE});
    FloatRect visibleArea({0.f, 0.f}, {static_cast<float>(field_.rows() * CELL_SIZE), static_cast<float>(field_.cols() * CELL_SIZE + CELL_SIZE)});
    window_->setView(View(visibleArea));
}

void GameWindow::run() {
    // начинаем новую игру
    field_.restart();
    while (window_->isOpen()) {
        eventHandler();
        render();
    }
}

void GameWindow::eventHandler() {
    while (const std::optional event { window_->pollEvent() }) {
        if (event->is<Event::Closed>()) { window_->close(); }
        if (event->is<Event::Resized>()) {
            // to do
        }

        // Получаем координаты курсора мышки относительно окна нашего приложения
        Vector2i pos = Mouse::getPosition(*window_);
        int x = pos.x / CELL_SIZE;
        int y = pos.y / CELL_SIZE - 1; // -1 так как y = 0 под таймер

        // Определяем, была ли нажата кнопка мыши (на клетку)?
        if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed && y >= 0 && field_.state() != Field::State::lost) {
            // Если была нажата левая кнопка мыши, то открываем клетку
            if (mouseButtonPressed->button == Mouse::Button::Right) {
                field_.open(x, y);
            }
            // Если была нажата правая кнопка мыши, то отображаем флажок
            else if (mouseButtonPressed->button == Mouse::Button::Left) {
                if (!field_.at(x, y).open()) {
                    field_.cell(x, y).setFlagged(!field_.at(x, y).flagged()); // подумать над способом получения доступа к клетке поля
                }
            }
        }
        // ???
        auto inResetButton = [](int x, int y) {
            return 5 <= x && x <= 6 && y < 0;
        };
        // if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed && inResetButton(x, y) && !isResetWindowOpen && !gameOver) {
        //     if (mouseButtonPressed->button == Mouse::Button::Left) {
        //         isResetWindowOpen = true; //
        //     }
        // }
        // // ???
        // auto inResetWindowCloseButton = [](int x, int y) {
        //     return x == 0 && y == -1;
        // };
        // if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed && inResetWindowCloseButton(x, y) && isResetWindowOpen && !gameOver) {
        //     if (mouseButtonPressed->button == Mouse::Button::Left) {
        //         isResetWindowOpen = false;
        //     }
        // }
        // Перезапуск игры (про таймер не забыть)
        // if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed && inResetButton(x, y) && field_.state() != Field::State::lost) {
        //     if (mouseButtonPressed->button == Mouse::Button::Left) {
        //         field_.restart();
        //     }
        // }
        auto inSettingsButton = [](int x, int y) {
            return true; //
        };
        // if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed && inSettingsButton(x, y)) {
        //     if (mouseButtonPressed->button == Mouse::Button::Left) {
        //         field_.restart();
        //     }
        // }
    }
}

void GameWindow::drawField() const{
    Texture cellTexture("/Users/a1/CLionProjects/minesweeper/src/Minesweeper.jpg");
    cellTexture.setSmooth(true);
    Sprite cellSprite(cellTexture);
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
    Font font("/Users/a1/CLionProjects/minesweeper/src/Monaco.ttf");
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
    window_->display();
}
