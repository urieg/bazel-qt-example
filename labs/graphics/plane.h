#ifndef PLANE_H
#define PLANE_H

#include "controller.h"

#include <QWidget>
#include <QImage>
#include <QPoint>

class Plane : public QWidget{
public:
    Plane(QWidget *parent = nullptr);
    ~Plane();
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void leaveEvent(QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
private:
    enum class Mode {Light, Polygons};
    Mode mode_ = Mode::Light;
    bool drawing_ = false;
    QPoint cursor_pos_;
    bool cursor_visible_ = true;
    Controller controller_;
};

#endif  // PLANE_H
