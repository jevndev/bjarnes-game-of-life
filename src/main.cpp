#include "board.hpp"

#include <cstdio>

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
void printBlock() {
  putchar(getBlock(Board<Width, Height, Epoch>::isAlive));
}

template <std::size_t Epoch, std::size_t Width, std::size_t Height,
          std::size_t TotalWidth>
struct PrintBoardImpl {
  void operator()() const {
    PrintBoardImpl<Epoch, Width - 1, Height, TotalWidth>()();
    printBlock<Epoch, Width, Height>();
  }
};

template <std::size_t Epoch, std::size_t Height, std::size_t TotalWidth>
struct PrintBoardImpl<Epoch, 0, Height, TotalWidth> {
  void operator()() const {
    PrintBoardImpl<Epoch, TotalWidth, Height - 1, TotalWidth>()();
    putchar('\n');
    printBlock<Epoch, 0, Height>();
  }
};

template <std::size_t Epoch, std::size_t TotalWidth>
struct PrintBoardImpl<Epoch, 0, 0, TotalWidth> {
  void operator()() const { printBlock<Epoch, 0, 0>(); }
};

template <std::size_t Epoch, std::size_t Width, std::size_t Height>
void printBoard() {
  PrintBoardImpl<Epoch, Width, Height, Width>()();
  putchar('\n');
}

template <std::size_t Epochs, std::size_t Width, std::size_t Height>
struct PrintBoardsImpl {
  void operator()() {
    PrintBoardsImpl<Epochs - 1, Width, Height>()();
    printf("----------\n");
    printBoard<Epochs, Width, Height>();
  }
};

template <std::size_t Width, std::size_t Height>
struct PrintBoardsImpl<0, Width, Height> {
  void operator()() { printBoard<0, Width, Height>(); }
};

template <std::size_t Epochs, std::size_t Width, std::size_t Height>
void printBoards() {
  PrintBoardsImpl<Epochs, Width, Height>()();
}
int main(int argc, char const *argv[]) { printBoards<32, 10, 10>(); }
