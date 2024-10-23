#include "board.hpp"

#include <array>
#include <cstdio>
#include <utility>

// Board definition

#define SEED_CELL(Epoch, Width, Height)                                        \
  template <> struct Board<Epoch, Width, Height> {                             \
    static constexpr auto isAlive = true;                                      \
  }

SEED_CELL(0, 1, 0);
SEED_CELL(1, 2, 0);
SEED_CELL(2, 0, 0);
SEED_CELL(2, 1, 0);
SEED_CELL(2, 2, 0);

char getBlock(const bool value) { return value ? 'x' : ' '; }

template <std::size_t Epoch, std::size_t Width, std::size_t Height>
struct GetBoardAtEpoch_impl {
  static constexpr char result[] = "N";
};

template <std::size_t Width, std::size_t Height>
struct GetBoardAtEpoch_impl<0, Width, Height> {
  static constexpr char result[] = "0";
};

template <std::size_t Width, std::size_t Height>
struct GetBoardAtEpoch_impl<1, Width, Height> {
  static constexpr char result[] = "1";
};

template <std::size_t Epoch, std::size_t Width, std::size_t Height>
struct GetBoardAtEpoch {
  static constexpr std::array result = {
      GetBoardAtEpoch_impl<Epoch - 1, Width, Height>::result,
      GetBoardAtEpoch_impl<Epoch, Width, Height>::result};
};

int main(int argc, char const *argv[]) {
  using epochs = GetBoardAtEpoch<1, 1, 1>;
  printf("%s\n%s\n", epochs::result[0], epochs::result[1]);
}
