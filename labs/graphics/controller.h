#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "polygon.h"
#include <vector>
#include <QColor>

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
    void ClearPlate();
    Polygon CreateLightArea(std::vector<Ray>* rays);
    void SetPolygonVisibility(bool new_status);
    bool IsPolygonVisible() const;
    QColor PolygonBorderColor() const;

    /// light source
    void SetLightSource(QPointF new_pos);
    [[nodiscard]]QPointF GetLightSource() const;
    void SetLightSourceVisibility(bool new_state);
    bool IsLightSourceVisible() const;
    void SetMode(Mode new_mode);
    [[nodiscard]]Mode GetMode() const;
    void SetDrawing(bool new_state);
    bool IsDrawing() const;
    int Ls_cnt() const;
    double Radius() const;
    QColor BackGroundColor() const;
    QColor LightSourceColor() const;

    /// rays
    std::vector<Ray> CastRays();
    void IntersectRays(std::vector<Ray>* rays);
    void SortRaysByAngle(std::vector<Ray>* rays);
    void RemoveAdjacentRays(std::vector<Ray>* rays);
    Polygon CreateLightArea();
private:
    Mode mode_ = Mode::Light;
    std::vector<Polygon> polygons_;
    const int ls_cnt_ = 12;
    const double radius_ = 5;
    QPointF light_source_;
    bool light_source_visibility_ = true;
    bool is_drawing_polygons = false;
    bool polygons_visibility_ = true;
    QColor bg_color_ = QColor(0, 0, 10);
    QColor light_source_color_ = QColor(135,206,250, 20);
    QColor polygon_border_color_ = QColor(0, 76, 153);
};

#endif  // CONTROLLER_H
