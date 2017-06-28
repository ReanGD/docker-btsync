#pragma once
#include <cstdint>
#include <vector>
#include <random>
#include <memory>


class Generator {
public:
  Generator();
  // [from; to)
  uint16_t next(uint16_t from, uint16_t to);
private:
  std::random_device m_device;
  std::mt19937 m_generator;
};

struct Position {
  uint16_t m_x;
  uint16_t m_y;
};

struct SceneMeta {
  SceneMeta(uint16_t width, uint16_t height);

  uint16_t m_width; // x
  uint16_t m_height; // y
  Generator m_generator;
};

class Bot {
public:
  Bot() = delete;
  Bot(const std::shared_ptr<SceneMeta>& meta);

  Position update();
private:
  std::shared_ptr<SceneMeta> m_meta;
  Position m_position;
};

class Scene {
public:
  Scene() = delete;
  Scene(uint16_t width, uint16_t height);

  std::vector<Position> update();
private:
  std::shared_ptr<SceneMeta> m_meta;
  std::vector<Bot> m_bots;
};
