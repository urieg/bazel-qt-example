#include "plane.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QWidget>
#include <QKeyEvent>


Plane::Plane(QWidget *parent) : QWidget(parent) {
    controller_.SetLightSource(QPointF(1, 1));
    setMouseTracking(true);
    setFocusPolicy(Qt::StrongFocus);
}

Plane::~Plane() {
}

void Plane::mousePressEvent(QMouseEvent *event) {
    controller_.SetLightSource(event->pos());
    if (controller_.GetMode() == Controller::Mode::Polygons) {
        if (event->button() == Qt::LeftButton) {
            if (!controller_.IsDrawing()) {
                controller_.SetDrawing(true);
                controller_.AddPolygon(Polygon());
            }
            controller_.AddVertexToLastPolygon(event->pos());
        } else {
            controller_.SetDrawing(false);
        }
    }
    update();
}

void Plane::mouseMoveEvent(QMouseEvent *event) {
    controller_.SetLightSource(event->pos());
    if (controller_.GetMode() == Controller::Mode::Light) {
        controller_.SetLightSourceVisibility(true);
        update();
    }
}

void Plane::leaveEvent(QEvent *event) {
    controller_.SetLightSource(QPointF(-1, -1));
    if (controller_.GetMode() == Controller::Mode::Light) {
        controller_.SetLightSourceVisibility(false);
        update();
    }
}

void Plane::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    //painter.fillRect(rect(), Qt::white);
    painter.setPen(QPen(Qt::black, 2));
    painter.setBrush(QColor(0, 0, 0, 100));

    QPointF prev_vertex;
    for (const auto& polygon : controller_.GetPolygons()) {
        const int sz = polygon.GetVerticesNumber();
        for (int i = 0; i <= sz; i++) {
            auto vertex = polygon.GetVertex(i % sz);
            //painter.drawEllipse(vertex, 5, 5);
            if (i) {
                painter.drawLine(prev_vertex, vertex);
            }
            prev_vertex = vertex;
        }
    }



    if (controller_.IsLightSourceVisible()) {
        painter.setPen(QPen(Qt::red, 2));
        painter.setBrush(QColor(255, 0, 0, 100));
        painter.drawEllipse(controller_.GetLightSource(), 5, 5);

        painter.setPen(QPen(Qt::red, 1));
        const auto rays = controller_.CastRays();
        for (const auto& ray : rays) {
            painter.drawLine(ray.Begin(), ray.End());
        }
    }
}

void Plane::keyPressEvent(QKeyEvent *event) {

    switch(event->key()) {
        case Qt::Key_L:
            if (controller_.GetMode() != Controller::Mode::Light) {
                controller_.SetMode(Controller::Mode::Light);
                controller_.SetDrawing(false);
                controller_.SetLightSourceVisibility(true);
                update();
            }
            break;
        case Qt::Key_P:
            if (controller_.GetMode() != Controller::Mode::Polygons) {
                controller_.SetMode(Controller::Mode::Polygons);
                controller_.SetLightSourceVisibility(false);
                update();
            }
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}
