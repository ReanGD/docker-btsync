#include "scene.h"
#include "settings.h"


Cell::Cell(CellType type)
  : m_type(type) {

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
  : m_cells(Settings::m_worldMaxCoord, Cell(CellType::Space)) {

  const size_t botsCount = 500;
  for(size_t i=0; i!=botsCount; ++i) {
    while(true) {
      auto coord = m_random.get(Settings::m_worldMaxCoord);
      if (m_cells[coord].m_type == CellType::Space) {
        m_organisms.push_front(std::make_unique<Organism>(Position(coord), m_random));
        m_cells[coord].m_type = CellType::Organism;
        break;
      }
    }
  }
}

void World::step() {
  for (auto& organism: m_organisms) {
    Position pos = organism->getPosition();

    Cell barrier(CellType::Barrier);
    std::array<Cell*, static_cast<size_t>(Direction::Last)> cells;
    for(size_t i=0; i!=cells.size(); ++i) {
      Position copyPos = pos;
      copyPos.move(static_cast<Direction>(i));
      if (copyPos.m_coord == pos.m_coord) {
        cells[i] = &barrier;
      } else {
        cells[i] = &m_cells[copyPos.m_coord];
      }
    }
    organism->calc(this, cells);
  }
}

bool World::move(Position from, Position to) {
  if (m_cells[to].m_type == CellType::Space) {
    m_cells[from].m_type = CellType::Space;
    m_cells[to].m_type = CellType::Organism;
    return true;
  }

  return false;
}
