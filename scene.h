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

class World;
struct Organism {
  Organism() = delete;
  Organism(Position position, Generator& generator);

  void calc(World* word, const std::array<Cell*, static_cast<size_t>(Direction::Last)>& cells);
  Position getPosition() const { return m_position; }
private:
  Position m_position;
  Direction m_direction;
  NeuralNetwork m_network;
};

class World {
public:
  World();
public:
  void step();
  bool move(Position from, Position to);
  const std::vector<Cell>& cells() { return m_cells; }
private:
  Generator m_random;
  std::vector<Cell> m_cells;
  std::forward_list<std::unique_ptr<Organism>> m_organisms;
};
