#pragma once
#include <memory>
#include <vector>
#include <forward_list>
#include "math.h"
#include "NeuralNetwork.h"


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
  Organism(Position position, Generator& generator);

  CommandCode calc(const std::array<Cell*, static_cast<size_t>(Direction::Last)>& cells);

  Position m_position;
private:
  NeuralNetwork m_network;
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
