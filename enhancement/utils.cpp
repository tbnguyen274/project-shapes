#include "utils.h"


void calculateAreaPerimeter(Shape& shape) {
    switch (shape.type) {
        case Shape::SQUARE:
            shape.area = shape.square->side * shape.square->side;
            shape.perimeter = 4 * shape.square->side;
            break;
        case Shape::CIRCLE:
            shape.area = 3.14 * shape.circle->radius * shape.circle->radius;
            shape.perimeter = 2 * 3.14 * shape.circle->radius;
            break;
        case Shape::RECTANGLE:
            shape.area = shape.rectangle->width * shape.rectangle->height;
            shape.perimeter = 2 * (shape.rectangle->width + shape.rectangle->height);
            break;
    }
}

void printShapeInfo(const Shape& shape) {
    switch (shape.type) {
        case Shape::SQUARE:
            cout << "Square a=" << shape.square->side;
            break;
        case Shape::CIRCLE:
            cout << "Circle r=" << shape.circle->radius;
            break;
        case Shape::RECTANGLE:
            cout << "Rectangle w=" << shape.rectangle->width << ", h=" << shape.rectangle->height;
            break;
    }
}

void printShapeSize(const Shape& shape) {
    cout << " => ";
    cout << "area=" << shape.area << ", perimeter=" << shape.perimeter << endl;    
}

double extractNumber(const string& s) {
    unsigned int i = 0;
    while (i < s.length() && !isdigit(s[i])) {
        i++;
    }
    return stod(s.substr(i));
}