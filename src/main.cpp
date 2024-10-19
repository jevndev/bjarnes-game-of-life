#include "board.hpp"

#include <cstdio>

// Board definition

template <> struct Board<0, 1, 0> {
  static constexpr auto isAlive = true;
};

template <> struct Board<1, 1, 0> {
  static constexpr auto isAlive = true;
};

template <> struct Board<2, 1, 0> {
  static constexpr auto isAlive = true;
};

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

int main(int argc, char const *argv[]) { printBoard<0, 2, 2>(); }
