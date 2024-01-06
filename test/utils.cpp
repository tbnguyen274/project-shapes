#include "utils.h"

void calculateAreaPerimeter(Square* square, double& area, double& perimeter) {
    area = square->side * square->side;
    perimeter = 4 * square->side;
}

void calculateAreaPerimeter(Circle* circle, double& area, double& perimeter) {
    area = 3.14 * circle->radius * circle->radius;
    perimeter = 2 * 3.14 * circle->radius;
}

void calculateAreaPerimeter(Rectangle* rectangle, double& area, double& perimeter) {
    area = rectangle->width * rectangle->height;
    perimeter = 2 * (rectangle->width + rectangle->height);
}

void calculateAreaPerimeter(void* shape, ShapeType type, double& area, double& perimeter) {
    if (ShapeType::SQUARE == type) {
        calculateAreaPerimeter(static_cast<Square*>(shape), area, perimeter);
    }
    else if (ShapeType::CIRCLE == type) {
        calculateAreaPerimeter(static_cast<Circle*>(shape), area, perimeter);
    }
    else if (ShapeType::RECTANGLE == type) {
        calculateAreaPerimeter(static_cast<Rectangle*>(shape), area, perimeter);
    }
}


void print(Square* square) {
    cout << "Square a=" << square->side;
}

void print(Circle* circle) {
    cout << "Circle r=" << circle->radius;
}

void print(Rectangle* rectangle) {
    cout << "Rectangle w=" << rectangle->width
        << ", h=" << rectangle->height;
}

void print(void* shape, ShapeType type) {
    if (ShapeType::SQUARE == type) {
        print(static_cast<Square*>(shape));
    }
    else if (ShapeType::CIRCLE == type) {
        print(static_cast<Circle*>(shape));
    }
    else if (ShapeType::RECTANGLE == type) {
        print(static_cast<Rectangle*>(shape));
    }
}


double extractNumber(const string& s) {
    unsigned int i = 0;
    while (i < s.length() && !isdigit(s[i])) {
        i++;
    }
    return stod(s.substr(i));
}


void printShapeSize(double area, double perimeter) {
    cout << " => ";
    cout << "area=" << area << ", perimeter=" << perimeter << endl;
}


Square* createSquare(const string& buffer) {
    Square* square = new Square;
    square->side = extractNumber(buffer);
    return square;
}

Circle* createCircle(const string& buffer) {
    Circle* circle = new Circle;
    circle->radius = extractNumber(buffer);
    return circle;
}

Rectangle* createRectangle(const string& buffer) {
    Rectangle* rectangle = new Rectangle;
    unsigned int posW = buffer.find("w=");
    unsigned int posH = buffer.find(", h=");
    rectangle->width = extractNumber(buffer.substr(posW));
    rectangle->height = extractNumber(buffer.substr(posH));
    return rectangle;
}

void deleteShape(void* shape, ShapeType type) {
    if (ShapeType::SQUARE == type) {
        delete static_cast<Square*>(shape);
    }
    else if (ShapeType::CIRCLE == type) {
        delete static_cast<Circle*>(shape);
    }
    else if (ShapeType::RECTANGLE == type) {
        delete static_cast<Rectangle*>(shape);
    }
}