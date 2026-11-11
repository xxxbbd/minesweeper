#include "Cell.h"

bool Cell::mine() const {
    return isMine_;
}
bool Cell::open() const {
    return isOpen_;
}
bool Cell::flagged() const {
    return isFlagged_;
}
int Cell::minesAround() const {
    return minesAround_;
}
void Cell::setMine() {
    isMine_ = true;
}
void Cell::setOpen() {
    isOpen_ = true;
}
void Cell::setFlagged(bool flagged) {
    isFlagged_ = flagged;
}
void Cell::reset() {
    isMine_ = false;
    isOpen_ = false;
    isFlagged_ = false;
    minesAround_ = 0;
}