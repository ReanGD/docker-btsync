#include "scene.h"
#include <random>

Generator::Generator()
  : m_generator(std::random_device()()) {
}

Cell::Cell(CellType type)
  : m_type(type) {

}

World::World(uint16_t maxX, uint16_t maxY)
  : m_maxX(maxX)
  , m_maxY(maxY) {

  for(uint16_t i=0; i!=m_maxX * m_maxY; ++i) {
    m_cells.push_back(Cell(m_random.get(CellType::Last)));
  }
}

const std::vector<Cell>& World::step() {
  return m_cells;
}
