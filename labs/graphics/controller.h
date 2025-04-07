#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "polygon.h"

#include <vector>

class Controller {
public:
    enum class Mode {Light, Polygons};
    Controller();

    /// polygons
    [[nodiscard]] const std::vector<Polygon>& GetPolygons();
    void AddPolygon(const Polygon&);
    void AddPolygon();
    void AddVertexToLastPolygon(const QPointF& new_vertex);
    void UpdateLastPolygon(const QPointF& new_vertex);

    /// light source
    void SetLightSource(QPointF new_pos);
    [[nodiscard]]QPointF GetLightSource() const;
    void SetLightSourceVisibility(bool new_state);
    bool IsLightSourceVisible() const;
    void SetMode(Mode new_mode);
    [[nodiscard]]Mode GetMode() const;
    void SetDrawing(bool new_state);
    bool IsDrawing() const;

    /// rays
    std::vector<Ray> CastRays();
    void IntersectRays(std::vector<Ray>* rays);
    void RemoveAdjacentRays(std::vector<Ray>* rays);
    Polygon CreateLightArea();
private:
    Mode mode_ = Mode::Light;
    std::vector<Polygon> polygons_;
    QPointF light_source_;
    bool light_source_visibility_ = true;
    bool is_drawing_polygons = false;
};

#endif  // CONTROLLER_H
