//
// Created by Viacheslav on 24.05.2019.
//

#include "ConvexHull.h"

vector<Point> ConvexHull::getConvexHull(const vector<Point>& a) const {
    if (a.size() == 1) return a;
    // assume that sort
//    sort (a.begin(), a.end(), &cmp);
    Point p1 = a[0], p2 = a.back();
    vector<Point> up, down;
    up.push_back(p1);
    down.push_back(p1);
    for (size_t i = 1; i < a.size(); ++i) {
        if (i == a.size() - 1 || cw(p1, a[i], p2)) {
            while (up.size() >= 2 && !cw(up[up.size() - 2], up[up.size() - 1], a[i])) {
                up.pop_back();
            }
            up.push_back(a[i]);
        }
        if (i == a.size() - 1 || ccw(p1, a[i], p2)) {
            while (down.size() >= 2 && !ccw(down[down.size() - 2], down[down.size() - 1], a[i])) {
                down.pop_back();
            }
            down.push_back(a[i]);
        }
    }
    return down;
}

bool ConvexHull::cw(Point a, Point b, Point c) {
    return a.getX() * (b.getY() - c.getY()) + b.getX() * (c.getY() - a.getY()) + c.getX() * (a.getY() - b.getY()) <= 0;
}

bool ConvexHull::ccw(Point a, Point b, Point c) {
    return a.getX() * (b.getY() - c.getY()) + b.getX() * (c.getY() - a.getY()) + c.getX() * (a.getY() - b.getY()) >= 0;
}
