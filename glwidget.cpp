#include "glwidget.h"
#include <QPaintEvent>
#include <QPainter>
#include "settings.h"
#include "scene.h"


GLWidget::GLWidget(QWidget *parent, std::shared_ptr<World> world)
  : QOpenGLWidget(parent)
  , m_world(world) {

  setFixedSize(Settings::m_worldMaxXPixel, Settings::m_worldMaxYPixel);
  setAutoFillBackground(false);
  m_start = std::chrono::steady_clock::now();
}

void GLWidget::drawScene(QPainter* painter) {
  static const size_t cellTypes = static_cast<size_t>(CellType::Last);
  static const QColor colors[cellTypes] = {Qt::red, Qt::green, Qt::blue, Qt::gray};
  static const QSize botSize = QSize(Settings::m_botSizePixel, Settings::m_botSizePixel);

  painter->setPen(Qt::NoPen);

  int pos = 0;
  for(const Cell& cell :m_world->cells()) {
    int x = pos % Settings::m_worldMaxX;
    int y = (pos - x) / Settings::m_worldMaxX;
    pos++;
    QPoint topleft(x * Settings::m_botSizePixel, y * Settings::m_botSizePixel);

    QColor color = colors[static_cast<size_t>(cell.m_type)];
    QBrush brush = QBrush(color);
    painter->setBrush(brush);

    painter->drawRect(QRect(topleft, botSize));
  }
}

void GLWidget::paintEvent(QPaintEvent *event) {
  const uint32_t calcPerDraw = 10;

  if (m_step % calcPerDraw == 0) {
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start).count();
    m_fps = (calcPerDraw * 1000.0f / static_cast<float>(ms));
    m_start = now;
  }
  m_step++;

  QPainter painter;
  painter.begin(this);
  painter.fillRect(event->rect(), QBrush(Qt::black));
  drawScene(&painter);
  painter.end();
}
