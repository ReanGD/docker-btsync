#include "scene.h"
#include "settings.h"


Cell::Cell(CellType type, Mass mass)
  : m_type(type)
  , m_mass(mass) {

}

void Cell::move(Cell& to) {
  to.m_type = m_type;
  m_type = CellType::Space;

  to.m_mass += m_mass;
  m_mass = Mass(0);
}

Organism::Organism(Position position, Generator& generator)
  : m_position(position)
  , m_direction(generator.get(Direction::Last))
  , m_network(8, 8, generator) {
}

void Organism::calc(World* word, const std::array<Cell*, static_cast<size_t>(Direction::Last)>& cells) {
  auto inputs = std::shared_ptr<float[]>(new float[static_cast<size_t>(Direction::Last)]);
  size_t i=0;
  for (const auto cell :cells) {
    inputs[i++] = static_cast<float>(cell->m_type) / static_cast<float>(CellType::Last);
  }

  float result = m_network.calc(inputs);
  Direction directionMove;
  if (result < 1.0f/8.0f) {
    directionMove = Direction::Forward;
  } else if (result < 2.0f/8.0f) {
    directionMove = Direction::ForwardRight;
  } else if (result < 3.0f/8.0f) {
    directionMove = Direction::Right;
  } else if (result < 4.0f/8.0f) {
    directionMove = Direction::BackwardRight;
  } else if (result < 5.0f/8.0f) {
    directionMove = Direction::Backward;
  } else if (result < 6.0f/8.0f) {
    directionMove = Direction::BackwardLeft;
  } else if (result < 7.0f/8.0f) {
    directionMove = Direction::Left;
  } else {
    directionMove = Direction::ForwardLeft;
  }

  Position newPosition = m_position;
  newPosition.move(directionMove + m_direction);
  if (word->move(m_position, newPosition)) {
    m_position = newPosition;
  }
}

World::World()
  : m_cells(Settings::m_worldMaxCoord, Cell(CellType::Space, Mass(0))) {

  initOrganisms(500);
  initFoods(500);
}

void World::step() {
  for (auto& organism: m_organisms) {
    Position pos = organism->getPosition();

    Cell barrier(CellType::Barrier, Mass(0));
    std::array<Cell*, static_cast<size_t>(Direction::Last)> cells;
    for(size_t i=0; i!=cells.size(); ++i) {
      Position copyPos = pos;
      copyPos.move(static_cast<Direction>(i));
      if (copyPos == pos) {
        cells[i] = &barrier;
      } else {
        cells[i] = &m_cells[copyPos];
      }
    }
    organism->calc(this, cells);
  }
}

bool World::move(Position from, Position to) {
  if (m_cells[to].m_type == CellType::Space) {
    m_cells[from].move(m_cells[to]);
    m_cells[to].m_mass -= Mass(1);
    return true;
  } else if (m_cells[to].m_type == CellType::Food) {
    m_cells[from].move(m_cells[to]);
    return true;
  }

  return false;
}

Position World::getRandomSpaceCell() const {
  while(true) {
    auto coord = m_random.get(Settings::m_worldMaxCoord);
    if (m_cells[coord].m_type == CellType::Space) {
      return Position(coord);
    }
  }
}

void World::initOrganisms(uint32_t cnt) {
  for(size_t i=0; i!=cnt; ++i) {
    Position coord = getRandomSpaceCell();
    m_organisms.push_front(std::make_unique<Organism>(coord, m_random));
    m_cells[coord] = Cell(CellType::Organism, Mass(20));
  }
}

void World::initFoods(uint32_t cnt) {
  for(size_t i=0; i!=cnt; ++i) {
    Position coord = getRandomSpaceCell();
    m_cells[coord] = Cell(CellType::Food, Mass(20));
  }
}
