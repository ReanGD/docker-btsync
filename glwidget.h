#pragma once
#include <memory>
#include <QOpenGLWidget>

class World;
class GLWidget : public QOpenGLWidget {
    Q_OBJECT
public:
    GLWidget(QWidget *parent);
public slots:
    void animate();
protected:
    void drawScene(QPainter* painter);
    void paintEvent(QPaintEvent *event) override;
private:
    const uint16_t BOT_SIZE_PIXEL = 10;
    const uint16_t MAX_X_PIXEL = 800;
    const uint16_t MAX_Y_PIXEL = 600;
    const uint16_t MAX_X = MAX_X_PIXEL / BOT_SIZE_PIXEL;
    const uint16_t MAX_Y = MAX_Y_PIXEL / BOT_SIZE_PIXEL;
    std::shared_ptr<World> m_world;
};
