#ifndef RAY_H
#define RAY_H
#include <QPoint>

class Ray {
public:
    Ray();
    Ray(const QPoint& begin,QPoint& end, double angle);
    Ray Rotate(double angle) const;

private:
    QPoint begin_;
    QPoint end_;
};

#endif  // RAY_H
