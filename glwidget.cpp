#include "glwidget.h"
#include "scene.h"
#include <QPaintEvent>
#include <QPainter>


GLWidget::GLWidget(QWidget *parent)
  : QOpenGLWidget(parent)
  , m_scene(std::make_shared<Scene>()) {

  setFixedSize(800, 600);
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

  QSize botSize = QSize(5, 5);
  for(Position& pos :m_scene->update()) {
    QPoint topleft(pos.m_x * 5, pos.m_y * 5);
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
