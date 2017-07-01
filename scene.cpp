#include "scene.h"


Cell::Cell(CellType type)
  : m_type(type) {

}

Organism::Organism(Generator& random, Position position)
  : m_position(position) {
  for(CommandCode& code: m_genome) {
    code = random.get(CommandCode::Last);
  }
}

CommandCode Organism::next() {
  m_commandPos %= m_genome.size();
  return m_genome[m_commandPos++];
}

World::World(uint16_t maxX, uint16_t maxY)
  : m_maxX(maxX)
  , m_maxY(maxY)
  , m_cells(maxX * maxY, Cell(CellType::Space)) {

  const size_t botsCount = 100;
  const uint32_t maxCoord = maxX * maxY;
  for(size_t i=0; i!=botsCount; ++i) {
    Direction direction(m_random.get(Direction::Last));
    while(true) {
      uint32_t coord = m_random.get(maxCoord);
      if (m_cells[coord].m_type == CellType::Space) {
        m_organisms.push_front(std::make_unique<Organism>(m_random, Position(coord, maxCoord, maxX, direction)));
        m_cells[coord].m_type = CellType::Organism;
        break;
      }
    }
  }
}

const std::vector<Cell>& World::step() {
  for (auto& organism: m_organisms) {
    Position pos = organism->m_position;
    CommandCode code = organism->next();
    switch (code) {
    case CommandCode::MoveForward:
      pos.move(Direction::Forward);
      break;
    case CommandCode::MoveForwardRight:
      pos.move(Direction::ForwardRight);
      break;
    case CommandCode::MoveRight:
      pos.move(Direction::Right);
      break;
    case CommandCode::MoveBackwardRight:
      pos.move(Direction::BackwardRight);
      break;
    case CommandCode::MoveBackward:
      pos.move(Direction::Backward);
      break;
    case CommandCode::MoveBackwardLeft:
      pos.move(Direction::BackwardLeft);
      break;
    case CommandCode::MoveLeft:
      pos.move(Direction::Left);
      break;
    case CommandCode::MoveForwardLeft:
      pos.move(Direction::ForwardLeft);
      break;
    default:
      break;
    }
    if (m_cells[pos.m_coord].m_type == CellType::Space) {
      m_cells[organism->m_position.m_coord].m_type = CellType::Space;
      m_cells[pos.m_coord].m_type = CellType::Organism;
      organism->m_position = pos;
    }
  }

  return m_cells;
}
