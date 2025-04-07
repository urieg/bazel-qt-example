#include "controller.h"
#include <QDebug>

Controller::Controller() {
}

/// polygons ------------------------------------------------------------------

const std::vector<Polygon>& Controller::GetPolygons() {
    return polygons_;
}

void Controller::AddPolygon(const Polygon& new_polygon) {
    polygons_.push_back(new_polygon);
}

void Controller::AddPolygon() {
    polygons_.push_back(Polygon());
}

void Controller::AddVertexToLastPolygon(const QPointF& new_vertex) {
    if (polygons_.empty()) {
        return;
    }
    polygons_.back().AddVertex(new_vertex);
}

void Controller::UpdateLastPolygon(const QPointF& new_vertex) {
    if (polygons_.empty()) {
        return;
    }
    polygons_.back().UpdateLastVertex(new_vertex);
}

/// light source -----------------------------------------------------

void Controller::SetLightSource(QPointF new_pos) {
    light_source_ = new_pos;
}

[[nodiscard]]QPointF Controller::GetLightSource() const {
    return light_source_;
}

void Controller::SetLightSourceVisibility(bool state) {
    light_source_visibility_ = state;
}

bool Controller::IsLightSourceVisible() const {
    return light_source_visibility_;
}

void Controller::SetMode(Controller::Mode new_mode) {
    mode_ = new_mode;
}

[[nodiscard]]Controller::Mode Controller::GetMode() const {
    return mode_;
}

void Controller::SetDrawing(bool new_state) {
    is_drawing_polygons = new_state;
}

bool Controller::IsDrawing() const {
    return is_drawing_polygons;
}

/// rays ---------------------------------------------------------------


std::vector<Ray> Controller::CastRays() {
    std::vector<Ray> rays;
    for (const auto& polygon : polygons_) {
        for(int i = 0; i < polygon.GetVerticesNumber(); i++) {
            auto vertex = polygon.GetVertex(i);
            Ray ray(light_source_, vertex);
            //qDebug();
            //qDebug() << "Ray is to vertex " << i << ' ' << vertex.x() << ' ' << vertex.y();
            for (const auto& polygon2 : polygons_) {
                auto new_end = polygon2.IntersectRay(ray);
                if (new_end != std::nullopt) {
                    ray.SetEnd(new_end.value());
                }
            }
            rays.push_back(ray);
        }
    }
    return rays;
}
