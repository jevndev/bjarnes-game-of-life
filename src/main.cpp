#include "board.hpp"

#include <iostream>

char getBlock(const bool value) { return value ? 'x' : ' '; }

template <std::size_t Epoch> void printBoard() {
  std::cout << getBlock(Board<0, 2, Epoch>::isAlive)
            << getBlock(Board<1, 2, Epoch>::isAlive)
            << getBlock(Board<2, 2, Epoch>::isAlive) << "\n"
            << getBlock(Board<0, 1, Epoch>::isAlive)
            << getBlock(Board<1, 1, Epoch>::isAlive)
            << getBlock(Board<2, 1, Epoch>::isAlive) << "\n"
            << getBlock(Board<0, 0, Epoch>::isAlive)
            << getBlock(Board<1, 0, Epoch>::isAlive)
            << getBlock(Board<2, 0, Epoch>::isAlive) << "\n";
}


template <std::size_t Epoch> void printBoards() {
  printBoards<Epoch - 1>();
  printBoard<Epoch>();
}

template <> void printBoards<0>() { printBoard<0>(); }

int main(int argc, char const *argv[]) { printBoards<3>(); }
