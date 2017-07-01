#include "scene.h"

void Position::move(Direction direction, uint32_t lineSize, uint32_t maxPos) {
  switch (direction) {
  case Direction::Up:
    if (m_value >= lineSize) {
      m_value -= lineSize;
    }
    break;
  case Direction::Right:
    if (++m_value % lineSize == 0) {
      m_value -= lineSize;
    }
    break;
  case Direction::Down:
    m_value += lineSize;
    if (m_value >= maxPos) {
      m_value -= lineSize;
    }
    break;
  case Direction::Left:
    if (m_value > 0) {
      if (m_value % lineSize == 0) {
        m_value += (lineSize - 1);
      } else {
        m_value--;
      }
    }
    break;
  default:
    break;
  }
}

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

World::World(uint32_t maxX, uint32_t maxY)
  : m_maxX(maxX)
  , m_maxY(maxY)
  , m_cells(maxX * maxY, Cell(CellType::Space)) {

  const size_t botsCount = 100;
  const uint32_t maxPosition = maxX * maxY;
  for(size_t i=0; i!=botsCount; ++i) {
    while(true) {
      uint32_t pos = m_random.get(maxPosition);
      if (m_cells[pos].m_type == CellType::Space) {
        m_organisms.push_front(std::make_unique<Organism>(m_random, Position{pos}));
        m_cells[pos].m_type = CellType::Organism;
        break;
      }
    }
  }
}

const std::vector<Cell>& World::step() {
  const uint32_t maxPos = m_maxX * m_maxY;
  for (auto& organism: m_organisms) {
    Position pos = organism->m_position;
    CommandCode code = organism->next();
    switch (code) {
    case CommandCode::MoveUp:
      pos.move(Direction::Up, m_maxX, maxPos);
      break;
    case CommandCode::MoveRight:
      pos.move(Direction::Right, m_maxX, maxPos);
      break;
    case CommandCode::MoveDown:
      pos.move(Direction::Down, m_maxX, maxPos);
      break;
    case CommandCode::MoveLeft:
      pos.move(Direction::Left, m_maxX, maxPos);
      break;
    default:
      break;
    }
    if (m_cells[pos.m_value].m_type == CellType::Space) {
      m_cells[organism->m_position.m_value].m_type = CellType::Space;
      m_cells[pos.m_value].m_type = CellType::Organism;
      organism->m_position = pos;
    }
  }

  return m_cells;
}

