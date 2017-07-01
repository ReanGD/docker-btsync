#include "window.h"
#include "glwidget.h"

#include <QTimer>
#include <QLabel>
#include <QGridLayout>

Window::Window() {
  setWindowTitle(tr("Evolution"));

  QGridLayout *layout = new QGridLayout;

  m_topInfo = new QLabel(this);
  m_topInfo->setAlignment(Qt::AlignBottom | Qt::AlignLeft);
  layout->addWidget(m_topInfo, 0, 0);

  m_glWidget = new GLWidget(this);
  layout->addWidget(m_glWidget, 1, 0);

  m_bottomInfo = new QLabel(this);
  layout->addWidget(m_bottomInfo, 2, 0);

  setLayout(layout);

  m_start = std::chrono::steady_clock::now();
  QTimer::singleShot(10, this, &Window::step);
}

void Window::step() {
  const uint32_t updatePerStep = 20;
  if (m_step % updatePerStep == 0) {
    auto now = std::chrono::steady_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now - m_start).count();
    m_sps = (updatePerStep * 1000.0f / static_cast<float>(ms));
    m_start = now;
    m_topInfo->setText("Step: " + QString::number(m_step) + " (" + QString::number(m_sps, 'f', 2) + " step/sec)");
  }

  m_glWidget->step();
  m_step++;
  QTimer::singleShot(10, this, &Window::step);
}
