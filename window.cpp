#include "glwidget.h"
#include "window.h"

#include <QGridLayout>
#include <QTimer>
#include <QLabel>

Window::Window() {
  setWindowTitle(tr("Evolution"));

  QGridLayout *layout = new QGridLayout;

  GLWidget *openGL = new GLWidget(this);
  layout->addWidget(openGL, 1, 0);

  setLayout(layout);

  QTimer *timer = new QTimer(this);
  connect(timer, &QTimer::timeout, openGL, &GLWidget::animate);
  timer->start(50);
}
