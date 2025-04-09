#include "plane.h"

#include <QMouseEvent>
#include <QDebug>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QEvent>
#include <QWidget>
#include <QKeyEvent>
#include <QRadialGradient>


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
    painter.fillRect(rect(), QColor(0, 0, 10));
    painter.setPen(
        controller_.IsPolygonVisible()
        ? QPen(controller_.PolygonBorderColor(), 1)
        : QPen(Qt::NoPen)
    );
    painter.setBrush(QColor(0, 0, 10));

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
        painter.setPen(QPen(Qt::white, 2));
        painter.setBrush(Qt::white);
        //painter.setBrush(QColor(255, 0, 0, 100));
        painter.drawEllipse(controller_.GetLightSource(), 5, 5);

        painter.setPen(Qt::NoPen);
        painter.setBrush(controller_.LightSourceColor());

        QPointF old_pos_of_light_source = controller_.GetLightSource();
        for (int i = 1; i <= controller_.Ls_cnt(); i++) {
            double alpha = 2*acos(-1)/controller_.Ls_cnt()*i;
            controller_.SetLightSource(
                QPointF(old_pos_of_light_source.x() + controller_.Radius()*cos(alpha),
                        old_pos_of_light_source.y() + controller_.Radius()*sin(alpha)
                        )
                );
            auto rays = controller_.CastRays();
            controller_.IntersectRays(&rays);
            controller_.SortRaysByAngle(&rays);
            auto light_area = controller_.CreateLightArea(&rays);

            // qreal dist = 500;
            // QRadialGradient gradient(controller_.GetLightSource(), dist);
            // gradient.setColorAt(0.0, light_color_);
            // gradient.setColorAt(1.0, bg_color_);
            // painter.setBrush(gradient);

            painter.drawPolygon(light_area.Data(), light_area.GetVerticesNumber());
        }
        controller_.SetLightSource(old_pos_of_light_source);
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
                controller_.SetPolygonVisibility(true);
                controller_.SetMode(Controller::Mode::Polygons);
                controller_.SetLightSourceVisibility(false);
                update();
            }
            break;
        case Qt::Key_C:
            controller_.ClearPlate();
            controller_.SetDrawing(false);
            update();
            break;
        case Qt::Key_B:
            if (controller_.GetMode() == Controller::Mode::Light) {
                controller_.SetPolygonVisibility(
                    1 - controller_.IsPolygonVisible());
                update();
            }
            break;
        default:
            QWidget::keyPressEvent(event);
    }
}
