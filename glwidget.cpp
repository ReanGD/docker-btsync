#include "glwidget.h"
#include "scene.h"
#include <QPaintEvent>
#include <QPainter>


GLWidget::GLWidget(QWidget *parent)
  : QOpenGLWidget(parent)
  , m_scene(std::make_shared<Scene>(WIDTH / BOT_SIZE, HEIGHT / BOT_SIZE)) {

  setFixedSize(WIDTH, HEIGHT);
  setAutoFillBackground(false);
}

void GLWidget::animate() {
  update();
}

void GLWidget::drawScene(QPainter* painter) {
  QPen botPen = QPen(Qt::white);
  painter->setPen(botPen);
  botPen.setWidth(1);

  QBrush botBrush = QBrush(Qt::white);
  painter->setBrush(botBrush);

  QSize botSize = QSize(BOT_SIZE, BOT_SIZE);
  for(Position& pos :m_scene->update()) {
    QPoint topleft(pos.m_x * BOT_SIZE, pos.m_y * BOT_SIZE);
    painter->drawRect(QRect(topleft, botSize));
  }
}

void GLWidget::paintEvent(QPaintEvent *event) {
  QPainter painter;
  painter.begin(this);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.fillRect(event->rect(), QBrush(QColor(0x0, 0x0, 0x0)));
  drawScene(&painter);
  painter.end();
}
