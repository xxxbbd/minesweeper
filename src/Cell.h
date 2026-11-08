#ifndef MINESWEEPER_CELL_H
#define MINESWEEPER_CELL_H

class Cell {
public:
    Cell() = default;
    bool mine() const;
    bool open() const;
    bool flagged() const;
    int minesAround() const;
    void setMine();
    void setOpen();
    void setFlagged(bool);
private:
    void reset();
    bool isMine_{ false };
    bool isOpen_{ false };
    bool isFlagged_{ false };
    int minesAround_{ 0 };

    friend class Field;
};

#endif //MINESWEEPER_CELL_H
