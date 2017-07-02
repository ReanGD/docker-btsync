#pragma once
#include <cstdint>

enum class Direction : uint8_t {
  Forward = 0u,
  ForwardRight,
  Right,
  BackwardRight,
  Backward,
  BackwardLeft,
  Left,
  ForwardLeft,
  Last
};

Direction operator+(Direction first, Direction second);

struct Position {
  Position() = delete;
  Position(uint32_t coord, Direction direction);

  void move(Direction direction);
  void turn(Direction direction);

  uint32_t m_coord;
  Direction m_direction;
};
