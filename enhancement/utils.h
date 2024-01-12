#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>
#include <cctype>

using namespace std;

struct Square {
    double side;
};

struct Circle {
    double radius;
};

struct Rectangle {
    double width;
    double height;
};

struct Shape {
    enum ShapeType {
        SQUARE,
        CIRCLE,
        RECTANGLE
    };

    ShapeType type;
    double area;
    double perimeter;

    Square* square;
    Circle* circle;
    Rectangle* rectangle;
};

void calculateAreaPerimeter(Shape& shape);
void printShapeInfo(const Shape& shape);
void printShapeSize(const Shape& shape);
double extractNumber(const string& s);