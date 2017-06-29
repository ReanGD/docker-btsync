#pragma once
#include <cstdint>
#include <vector>
#include <random>
#include <memory>


class Generator {
public:
  Generator();

  // [0; to)
  template<class T> T get(T to) {
    return static_cast<T>(std::uniform_int_distribution<int>(0, static_cast<uint16_t>(to)-1)(m_generator));
  }
private:
  std::mt19937 m_generator;
};

struct Position {
  uint16_t m_value;
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

class World {
public:
  World() = delete;
  World(uint16_t maxX, uint16_t maxY);
public:
//  Cell& get(Position pos);
  const std::vector<Cell>& step();
private:
  uint16_t m_maxX;
  uint16_t m_maxY;
  Generator m_random;
  std::vector<Cell> m_cells;
};

//enum class CommandType : uint8_t {
//  MoveUp,
//  MoveRight,
//  MoveDown,
//  MoveLeft,
//  Last
//};

//class Organism {
//public:
//  Organism();

//  void step(World& world, Cell& current);
//private:
//  std::array<CommandType> m_genome;
//};
