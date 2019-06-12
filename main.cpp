#include <iostream>
#include <vector>
#include <ctime>
#include <cmath>
#include <GL/freeglut.h>

#include "MinimumSpanningTree.h"
#include "GraphEdge.h"
#include "DelaunayTriangulation.h"
#include "Point.hpp"

using namespace std;

vector<Point> points;
vector<GraphEdge<Point, double>> mst;
Edges edges;
int XX;

void display() {

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);                          // BackGround color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);            // Clear the color buffer (background)

    // Anti - aliasing Begin Сглаживание
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH, GL_NICEST);

    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH, GL_NICEST);
    // Anti - aliasing End


    double SIZE = (XX / 7.0) * 4.5;
    double T = 0.75;

    // Draw triangulations
    glLineWidth(2.0);
    glColor3f(0.69f, 0.0f, 0.0f);
    glBegin(GL_LINES);
    for (const auto& item : edges) {
        const Point& from = item.first;
        for (const Point& to : item.second) {
            glVertex2f(from.getX() / SIZE - T, from.getY() / SIZE - T);
            glVertex2f(to.getX() / SIZE - T, to.getY() / SIZE - T);
        }
    }
    glEnd();

    // Draw mst
    glLineWidth(3.0);
    glColor3f(0.0f, 0.69f, 0.0f);
    glBegin(GL_LINES);
    for (const GraphEdge<Point, double>& edge : mst) {
        glVertex2f(edge.getFrom().getX() / SIZE - T, edge.getFrom().getY() / SIZE - T);
        glVertex2f(edge.getTo().getX() / SIZE - T, edge.getTo().getY() / SIZE - T);
    }
    glEnd();

    // Draw points
    glPointSize(10.0);
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_POINTS);
    for (const Point& point : points) {
        glVertex2f(point.getX() / SIZE - T, point.getY() / SIZE - T);
    }
    glEnd();
    glutSwapBuffers();  // Swap the front and back frame buffers (double buffering)
}

void draw(const vector<Point>& points, const Edges& edges, const vector<GraphEdge<Point, double>>& mst) {
    ::points = points;
    ::edges = edges;
    ::mst = mst;
    glutDisplayFunc(display);
}

void generatePoints(int sz, vector<Point>& points) {
    points.clear();
    set<Point> set_points;
    srand(time(nullptr));
    int t = sz / 3;
    XX = t;
    for (int i = 0; i < sz; ++i) {
        double x = rand() % t;
        double y = rand() % t;
        for (int j = 0; j < 5; ++j) {
            if (set_points.find({x, y}) != set_points.end()) {
                x = rand() % t;
                y = rand() % t;
            } else break;
        }
        set_points.insert({x, y});
    }
    points = {set_points.begin(), set_points.end()};
}

void Do(int argc, char **argv, int chose) {

    vector<Point> points = { // TODO: Work incorrect (vertical line)
            {0, 1},
            {1, 0},
            {1, 2},
            {1, 3},
            {2, 1},
            {3, 3},
            {4, 2},
            {5, 0},
            {5, 1},
            {5, 3},

            {2, 5},
            {7, 6},
            {5, 8},
            {0, 6},
            {6, 6},

            {5, 5},
            {3, 0},
            {4, 9},
            {4, 0},
            {3, 4},
    };

    //    vector<Point> points = {
    //            {0, 1}, {1, 0}, {1, 2}, {1, 3}, {2, 1},
    //            {3, 3},
    //
    //            {2, 5}, {0, 6},
    //
    //            {3, 0}, {3, 4},
    //    };

    //    vector<Point> points = {
    //         {4, 2}, {5, 0}, {5, 1}, {5, 3},
    //         {7, 6}, {5, 8},  {6, 6},
    //         {5, 5},  {4, 9}, {4, 0},
    //    };

    //    vector<Point> points = {
    //        {0, 1}, {1, 0}, {1, 2}, {1, 3}, {2, 1},
    //        {3, 3}, {3, 0}, {3, 4},
    //    };


    if (chose == 2) {
        int q;
        cout << "Enter count of points:\n";
        cin >> q;
        generatePoints(q, points);
    } else if (chose == 1) {
        cout << "Enter count of points and points after that:\n";
        int q;
        cin >> q;
        points.clear();
        set<Point> set_points;
        XX = 1;
        for (int i = 0; i < q; ++i) {
            double xx, yy;
            cin >> xx >> yy;
            XX = max(XX, (int) abs(xx));
            XX = max(XX, (int) abs(yy));
            set_points.insert({xx, yy});
        }

        points = {set_points.begin(), set_points.end()};
    }

    DelaunayTriangulation delaunayTriangulation = DelaunayTriangulation();
    Edges edges = delaunayTriangulation.getTriangulation(points);
    MinimumSpanningTree<Point> minimumSpanningTree;
    vector<GraphEdge<Point, double>> graphEdges;
    for (const auto& item : edges) {
        const Point& from = item.first;
        for (const Point& to : item.second) {
            graphEdges.emplace_back(from, to, from.distToPoint(to));
        }
    }

    vector<GraphEdge<Point, double>> mst;
    double length = 0.0;
    pair<vector<GraphEdge<Point, double>>, double> res = minimumSpanningTree.getMST(graphEdges);
    mst = move(res.first);
    length = res.second;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA | GLUT_MULTISAMPLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Delaunay triangulations");

    draw(points, edges, mst);
    glutMainLoop();
}

int main(int argc, char **argv) {

    cout << "Please, chose what to do:\n"
            "1. Read points from file\n"
            "2. Generate points\n";

    int chose = -1;
    cin >> chose;
    switch (chose) {
        case 1:
            Do(argc, argv, 1);
            break;
        case 2:
            Do(argc, argv, 2);
            break;
        default:
            cout << "WRONG";
    }

    return 0;
}