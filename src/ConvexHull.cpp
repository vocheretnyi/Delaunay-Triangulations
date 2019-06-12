//
// Created by Viacheslav on 24.05.2019.
//

#include "ConvexHull.h"

#include <algorithm>
#include <iostream>

using  namespace std;

vector<Point> ConvexHull::getLowerConvexHull(vector<Point> points) const {
    if (points.size() == 1) return points;
    vector<Point> a = move(points);
    if (!is_sorted(a.begin(), a.end())) {
        sort(a.begin(), a.end());
    }
    Point p1 = a[0], p2 = a.back();
    vector<Point> down;
    down.push_back(p1);
    for (int i = 1; i < a.size(); ++i) {
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i])) {
                down.pop_back();
            }
            down.push_back(a[i]);
        }
    }
    return down;
}

bool ConvexHull::ccw(Point a, Point b, Point c) {
    return a.getX() * (b.getY() - c.getY()) + b.getX() * (c.getY() - a.getY()) + c.getX() * (a.getY() - b.getY()) >= 0;
}
