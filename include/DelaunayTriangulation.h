//
// Created by Viacheslav on 22.05.2019.
//

#ifndef DELAUNAY_TRIANGULATIONS_DELAUNAYTRIANGULATION_H
#define DELAUNAY_TRIANGULATIONS_DELAUNAYTRIANGULATION_H

#include <vector>
#include <map>
#include <set>

#include "Point.hpp"

using namespace std;

using Edges = map<Point, vector<Point>>;

class DelaunayTriangulation {
public:

    Edges getTriangulation(vector<Point>);

    static double getClockwiseAngle(const Point& a, const Point& b, const Point& c);

    static double getCounterclockwiseAngle(const Point& a, const Point& b, const Point& c);

private:

    static double getAngle(const Point& a, const Point& b, const Point& c);

    Edges solve(const vector<Point>&);

};


#endif //DELAUNAY_TRIANGULATIONS_DELAUNAYTRIANGULATION_H
