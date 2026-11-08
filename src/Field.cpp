#include "Field.h"
#include <random>
#include "Cell.h"

Field::Field(int rows, int cols, int mines)
    : rows_ { rows }, cols_ { cols }, mines_{ mines } {
    cells_.reserve(rows * cols);
}

void Field::reset(int rows, int cols, int mines) {

}

// size_t надо будет поменять везде
void Field::restart() {
    // Сбрасываем время
    // timeView = timeReal = 0;

    state_ = playing;

    // Сбрасываем все клетки
    for (int x { 0 }; x < rows_; ++x) {
        for (int y { 0 }; y < cols_; ++y) {
            cell(x, y).reset();
        }
    }

    // Расставляем мины
    for (int x { 0 }; x < rows_; ++x) {
        for (int y { 0 }; y < cols_; ++y) {
            std::random_device rd1{};
            std::mt19937 gen {rd1()};
            // ???
            if (gen() % 5 == 0) {
                // Текстура мины под номером 9 на картинке
                cell(x, y).setMine();
            }
        }
    }

    for (int x { 0 }; x < rows_; ++x) {
        for (int y { 0 }; y < cols_; ++y) {
            if (at(x, y).mine()) {
                continue;
            }
            for (int i { x - 1 }; i <= x + 1; ++i) {
                for (int j { y - 1 }; j <= y + 1; ++j) {
                    if (i >= 0 && j >= 0 && i < rows_ && j < cols_ && at(x, y).mine()) {
                        cell(x, y).minesAround_++;
                    }
                }
            }
        }
    }
}

void Field::open(int row, int col) {
    Cell& c{ cell(row, col) };
    if (c.open() || c.flagged()) {
        return;
    }
    if (c.mine()) {
        lose();
    } else {
        c.setOpen();
    }
}

Field::State Field::state() const { return state_; }

int Field::rows() const { return rows_; }
int Field::cols() const { return cols_; }

const Cell& Field::at(int row, int col) const {
    return cells_[row * cols_ + col];
}

Cell& Field::cell(int row, int col) {
    return cells_[row * cols_ + col];
}

void Field::placeMines() {
    // Расставляем мины
    for (size_t x { 0 }; x < rows_; ++x) {
        for (size_t y { 0 }; y < cols_; ++y) {
            std::random_device rd1{};
            std::mt19937 gen { rd1()} ;
            // ???
            if (gen() % 5 == 0) {
                cell(x, y).setMine();
            }
        }
    }
}

void Field::isWin() {
    for (int x { 0 }; x < rows_; ++x) {
        for (int y { 0 }; y < cols_; ++y) {
            // Если осталась хоть бы одна нераскрытая безопасная клетка, то игра продолжается
            if (!cell(x, y).open() && !cell(x, y).mine()) {
                return;
            }
        }
    }
    state_ = State::won;
}

void Field::lose() {
    state_ = State::lost;
    for (int x { 0 }; x < rows_; ++x) {
        for (int y { 0 }; y < cols_; ++y) {
            // Показываем все непомеченные мины
            if (!cell(x, y).flagged() && cell(x, y).mine()) {
                cell(x, y).setOpen();
            }
        }
    }
}
