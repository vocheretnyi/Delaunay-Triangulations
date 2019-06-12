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

    vector<Point> getLowerConvexHull(vector<Point> a) const;

private:

    // check if points create counter-clockwise angle
    static bool ccw (Point a, Point b, Point c);
};


#endif //DELAUNAY_TRIANGULATIONS_CONVEXHULL_H
