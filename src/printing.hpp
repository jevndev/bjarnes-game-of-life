#pragma once

#include "board.hpp"

#include <cstddef>
#include <utility>

template <bool b> struct getBlockChar;

template <> struct getBlockChar<true> {
  static constexpr char C = '#'; // Unicode full block character
};

template <> struct getBlockChar<false> {
  static constexpr char C = ' '; // Unicode light shade character
};

template <std::size_t Epoch, std::size_t I, std::size_t J, std::size_t Width>
struct getChar {
  static constexpr char C = getBlockChar<Board<I, J, Epoch>::isAlive>::C;
};

template <std::size_t Epoch, std::size_t J, std::size_t Width>
struct getChar<Epoch, Width, J, Width> {
  static constexpr char C = '\n';
};
template <std::size_t Epoch, std::size_t Width, typename T, typename U>
struct GetRow;

template <std::size_t Epoch, std::size_t Width, std::size_t... Is,
          std::size_t... Js>
struct GetRow<Epoch, Width, std::index_sequence<Is...>,
              std::index_sequence<Js...>> {
  static constexpr char row[] = {
      getBlockChar<Board<Is, Js, Epoch>::isAlive>::C...};
};

template <std::size_t Epoch, std::size_t Width, std::size_t Height>
struct GetBoard {
  static constexpr auto board =
      GetRow<Epoch, Width, std::make_index_sequence<Width>,
             std::make_index_sequence<Height>>::row;
};
