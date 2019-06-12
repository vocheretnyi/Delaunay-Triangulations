//
// Created by Viacheslav on 24.05.2019.
//

#ifndef DELAUNAY_TRIANGULATIONS_CONVEXHULL_H
#define DELAUNAY_TRIANGULATIONS_CONVEXHULL_H

#include <vector>

#include "Point.hpp"

using namespace std;

class ConvexHull {
public:

    ConvexHull() = default;

    vector<Point> getConvexHull(const vector<Point>&) const;

private:

    static bool cw(Point a, Point b, Point c);

    static bool ccw (Point a, Point b, Point c);
};


#endif //DELAUNAY_TRIANGULATIONS_CONVEXHULL_H
