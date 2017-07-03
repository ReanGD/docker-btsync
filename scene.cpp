#include "scene.h"
#include "settings.h"


Cell::Cell(CellType type)
  : m_type(type) {

}

Organism::Organism(Position position, FGenerator& generator)
  : m_position(position)
  , m_network(8, 8, generator) {
}

CommandCode Organism::calc(const std::array<Cell*, static_cast<size_t>(Direction::Last)>& cells) {
  auto inputs = std::shared_ptr<float[]>(new float[static_cast<size_t>(Direction::Last)]);
  size_t i=0;
  for (const auto cell :cells) {
    inputs[i++] = static_cast<float>(cell->m_type) / static_cast<float>(CellType::Last);
  }

  float result = m_network.calc(inputs);
  if (result < 1.0f/8.0f) {
    return CommandCode::MoveForward;
  }
  if (result < 2.0f/8.0f) {
    return CommandCode::MoveForwardRight;
  }
  if (result < 3.0f/8.0f) {
    return CommandCode::MoveRight;
  }
  if (result < 4.0f/8.0f) {
    return CommandCode::MoveBackwardRight;
  }
  if (result < 5.0f/8.0f) {
    return CommandCode::MoveBackward;
  }
  if (result < 6.0f/8.0f) {
    return CommandCode::MoveBackwardLeft;
  }
  if (result < 7.0f/8.0f) {
    return CommandCode::MoveLeft;
  }
  return CommandCode::MoveForwardLeft;
}

World::World()
  : m_cells(Settings::m_worldMaxCoord, Cell(CellType::Space)) {

  FGenerator generator;
  const size_t botsCount = 500;
  for(size_t i=0; i!=botsCount; ++i) {
    Direction direction(m_random.get(Direction::Last));
    while(true) {
      auto coord = m_random.get(Settings::m_worldMaxCoord);
      if (m_cells[coord].m_type == CellType::Space) {
        m_organisms.push_front(std::make_unique<Organism>(Position(coord, direction), generator));
        m_cells[coord].m_type = CellType::Organism;
        break;
      }
    }
  }
}

void World::step() {
  for (auto& organism: m_organisms) {
    Position pos = organism->m_position;

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
    CommandCode code = organism->calc(cells);
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
}
