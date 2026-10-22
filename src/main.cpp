#include <array>
#include <random>
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;

// Ширина клетки
int w { 32 };
static std::array<std::array<int, 12>, 12> fieldLogic{};
static std::array<std::array<int, 12>, 12> fieldView{};

int main();

void eventHandler(RenderWindow& window, bool& isResetWindowOpen, bool gameOver) {
    while (const std::optional event { window.pollEvent() }) {
        if (event->is<Event::Closed>()) { window.close(); }

        // Получаем координаты курсора мышки относительно окна нашего приложения
        Vector2i pos = Mouse::getPosition(window);
        int x = pos.x / w;
        int y = pos.y / w - 1; // -1 так как y = 0 под таймер

        // Определяем, была ли нажата кнопка мыши (на клетку)?
        if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed && y >= 0 && !isResetWindowOpen && !gameOver) {
            // Если была нажата левая кнопка мыши, то открываем клетку
            if (mouseButtonPressed->button == Mouse::Button::Right) {
                if (fieldView[x][y] != 11) {
                    fieldView[x][y] = fieldLogic[x][y];
                }
            }
            // Если была нажата правая кнопка мыши, то отображаем флажок
            else if (mouseButtonPressed->button == Mouse::Button::Left) {
                if (fieldView[x][y] == 10) {
                    fieldView[x][y] = 11;
                } else if (fieldView[x][y] == 11) {
                    // Если флаг уже был, убираем его
                    fieldView[x][y] = 10;
                }
            }
        }
        // ???
        auto inResetButton = [](int x, int y) {
            return 5 <= x && x <= 6 && y < 0;
        };
        if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed && inResetButton(x, y) && !isResetWindowOpen && !gameOver) {
            if (mouseButtonPressed->button == Mouse::Button::Left) {
                isResetWindowOpen = true; //
            }
        }
        // ???
        auto inResetWindowCloseButton = [](int x, int y) {
            return x == 0 && y == -1;
        };
        if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed && inResetWindowCloseButton(x, y) && isResetWindowOpen && !gameOver) {
            if (mouseButtonPressed->button == Mouse::Button::Left) {
                isResetWindowOpen = false;
            }
        }
        // Перезапуск игры
        if (const auto* mouseButtonPressed { event->getIf<Event::MouseButtonPressed>() }; mouseButtonPressed && inResetButton(x, y) && gameOver) {
            if (mouseButtonPressed->button == Mouse::Button::Left) {
                // ???
                main();
            }
        }
    }
}

// ???
int isGameOver() {
    for (size_t x { 0 }; x < fieldView.size(); ++x) {
        for (size_t y { 0 }; y < fieldView[x].size(); ++y) {
            if (fieldView[x][y] == 9) {
                return -1;
            }
        }
    }
    for (size_t x { 0 }; x < fieldView.size(); ++x) {
        for (size_t y { 0 }; y < fieldView[x].size(); ++y) {
            // Если осталась хоть бы одна безопасная клетка, то игра продолжается
            if (fieldView[x][y] == 10 && fieldLogic[x][y] != 9)
                return 0;
            // Если флаг стоит не на бомбе, то игра продолжается
            if (fieldView[x][y] == 11 && fieldLogic[x][y] != 9)
                return 0;
        }
    }
    return 1;
}

int main() {

    RenderWindow window(VideoMode({ 384, 416 }), "Minesweeper");

    // Загрузка текстуры и создание спрайта
    Texture cellTexture("/Users/a1/CLionProjects/minesweeper/src/Minesweeper.jpg");
    cellTexture.setSmooth(true);
    Sprite cellSprite(cellTexture);

    // Кнопка сброса
    Texture resetTexture("/Users/a1/CLionProjects/minesweeper/src/Reset.png");
    resetTexture.setSmooth(true);
    CircleShape circle(16.f);
    circle.setTexture(&resetTexture);
    circle.setPosition({ 176.f, 0.f });

    // Заполняем элементы "внешнего" массива начальными значениями
    for (size_t x { 0 }; x < fieldView.size(); ++x) {
        for (size_t y { 0 }; y < fieldView[x].size(); ++y) {
            fieldView[x][y] = 10;
        }
    }

	// Расставляем мины
    for (size_t x { 0 }; x < fieldLogic.size(); ++x) {
        for (size_t y { 0 }; y < fieldLogic[x].size(); ++y) {
            std::random_device rd1{};
            std::mt19937 gen {rd1()};
            // ???
            if (gen() % 5 == 0) {
                // Текстура мины под номером 9 на картинке
                fieldLogic[x][y] = 9;
            } else {
                fieldLogic[x][y] = 0;
            }
        }
    }

    for (size_t x { 0 }; x < fieldLogic.size(); ++x) {
        for (size_t y { 0 }; y < fieldLogic[x].size(); ++y) {
            if (fieldLogic[x][y] == 9) {
                continue;
            }
            for (int i { static_cast<int>(x) - 1 }; i <= static_cast<int>(x) + 1; ++i) {
                for (int j { static_cast<int>(y) - 1 }; j <= static_cast<int>(y) + 1; ++j) {
                    if (i >= 0 && j >= 0 && i < fieldLogic.size() && j < fieldLogic[x].size() && fieldLogic[i][j] == 9) {
                        ++fieldLogic[x][y];
                    }
                }
            }
        }
    }

    Font font("/Users/a1/CLionProjects/minesweeper/src/Monaco.ttf");
    Text timeText(font);
    timeText.setCharacterSize(32);              // Размер текста в пикселях
    timeText.setFillColor(Color::Black);        // Цвет текста
    timeText.setStyle(Text::Bold);
    timeText.setPosition({320.f, 0.f});  // Позиция на экране

    int timeView { 0 };
    int timeReal { 0 };
    Clock clock; // Внутренние часы SFML для замера времени

    bool isResetWindowOpen { false };
    RectangleShape resetWindow(Vector2f(300.f, 20.f));
    resetWindow.setFillColor(Color::White);
    resetWindow.setOutlineColor(Color::Black);
    resetWindow.setOutlineThickness(2.f);
    resetWindow.setPosition({ 192.f, 208.f });

    // Текст в окне подтверждения начала новой игры
    Text resetText(font);
    resetText.setCharacterSize(12);              // Размер текста в пикселях
    resetText.setFillColor(Color::Black);        // Цвет текста
    resetText.setStyle(Text::Bold);
    resetText.setPosition({ 192.f, 208.f });  // Позиция на экране
    // L чтобы использовать wide literal string, иначе текст отображается неправильно
    resetText.setString(L"Вы хотите прекратить текущую игру?");

    // Кнопка закрытия окна сброса
    RectangleShape resetWindowCloseButton(Vector2f( 8.f, 8.f ));
    resetWindowCloseButton.setFillColor(Color::Red);
    resetWindowCloseButton.setPosition({ 0.f, 0.f });

    while (window.isOpen()) {

        // Устанавливаем белый фон
        window.clear(Color::White);

        int gameOver { isGameOver() };
        if (gameOver == -1) {
            for (size_t x { 0 }; x < fieldView.size(); ++x) {
                for (size_t y { 0 }; y < fieldView[x].size(); ++y) {
                    // Показываем все непомеченные мины
                    if (fieldView[x][y] == 10 && fieldLogic[x][y] == 9) {
                        fieldView[x][y] = 9;
                    }
                }
            }
        }

        for (size_t x { 0 }; x < fieldView.size(); ++x)
            for (size_t y { 0 }; y < fieldView[x].size(); ++y) {
                // Вырезаем из спрайта нужный нам квадратик текстуры
                cellSprite.setTextureRect(IntRect({fieldView[x][y] * w, 0}, {w, w}));
                // Устанавливаем его в заданную позицию...
                cellSprite.setPosition({ static_cast<float>(x * w), static_cast<float>((y * w) + 32)});
                // и отрисовываем
                window.draw(cellSprite);
            }

        window.draw(circle);

        // Обновляем значение времени каждую секунду
        if (clock.getElapsedTime().asSeconds() >= 1.0f && !isResetWindowOpen && !gameOver) {
            ++timeReal;
            if (timeView < 999) {
                ++timeView;
            }
            clock.restart(); // Перезапускаем таймер
        }

        if (timeView < 10) { timeText.setString("00" + std::to_string(timeView)); }
        else if (timeView < 100) { timeText.setString("0" + std::to_string(timeView)); }
        else { timeText.setString(std::to_string(timeView)); }
        window.draw(timeText);

        if (isResetWindowOpen) {
            window.draw(resetWindow);
            window.draw(resetText);
            window.draw(resetWindowCloseButton);
        }

        eventHandler(window, isResetWindowOpen, gameOver); // !!!

        // Отображаем всю композицию на экране
        window.display();
    }
    
    return 0;
}
