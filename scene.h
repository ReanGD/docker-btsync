#pragma once
#include <cstdint>
#include <vector>


struct Position {
  uint16_t m_x;
  uint16_t m_y;
};

class Bot {
public:
  Bot() = delete;
  Bot(Position position);

  Position update();
private:
  Position m_position;
};

class Scene {
public:
  Scene();

  std::vector<Position> update();
private:
  std::vector<Bot> m_bots;
};
