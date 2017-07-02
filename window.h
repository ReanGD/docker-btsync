#pragma once

#include <chrono>
#include <memory>
#include <QWidget>

class World;
class QLabel;
class GLWidget;

class Window : public QWidget {
    Q_OBJECT
public:
    Window();
private slots:
    void step();
private:
    std::shared_ptr<World> m_world;
    GLWidget *m_glWidget;
    QLabel *m_topInfo;
    QLabel *m_bottomInfo;

    uint32_t m_step = 0;
    std::chrono::steady_clock::time_point m_start;
};
