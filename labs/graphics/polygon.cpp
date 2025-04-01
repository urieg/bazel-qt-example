#include "polygon.h"

#include <exception>
#include <stdexcept>

Polygon::Polygon(const std::vector<QPoint>& vertices) {
    this->vertices_ = vertices;
}
[[nodiscard]] int Polygon::GetVerticesNumber() const {
    return static_cast<int>(vertices_.size());
}
[[nodiscard]] QPoint Polygon::GetVertex(int index) const {
    if (index >= vertices_.size() || index < 0) {
        throw std::runtime_error{"Polygon getter index out of range"};
    }
    return vertices_[index];
}

[[nodiscard]] QPoint& Polygon::GetVertex(int index) {
    if (index >= vertices_.size() || index < 0) {
        throw std::runtime_error{"Polygon getter index out of range"};
    }
    return vertices_[index];
}

void Polygon::AddVertex(const QPoint& vertex) {
    vertices_.push_back(vertex);
}

void Polygon::UpdateLastVertex(const QPoint& newVertex) {
    if (!vertices_.empty()) {
        vertices_.pop_back();
    }
    AddVertex(newVertex);
}

std::optional<QPoint> IntersectRay(const Ray& ray) {

}
