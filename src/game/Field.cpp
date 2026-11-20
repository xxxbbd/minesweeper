#include "Field.h"
#include <random>
#include "Cell.h"
#include "SFML/Window/Keyboard.hpp"

Field::Field(int rows, int cols, int mines)
    : rows_ { rows }, cols_ { cols }, mines_{ mines } {
    cells_.reserve(rows * cols);
}

void Field::reset(int rows, int cols, int mines) {
    // to do
}

void Field::restart() {
    state_ = ready;
    // Сбрасываем все клетки
    for (int x { 0 }; x < rows_; ++x) {
        for (int y { 0 }; y < cols_; ++y) {
            cell(x, y).reset();
        }
    }
}

void Field::reveal(int row, int col) {
    Cell& c{ cell(row, col) };
    if (c.flagged()) {
        return;
    }
    if (c.open()) {
        chord(row, col);
    }
    if (state_ == ready) {
        placeMines(row, col);
        state_ = playing;
    }
    if (c.mine()) {
        lose();
    } else {
        cascadeReveal(row, col);
        // to do
        isWin();
    }
}

void Field::flag(int row, int col) {
    Cell& c{ cell(row, col) };
    if (c.open()) {
        return;
    }
    if (!c.flagged()) {
        c.setFlagged(true);
    } else {
        c.setFlagged(false);
    }
}

void Field::cascadeReveal(int row, int col) {
    std::vector<std::pair<int, int>> order{ { row, col } };
    while (!order.empty()) {
        std::pair p{ order.back() };
        order.pop_back();
        Cell& c{ cell(p.first, p.second) };
        if (c.open() || c.flagged()) {
            continue;
        }
        c.setOpen();
        // ++marked_; to do

        // если вокруг нет мин, добавляем в очередь соседние клетки
        if (c.minesAround() == 0) {
            for (const auto neighbour : getNeighbours(p.first, p.second)) {
                order.push_back(neighbour);
            }
        }
    }
}

// срабатывает при нажатии правой кнопкой мыши на уже открытую клетку, если рядом с ней стоит столько же флажков, сколько указано в самой клетке
void Field::chord(int row, int col) {
    if (state_ != playing) {
        return;
    }
    const Cell& c{ at(row, col) };
    if (!c.open() || c.minesAround() == 0) {
        return;
    }
    int flags{ 0 };
    for (const auto n : getNeighbours(row, col)) {
        if (at(n.first, n.second).flagged()) {
            ++flags;
        }
    }
    if (flags != c.minesAround()) {
        return;
    }

    for (const auto n : getNeighbours(row, col)) {
        const Cell& nC{ at(n.first, n.second) };
        if (!nC.open() && !nC.flagged() && nC.mine()) {
            // to do
            lose();
            return;
        }
        if (!nC.open() && !nC.flagged()) {
            cascadeReveal(n.first, n.second);
            isWin();
        }
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

// Расставляем мины
void Field::placeMines(int row, int col) {
    int placed{ 0 };
    std::random_device rd{};
    std::mt19937 gen{ rd() };
    std::uniform_int_distribution distX(0, rows_ - 1);
    std::uniform_int_distribution distY(0, cols_ - 1);
    while (placed < mines_) {
        int x{ distX(gen) };
        int y{ distY(gen) };
        // делаем безопасную зону
        if (row - 1 <= x && x <= row + 1 && col - 1 <= y && y <= col + 1) {
            continue;
        }
        cell(x, y).setMine();
        ++placed;
    }
    for (int x { 0 }; x < rows_; ++x) {
        for (int y { 0 }; y < cols_; ++y) {
            if (at(x, y).mine()) {
                continue;
            }
            int count{ 0 };
            for (const auto neighbour : getNeighbours(x, y)) {
                if (cell(neighbour.first, neighbour.second).mine()) {
                    ++count;
                }
            }
            cell(x, y).minesAround_ = count;
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

std::vector<std::pair<int, int>> Field::getNeighbours(int row, int col) {
    std::vector<std::pair<int, int>> v{};
    for (int r{ row - 1 }; r <= row + 1; ++r) {
        for (int c{ col - 1 }; c <= col + 1; ++c) {
            if (r == row && c == col) {
                continue;
            }
            if (0 <= r && r < rows_ && 0 <= c && c < cols_) {
                v.emplace_back( r, c );
            }
        }
    }
    return v;
}