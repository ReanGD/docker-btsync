#include "math.h"
#include "settings.h"


Direction operator+(Direction first, Direction second) {
  return static_cast<Direction>((static_cast<uint8_t>(first) + static_cast<uint8_t>(second)) % static_cast<uint8_t>(Direction::Last));
}

Position::Position(uint32_t coord, Direction direction)
  : m_coord(coord % Settings::m_worldMaxCoord)
  , m_direction(direction) {
}

void Position::move(Direction direction) {
  static const uint16_t lineSize = Settings::m_worldMaxX;
  static const uint32_t maxCoord = Settings::m_worldMaxCoord;

  Direction absoluteDir = direction + m_direction;

  switch (absoluteDir) {
  case Direction::Forward:
  case Direction::ForwardRight:
  case Direction::ForwardLeft:
    if (m_coord >= lineSize) {
      m_coord -= lineSize;
    } else {
      return;
    }
    break;
  case Direction::Backward:
  case Direction::BackwardRight:
  case Direction::BackwardLeft:
    m_coord += lineSize;
    if (m_coord >= maxCoord) {
      m_coord -= lineSize;
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
    if (++m_coord % lineSize == 0) {
      m_coord -= lineSize;
    }
    break;
  case Direction::Left:
  case Direction::ForwardLeft:
  case Direction::BackwardLeft:
    if (m_coord % lineSize == 0) {
      m_coord += (lineSize - 1);
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
