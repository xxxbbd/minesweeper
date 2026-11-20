#ifndef MINESWEEPER_FIELD_H
#define MINESWEEPER_FIELD_H

#include <vector>
#include "Cell.h"

class Field {
public:
    enum State {
        ready,
        won,
        lost,
        playing,
    };

    Field(int rows, int cols, int mines);
    // reset нужен при изменении уровня сложности
    void reset(int rows, int cols, int mines);
    // restart для начала новой игры при той же сложности
    void restart();
    void reveal(int row, int col);
    void flag(int row, int col);
    State state() const;

    int rows() const;
    int cols() const;
    const Cell& at(int row, int col) const;

private:
    Cell& cell(int row, int col);
    void placeMines(int row, int col);
    void isWin();
    void lose();
    std::vector<std::pair<int, int>> getNeighbours(int row, int col);
    void cascadeReveal(int row, int col);
    void chord(int row, int col);

    std::vector<Cell> cells_{};
    int rows_{ 0 };
    int cols_{ 0 };
    int mines_{ 0 };
    int marked_{ 0 }; // to do
    State state_{ ready };

    friend class GameWindow;
};

#endif //MINESWEEPER_FIELD_H
