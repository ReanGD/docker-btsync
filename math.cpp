#include "math.h"


Direction operator+(Direction first, Direction second) {
  return static_cast<Direction>((static_cast<uint8_t>(first) + static_cast<uint8_t>(second)) % static_cast<uint8_t>(Direction::Last));
}

Position::Position(uint32_t coord, uint32_t maxCoord, uint16_t lineSize, Direction direction)
  : m_coord(coord % maxCoord)
  , m_maxCoord(maxCoord)
  , m_lineSize(lineSize)
  , m_direction(direction) {
}

void Position::move(Direction direction) {
  Direction absoluteDir = direction + m_direction;
  switch (absoluteDir) {
  case Direction::Forward:
  case Direction::ForwardRight:
  case Direction::ForwardLeft:
    if (m_coord >= m_lineSize) {
      m_coord -= m_lineSize;
    } else {
      return;
    }
    break;
  case Direction::Backward:
  case Direction::BackwardRight:
  case Direction::BackwardLeft:
    m_coord += m_lineSize;
    if (m_coord >= m_maxCoord) {
      m_coord -= m_lineSize;
      return;
    }
    break;
  default:
    break;
  }

  switch (absoluteDir) {
  case Direction::Right:
  case Direction::ForwardRight:
  case Direction::BackwardRight:
    if (++m_coord % m_lineSize == 0) {
      m_coord -= m_lineSize;
    }
    break;
  case Direction::Left:
  case Direction::ForwardLeft:
  case Direction::BackwardLeft:
    if (m_coord % m_lineSize == 0) {
      m_coord += (m_lineSize - 1);
    } else {
      m_coord--;
    }
    break;
  default:
    break;
  }
}

void Position::turn(Direction direction) {
  m_direction = m_direction + direction;
}
