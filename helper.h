#pragma once

#include <QPen>
#include <QBrush>
#include <QWidget>

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

class Helper {
public:
    Helper();

    void paint(QPainter *painter, const QRect& rect);
private:
    Scene m_scene;
    QBrush m_background = QBrush(QColor(0x0, 0x0, 0x0));
    QPen m_botPen;
    QBrush m_botBrush;
};
