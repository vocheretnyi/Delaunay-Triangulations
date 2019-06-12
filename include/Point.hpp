//
// Created by Viacheslav on 22.05.2019.
//

#ifndef DELAUNAY_TRIANGULATIONS_POINT_HPP
#define DELAUNAY_TRIANGULATIONS_POINT_HPP

#include <ostream>
#include <cmath>

class Point {
public:
    Point() :
        x_(0.0), y_(0.0) {}

    Point(double x, double y) :
        x_(x), y_(y) {}

    Point& operator=(const Point& other) = default;

    double getX() const {
        return x_;
    }

    double getY() const {
        return y_;
    }

    double distToPoint(const Point& other) const {
        return sqrt(sqr(this->getX() - other.getX()) + sqr(this->getY() - other.getY()));
    }

    friend bool operator<(const Point& main, const Point& other) {
        return main.x_ < other.x_ || (main.x_ == other.x_ && main.y_ < other.y_);
    }

    friend bool operator==(const Point& main, const Point& other) {
        return main.x_ == other.x_ && main.y_ == other.y_;
    }

    friend bool operator<=(const Point& main, const Point& other) {
        return main < other || main == other;
    }

    friend std::ostream& operator<<(std::ostream& out, const Point& point) {
        out << '{' << point.getX() << ", " << point.getY() << "}";
        return out;
    }

private:

    static double sqr(double x) {
        return x * x;
    }

    double x_, y_;
};


#endif //DELAUNAY_TRIANGULATIONS_POINT_HPP
