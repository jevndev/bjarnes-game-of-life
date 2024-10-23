#include "board.hpp"
#include "printing.hpp"

#include <cstdio>

// Board definition

#define SEED_CELL(Width, Height, Epoch)                                        \
  template <> struct Board<Width, Height, Epoch> {                             \
    static constexpr auto isAlive = true;                                      \
  }

SEED_CELL(0, 1, 0);
SEED_CELL(1, 2, 0);
SEED_CELL(2, 0, 0);
SEED_CELL(2, 1, 0);
SEED_CELL(2, 2, 0);

int main(int argc, char const *argv[]) {
  std::printf("%s\n", GetBoard<0, 3, 3>::board);

  std::printf("%s\n", GetBoard<1, 3, 3>::board);

  std::printf("%s\n", GetBoard<2, 3, 3>::board);
}
