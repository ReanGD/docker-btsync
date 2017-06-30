#include "glwidget.h"
#include "scene.h"
#include <QPaintEvent>
#include <QPainter>


GLWidget::GLWidget(QWidget *parent)
  : QOpenGLWidget(parent)
  , m_world(std::make_shared<World>(MAX_X, MAX_Y)) {

  setFixedSize(MAX_X_PIXEL, MAX_Y_PIXEL);
  setAutoFillBackground(false);
}

void GLWidget::step() {
  update();
}

void GLWidget::drawScene(QPainter* painter) {
  static const size_t cellTypes = static_cast<size_t>(CellType::Last);
  static const QColor colors[cellTypes] = {Qt::red, Qt::blue, Qt::gray};
  static const QSize botSize = QSize(BOT_SIZE_PIXEL, BOT_SIZE_PIXEL);

  painter->setPen(Qt::NoPen);

  int pos = 0;
  for(const Cell& cell :m_world->step()) {
    int x = pos % MAX_X;
    int y = (pos - x) / MAX_X;
    pos++;
    QPoint topleft(x * BOT_SIZE_PIXEL, y * BOT_SIZE_PIXEL);

    QColor color = colors[static_cast<size_t>(cell.m_type)];
    QBrush brush = QBrush(color);
    painter->setBrush(brush);

    painter->drawRect(QRect(topleft, botSize));
  }
}

void GLWidget::paintEvent(QPaintEvent *event) {
  QPainter painter;
  painter.begin(this);
  painter.fillRect(event->rect(), QBrush(Qt::black));
  drawScene(&painter);
  painter.end();
}
