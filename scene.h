#pragma once
#include <memory>
#include <vector>
#include <forward_list>
#include "math.h"
#include "NeuralNetwork.h"


enum class CellType : uint8_t {
  Organism,
  Food,
  Space,
  Barrier,
  Last
};

struct Cell {
  Cell() = delete;
  Cell(CellType type, Mass mass);

  void move(Cell& from);

  CellType m_type;
  Mass m_mass;
};

class World;
struct Organism {
  Organism() = delete;
  Organism(Position position, Generator& generator);

  void cloneFrom(Organism* parent, Position position, Generator& generator);
  void calc(World* word, Cell& currentCell, const std::array<Cell*, static_cast<size_t>(Direction::Last)>& cells);
  Position getPosition() const { return m_position; }
  Direction getDirection() const { return m_direction; }
  bool isDied() const { return m_died; }
private:
  bool m_died;
  Position m_position;
  Direction m_direction;
  NeuralNetwork m_network;
};

class World {
public:
  World();
public:
  void addFood();
  void step();

  const std::vector<Cell>& cells() { return m_cells; }
  Cell& getCell(Position pos) { return m_cells[pos]; }
  uint32_t getGenerationStepLife() const { return m_lastGenerationLife; }
  uint32_t getGeneration() const { return m_generation; }
private:
  Position getRandomSpaceCell() const;
  void initOrganisms(uint32_t cnt);
  void reinitOrganisms();
private:
  mutable Generator m_random;
  uint32_t m_currentGenerationLife = 0;
  uint32_t m_lastGenerationLife = 0;
  uint32_t m_generation = 0;
  uint32_t m_cntOrganisms;
  std::vector<Cell> m_cells;
  std::forward_list<std::unique_ptr<Organism>> m_organisms;
};
