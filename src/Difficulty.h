#ifndef MINESWEEPER_DIFFICULTY_H
#define MINESWEEPER_DIFFICULTY_H

struct Difficulty {
    int rows{};
    int cols{};
    int mines{};
};

namespace Difficulties {
    inline constexpr Difficulty Beginner{ 9, 9, 10 };
    inline constexpr Difficulty Intermediate{ 16, 16, 40 };
    inline constexpr Difficulty Expert{ 16, 30, 99 };
}

#endif //MINESWEEPER_DIFFICULTY_H
