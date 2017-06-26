#include "scene.h"

#include <QPainter>
#include <QPaintEvent>
#include <QWidget>

Bot::Bot(Position position)
  : m_position(position) {

}

Position Bot::update() {
  m_position.m_x = (m_position.m_x + 1) % 100;

  return m_position;
}

Scene::Scene() {
  for(uint16_t i=0; i!=100; ++i) {
    m_bots.emplace_back(Position{i, i});
  }
}

std::vector<Position> Scene::update() {
  std::vector<Position> result;
  for (Bot& bot: m_bots) {
    result.push_back(bot.update());
  }

  return result;
}
