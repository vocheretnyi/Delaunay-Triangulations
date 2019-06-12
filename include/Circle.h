//
// Created by Viacheslav on 23.05.2019.
//

#ifndef DELAUNAY_TRIANGULATIONS_CIRCLE_H
#define DELAUNAY_TRIANGULATIONS_CIRCLE_H

#include "Point.hpp"

class Circle {
public:
    Circle(Point p1, Point p2, Point p3);

    bool isPointInside(const Point&) const;

private:
    Point centre;
    double r;
};


#endif //DELAUNAY_TRIANGULATIONS_CIRCLE_H
