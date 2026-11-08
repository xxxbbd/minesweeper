#include <array>

#include "AppearanceWindow.h"
#include "GameWindow.h"

int main() {

    // RenderWindow window(VideoMode({ 384, 416 }), "Minesweeper");
    //
    // // Загрузка текстуры и создание спрайта
    // Texture cellTexture("/Users/a1/CLionProjects/minesweeper/src/Minesweeper.jpg");
    // cellTexture.setSmooth(true);
    // Sprite cellSprite(cellTexture);
    //
    // // Кнопка сброса
    // Texture resetTexture("/Users/a1/CLionProjects/minesweeper/src/Reset.png");
    // resetTexture.setSmooth(true);
    // CircleShape circle(16.f);
    // circle.setTexture(&resetTexture);
    // circle.setPosition({ 176.f, 0.f });
    //
    // Font font("/Users/a1/CLionProjects/minesweeper/src/Monaco.ttf");
    // Text timeText(font);
    // timeText.setCharacterSize(32);              // Размер текста в пикселях
    // timeText.setFillColor(Color::Black);        // Цвет текста
    // timeText.setStyle(Text::Bold);
    // timeText.setPosition({320.f, 0.f});  // Позиция на экране
    //
    // // Окно при запуске программы
    // bool isStartWindowOpen{ true };
    // RectangleShape startWindow(Vector2f(384.f, 416.f));
    // startWindow.setFillColor(Color::White);
    // startWindow.setPosition({ 0.f, 0.f });
    //
    // // Текст на главном экране
    // Text startText(font);
    // startText.setCharacterSize(32);
    // startText.setFillColor(Color::Black);
    // startText.setStyle(Text::Bold);
    // startText.setPosition({ 192.f, 208.f });
    // startText.setString("GO?");
    //
    // // Кнопка настройки
    // CircleShape settingsButton(16.f);
    // settingsButton.setFillColor(Color::Black);
    // settingsButton.setPosition({ 10.f, 10.f });
    //
    // // Окно настроек
    // bool isSettingsWindowOpen{ false };
    // RectangleShape settingsWindow(Vector2f(384.f, 416.f));
    // settingsWindow.setFillColor(Color::White);
    // settingsWindow.setPosition({ 0.f, 0.f });
    //
    // // Текст в окне настроек
    // Text gameTypeText(font);
    // gameTypeText.setCharacterSize(16);
    // gameTypeText.setFillColor(Color::Black);
    // gameTypeText.setStyle(Text::Bold);
    // gameTypeText.setPosition({ 192.f, 208.f });
    // // L чтобы использовать wide literal string, иначе текст отображается неправильно
    // gameTypeText.setString(L"Тип игры");
    //
    // // Окно подтверждения начала новой игры
    // bool isResetWindowOpen { false };
    // RectangleShape resetWindow(Vector2f(300.f, 20.f));
    // resetWindow.setFillColor(Color::White);
    // resetWindow.setOutlineColor(Color::Black);
    // resetWindow.setOutlineThickness(2.f);
    // resetWindow.setPosition({ 192.f, 208.f });
    //
    // // Текст в окне подтверждения начала новой игры
    // Text resetText(font);
    // resetText.setCharacterSize(10);
    // resetText.setFillColor(Color::Black);
    // resetText.setStyle(Text::Bold);
    // resetText.setPosition({ 192.f, 208.f });
    // resetText.setString(L"Вы хотите прекратить текущую игру?");
    //
    // // Кнопка закрытия окна сброса
    // RectangleShape resetWindowCloseButton(Vector2f( 8.f, 8.f ));
    // resetWindowCloseButton.setFillColor(Color::Red);
    // resetWindowCloseButton.setPosition({ 0.f, 0.f });
    //
    // startNewGame();
    //
    // while (window.isOpen()) {
    //
    //     using namespace parameters;
    //
    //     // Устанавливаем белый фон
    //     window.clear(Color::White);
    //
    //     int gameOver { isGameOver() };
    //
    //     if (isStartWindowOpen) {
    //         window.draw(startWindow);
    //         window.draw(startText);
    //         window.draw(settingsButton);
    //     }
    //
    //     if (isSettingsWindowOpen) {
    //         window.draw(settingsWindow);
    //         window.draw(gameTypeText);
    //     }
    //
    //     if (!isStartWindowOpen) {
    //         if (gameOver == -1) {
    //             for (size_t x { 0 }; x < fieldView.size(); ++x) {
    //                 for (size_t y { 0 }; y < fieldView[x].size(); ++y) {
    //                     // Показываем все непомеченные мины
    //                     if (fieldView[x][y] == 10 && fieldLogic[x][y] == 9) {
    //                         fieldView[x][y] = 9;
    //                     }
    //                 }
    //             }
    //         }
    //
    //         for (size_t x { 0 }; x < fieldView.size(); ++x)
    //             for (size_t y { 0 }; y < fieldView[x].size(); ++y) {
    //                 // Вырезаем из спрайта нужный нам квадратик текстуры
    //                 cellSprite.setTextureRect(IntRect({fieldView[x][y] * w, 0}, {w, w}));
    //                 // устанавливаем его в заданную позицию
    //                 cellSprite.setPosition({ static_cast<float>(x * w), static_cast<float>((y * w) + 32)});
    //                 // и отрисовываем
    //                 window.draw(cellSprite);
    //             }
    //
    //         // Отрисовываем кнопку сброса
    //         window.draw(circle);
    //
    //         // Обновляем значение времени каждую секунду
    //         if (parameters::clock.getElapsedTime().asSeconds() >= 1.0f && !isResetWindowOpen && !gameOver) {
    //             ++timeReal;
    //             if (timeView < 999) {
    //                 ++timeView;
    //             }
    //             parameters::clock.restart(); // Перезапускаем таймер
    //         }
    //
    //         if (timeView < 10) { timeText.setString("00" + std::to_string(timeView)); }
    //         else if (timeView < 100) { timeText.setString("0" + std::to_string(timeView)); }
    //         else { timeText.setString(std::to_string(timeView)); }
    //         window.draw(timeText);
    //
    //         if (isResetWindowOpen) {
    //             window.draw(resetWindow);
    //             window.draw(resetText);
    //             window.draw(resetWindowCloseButton);
    //         }
    //     }
    //     eventHandler(window, isResetWindowOpen, gameOver); // !!!
    //     // Отображаем всю композицию на экране
    //     window.display();
    // }

    AppearanceWindow window;
    window.run();
    return 0;
}
