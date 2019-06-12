//
// Created by Viacheslav on 22.05.2019.
//

#include <algorithm>
#include <iostream>
#include <cmath>

#include "DelaunayTriangulation.h"
#include "Circle.h"
#include "ConvexHull.h"


Edges DelaunayTriangulation::getTriangulation(vector<Point> _points) {
    vector<Point> points = move(_points);
    sort(points.begin(), points.end());
    return solve(points);
}

Edges DelaunayTriangulation::solve(const vector<Point>& points) {
    int n = points.size();
    Edges edges = Edges();

    if (n <= 3) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (i == 0 && j == 2 && points[0].getX() == points[1].getX() && points[1].getX() == points[2].getX()) {
                    continue;
                }
                if (i == 0 && j == 2 && points[0].getY() == points[1].getY() && points[1].getY() == points[2].getY()) {
                    continue;
                }
                edges[points[j]].push_back(points[i]);
                edges[points[i]].push_back(points[j]);
            }
        }
        return edges;
    }

    int mid = (n + 1) / 2;

    vector<Point> convexHull = ConvexHull().getLowerConvexHull(points);

    Point mid_point = points[mid];
    Point A;
    Point B;

    for (int i = 0; i + 1 < convexHull.size(); ++i) {
        if (convexHull[i] < mid_point && mid_point <= convexHull[i + 1]) {
            A = convexHull[i];
            B = convexHull[i + 1];
            break;
        }
    }

    Edges left_edges = solve({points.begin(), points.begin() + mid});
    Edges right_edges = solve({points.begin() + mid, points.end()});

    while(true) {

        sort(right_edges[B].begin(), right_edges[B].end(),
             [&A, &B](const Point& first, const Point& second) {
                 return getClockwiseAngle(A, B, first) < getClockwiseAngle(A, B, second) ||
                        (getClockwiseAngle(A, B, first) == getClockwiseAngle(A, B, second) && B.distToPoint(first) < B.distToPoint(second));
             });

        sort(left_edges[A].begin(), left_edges[A].end(),
             [&A, &B](const Point& first, const Point& second) {
                 return getCounterclockwiseAngle(B, A, first) < getCounterclockwiseAngle(B, A, second) ||
                        (getCounterclockwiseAngle(B, A, first) == getCounterclockwiseAngle(B, A, second) && A.distToPoint(first) < A.distToPoint(second));
             });

        bool rightCandidateChoosen = false;
        Point rightCandidate;

        for (int i = 0; !rightCandidateChoosen && i < right_edges[B].size(); ++i) {
            const Point& candidate = right_edges[B][i];
            double angle = getClockwiseAngle(A, B, candidate);
            if (angle >= M_PI) {
                break;
            }
            if (i + 1 == right_edges[B].size()) {
                rightCandidateChoosen = true;
                rightCandidate = candidate;
            } else {
                const Point& nextCandidate = right_edges[B][i + 1];
                Circle circle = Circle(A, B, candidate);
                if (circle.isPointInside(nextCandidate)) {
                    right_edges[candidate].erase(
                            remove(right_edges[candidate].begin(), right_edges[candidate].end(), B),
                            right_edges[candidate].end()
                    );
                    right_edges[B].erase(right_edges[B].begin() + i);
                    --i;
                } else {
                    rightCandidateChoosen = true;
                    rightCandidate = candidate;
                }
            }
        }

        bool leftCandidateChoosen = false;
        Point leftCandidate;

        for (int i = 0; !leftCandidateChoosen && i < left_edges[A].size(); ++i) {
            const Point& candidate = left_edges[A][i];
            double angle = getCounterclockwiseAngle(B, A, candidate);
            if (angle >= M_PI) {
                break;
            }
            if (i + 1 == left_edges[A].size()) {
                leftCandidateChoosen = true;
                leftCandidate = candidate;
            } else {
                const Point& nextCandidate = left_edges[A][i + 1];
                Circle circle = Circle(A, B, candidate);
                if (circle.isPointInside(nextCandidate)) {
                    left_edges[candidate].erase(
                        remove(left_edges[candidate].begin(), left_edges[candidate].end(), A),
                        left_edges[candidate].end()
                    );
                    left_edges[A].erase(left_edges[A].begin() + i);
                    --i;
                } else {
                    leftCandidateChoosen = true;
                    leftCandidate = candidate;
                }
            }
        }

        right_edges[B].push_back(A);
        left_edges[A].push_back(B);

        if (!leftCandidateChoosen && !rightCandidateChoosen) {
            break;
        } else if (!leftCandidateChoosen && rightCandidateChoosen) {
            B = rightCandidate;
        } else if (leftCandidateChoosen && !rightCandidateChoosen) {
            A = leftCandidate;
        } else if (leftCandidateChoosen && rightCandidateChoosen) {
            Circle circle = Circle(A, B, leftCandidate);
            if (circle.isPointInside(rightCandidate)) {
                B = rightCandidate;
            } else {
                A = leftCandidate;
            }
        }
    }
    edges.insert(left_edges.begin(), left_edges.end());
    edges.insert(right_edges.begin(), right_edges.end());

    return edges;
}

double DelaunayTriangulation::getAngle(const Point& a, const Point& b, const Point& c) {
    Point first_vector = {a.getX() - b.getX(), a.getY() - b.getY()};
    Point second_vector = {c.getX() - b.getX(), c.getY() - b.getY()};
//    dot = x1*x2 + y1*y2      # dot product between [x1, y1] and [x2, y2]
//    det = x1*y2 - y1*x2      # determinant
    double dot = first_vector.getX() * second_vector.getX() + first_vector.getY() * second_vector.getY();
    double det = first_vector.getX() * second_vector.getY() - first_vector.getY() * second_vector.getX();
    return atan2(det, dot);
}

double DelaunayTriangulation::getClockwiseAngle(const Point& a, const Point& b, const Point& c) {
    double angle = getAngle(a, b, c);

    angle = -angle;

    angle += 2 * M_PI;
    if (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    return angle;
}

double DelaunayTriangulation::getCounterclockwiseAngle(const Point& a, const Point& b, const Point& c) {
    double angle = getAngle(a, b, c);

    angle += 2 * M_PI;
    if (angle > 2 * M_PI) {
        angle -= 2 * M_PI;
    }
    return angle;
}