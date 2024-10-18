#pragma once

#include <cstddef>
#include <type_traits>

template <std::size_t I, std::size_t J, std::size_t N = 0> struct Board;

template <std::size_t I, std::size_t J, std::size_t N> struct GetNeighborCount {
  static constexpr auto neighborCount =
      static_cast<std::size_t>(Board<I - 1, J - 1, N>::isAlive) +
      static_cast<std::size_t>(Board<I - 1, J + 1, N>::isAlive) +
      static_cast<std::size_t>(Board<I - 1, J, N>::isAlive) +
      static_cast<std::size_t>(Board<I + 1, J - 1, N>::isAlive) +
      static_cast<std::size_t>(Board<I + 1, J + 1, N>::isAlive) +
      static_cast<std::size_t>(Board<I + 1, J, N>::isAlive) +
      static_cast<std::size_t>(Board<I, J - 1, N>::isAlive) +
      static_cast<std::size_t>(Board<I, J + 1, N>::isAlive);
};
// dead rule
template <std::size_t I, std::size_t J, std::size_t N, bool isAlive>
struct ShouldLiveImpl {
  static constexpr auto neighborCount =
      GetNeighborCount<I, J, N>::neighborCount;
  static constexpr auto value = (neighborCount == 3);
};

// live rule
template <std::size_t I, std::size_t J, std::size_t N>
struct ShouldLiveImpl<I, J, N, true> {
  static constexpr auto neighborCount =
      GetNeighborCount<I, J, N>::neighborCount;
  static constexpr auto value = (neighborCount == 2 || neighborCount == 3);
};

template <std::size_t I, std::size_t J, std::size_t N, bool isAlive>
using ShouldLive = ShouldLiveImpl<I, J, N, isAlive>;

template <std::size_t I, std::size_t J, std::size_t N> struct Board {
  static constexpr auto isAlive =
      ShouldLive<I, J, N - 1, Board<I, J, N - 1>::isAlive>::value;
};

template <std::size_t I, std::size_t J> struct Board<I, J, 0> {
  static constexpr auto isAlive = false;
};

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
