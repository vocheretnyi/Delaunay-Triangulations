//
// Created by Viacheslav on 23.05.2019.
//

#include <cmath>
#include <algorithm>
#include <cassert>

#include "Circle.h"
#include "DelaunayTriangulation.h"

Circle::Circle(Point p1, Point p2, Point p3) {
    const double eps = 1e-6;
    if (fabs(p1.getY() - p2.getY()) < eps && fabs(p1.getY() - p3.getY()) < eps) {
        assert(false && "NO CIRCLE");
    }
    if (fabs(p1.getX() - p2.getX()) < eps && fabs(p1.getX() - p3.getX()) < eps) {
        assert(false && "NO CIRCLE");
    }

    if (p1.getX() == p2.getX()) {
        swap(p2, p3);
    }
    if (p2.getX() == p3.getX()) {
        swap(p1, p2);
    }
    if (p1.getY() == p2.getY()) {
        swap(p1, p3);
    }
    double xDelta_a = (p2.getX() - p1.getX());
    double yDelta_b = (p3.getY() - p2.getY());

    if (fabs(xDelta_a) < eps && fabs(yDelta_b) < eps) {
        double x = 0.5 * (p2.getX() + p3.getX());
        double y = 0.5 * (p1.getY() + p2.getY());
        centre = {x, y};
        r = centre.distToPoint(p1);
        return;
    }

    double ma = (p2.getY() - p1.getY()) / xDelta_a;
    double mb = yDelta_b / (p3.getX() - p2.getX());
    double x = (ma * mb * (p1.getY() - p3.getY()) + mb * (p1.getX() + p2.getX()) -
                ma * (p2.getX() + p3.getX())) / (2 * (mb - ma));
    double y = -1 * (x - (p1.getX() + p2.getX()) / 2) / ma + (p1.getY() + p2.getY()) / 2;
    centre = {x, y};
    r = centre.distToPoint(p1);
}

bool Circle::isPointInside(const Point& point) const {
    return centre.distToPoint(point) < r;
}
