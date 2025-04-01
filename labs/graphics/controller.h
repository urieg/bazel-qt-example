#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "polygon.h"

#include <vector>

class Controller {
public:
    Controller();
    [[nodiscard]] const std::vector<Polygon>& GetPolygons();
    void AddPolygon(const Polygon&);
    void AddPolygon();
    void AddVertexToLastPolygon(const QPoint& new_vertex);
    void UpdateLastPolygon(const QPoint& new_vertex);
private:
    std::vector<Polygon> polygons_;
};

#endif  // CONTROLLER_H
