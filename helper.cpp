#include "helper.h"

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

Helper::Helper() {
  m_botBrush = QBrush(Qt::white);
  m_botPen = QPen(Qt::white);
  m_botPen.setWidth(1);
}

void Helper::paint(QPainter *painter, const QRect& rect) {
  painter->fillRect(rect, m_background);
  painter->save();
  painter->setBrush(m_botBrush);
  painter->setPen(m_botPen);

  QSize botSize = QSize(5, 5);
  for(Position& pos :m_scene.update()) {
    QPoint topleft(pos.m_x * 5, pos.m_y * 5);
    painter->drawRect(QRect(topleft, botSize));
  }

  painter->restore();
}
