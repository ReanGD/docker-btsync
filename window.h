#pragma once

#include <chrono>
#include <QWidget>

class QLabel;
class GLWidget;
class Window : public QWidget {
    Q_OBJECT
public:
    Window();
private slots:
    void step();
private:
    GLWidget *m_glWidget;
    QLabel *m_topInfo;
    QLabel *m_bottomInfo;

    uint32_t m_step = 0;
    float m_sps = 0.0f;
    std::chrono::steady_clock::time_point m_start;
};
