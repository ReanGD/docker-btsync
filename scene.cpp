#include "scene.h"
#include <random>

Generator::Generator()
  : m_generator(m_device()) {
}

uint16_t Generator::next(uint16_t from, uint16_t to) {
  return std::uniform_int_distribution<>(from, to-1)(m_generator);
}

SceneMeta::SceneMeta(uint16_t width, uint16_t height)
  : m_width(width)
  , m_height(height) {

}

Bot::Bot(const std::shared_ptr<SceneMeta>& meta)
  : m_meta(meta)
  , m_position{m_meta->m_generator.next(0, m_meta->m_width), m_meta->m_generator.next(0, m_meta->m_height)} {
}

Position Bot::update() {
  auto dir = m_meta->m_generator.next(0, 4);

  switch (dir) {
  case 0:
    m_position.m_x++;
    break;
  case 1:
    m_position.m_y+=(m_meta->m_height - 1);
    break;
  case 2:
    m_position.m_x+=(m_meta->m_width - 1);
    break;
  case 3:
    m_position.m_y++;
    break;
  }

  m_position.m_x %= m_meta->m_width;
  m_position.m_y %= m_meta->m_height;

  return m_position;
}

Scene::Scene(uint16_t width, uint16_t height)
  : m_meta(std::make_shared<SceneMeta>(width, height)) {

  for(uint16_t i=0; i!=100; ++i) {
    m_bots.emplace_back(m_meta);
  }
}

std::vector<Position> Scene::update() {
  std::vector<Position> result;
  for (Bot& bot: m_bots) {
    result.push_back(bot.update());
  }

  return result;
}
