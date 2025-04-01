#ifndef POLYGON_H
#define POLYGON_H

#include "ray.h"

#include <QPoint>
#include <vector>
#include <optional>

class Polygon {
public:
    Polygon() = default;
    Polygon(const std::vector<QPoint>& vertices);
    [[nodiscard]] int GetVerticesNumber() const;
    [[nodiscard]] QPoint GetVertex(int index) const;
    [[nodiscard]] QPoint& GetVertex(int index);
    void AddVertex(const QPoint& vertex);
    void UpdateLastVertex(const QPoint& new_vertex);
    std::optional<QPoint> IntersectRay(const Ray& ray);
private:
    std::vector<QPoint>vertices_;
};

#endif  // POLYGON_H
