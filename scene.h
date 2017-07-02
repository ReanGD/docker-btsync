#pragma once
#include <random>
#include <memory>
#include <vector>
#include <forward_list>
#include "math.h"


struct Generator {
  // [0; to)
  template<class T> T get(T to) {
    return static_cast<T>(std::uniform_int_distribution<int>(0, static_cast<uint16_t>(to)-1)(m_generator));
  }
private:
  std::mt19937 m_generator = std::mt19937(std::random_device()());
};

//struct Mass {
//  void add(Mass other);

//  uint16_t m_value;
//};

enum class CellType : uint8_t {
  Organism,
//  Food,
  Space,
  Barrier,
  Last
};

struct Cell {
  Cell() = delete;
  Cell(CellType type);

  CellType m_type;
//  Mass m_mass;
};

enum class CommandCode : uint8_t {
  MoveForward = 0u,
  MoveForwardRight,
  MoveRight,
  MoveBackwardRight,
  MoveBackward,
  MoveBackwardLeft,
  MoveLeft,
  MoveForwardLeft,
  Last
};

struct Organism {
  Organism() = delete;
  Organism(Generator& random, Position position);

  CommandCode next();

  Position m_position;
private:
  std::array<CommandCode, 64> m_genome;
  uint8_t m_commandPos = 0;
};

class World {
public:
  World();
public:
  void step();
  const std::vector<Cell>& cells() { return m_cells; }
private:
  Generator m_random;
  std::vector<Cell> m_cells;
  std::forward_list<std::unique_ptr<Organism>> m_organisms;
};
