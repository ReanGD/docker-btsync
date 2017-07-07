#pragma once
#include <cstdint>
#include <random>


struct Generator {
  // [0; to)
  template<class T> T get(T to) {
    return static_cast<T>(std::uniform_int_distribution<int>(0, static_cast<int>(to)-1)(m_generator));
  }

  // [0; to]
  float getf(float to) {
    return std::uniform_real_distribution<float>(0, to)(m_generator);
  }

private:
  std::mt19937 m_generator = std::mt19937(std::random_device()());
};


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
  Position(uint32_t coord);
  operator size_t() const { return m_coord; }

  void move(Direction direction);
  void turn(Direction direction);

  uint32_t m_coord;
};

struct Mass {
  Mass() = delete;
  Mass(uint32_t value);
  Mass& operator+=(const Mass& other);
  Mass& operator-=(const Mass& other);

  uint16_t m_value;
};
