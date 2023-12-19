#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>

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

void calculateAreaPerimeter(Shape& shape) {
    switch (shape.type) {
        case Shape::SQUARE:
            shape.area = shape.square->side * shape.square->side;
            shape.perimeter = 4 * shape.square->side;
            break;
        case Shape::CIRCLE:
            shape.area = M_PI * shape.circle->radius * shape.circle->radius;
            shape.perimeter = 2 * M_PI * shape.circle->radius;
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
    size_t i = 0;
    while(i < s.size() && !isdigit(s[i])) i++;
    return stod(s.substr(i));
}

int main() {
    
    ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int totalShapes;
    inputFile >> totalShapes;  // Read the total number of shapes
    inputFile.ignore(numeric_limits<streamsize>::max(), '\n');  // Consume the newline character

    Shape* shapes = new Shape[totalShapes];
    string line;

    for (int i = 0; i < totalShapes; ++i) {
        getline(inputFile, line);
        Shape& shape = shapes[i];

        if (line.find("Square") != string::npos) {
            shape.type = Shape::SQUARE;
            shape.square = new Square;
            shape.square->side = extractNumber(line);
        } else if (line.find("Circle") != string::npos) {
            shape.type = Shape::CIRCLE;
            shape.circle = new Circle;
            shape.circle->radius = extractNumber(line);
        } else if (line.find("Rectangle") != string::npos) {
            shape.type = Shape::RECTANGLE;
            shape.rectangle = new Rectangle;

            size_t posW = line.find("w=");
            size_t posH = line.find(", h=");
            shape.rectangle->width = extractNumber(line.substr(posW));
            shape.rectangle->height = extractNumber(line.substr(posH));
        }

        calculateAreaPerimeter(shape);
    }

    inputFile.close();

    double maxPerimeter = 0;
    double maxArea = 0;
    double minPerimeter = numeric_limits<double>::max();
    double minArea = numeric_limits<double>::max();

    Shape *maxPerimeterShape, *maxAreaShape, *minPerimeterShape, *minAreaShape;

    int squareCount = 0;
    int circleCount = 0;
    int rectangleCount = 0;

    for (int i = 0; i < totalShapes; ++i) {
        Shape& shape = shapes[i];
        printShapeInfo(shape);
        printShapeSize(shape);

        if (shape.perimeter > maxPerimeter) {
            maxPerimeter = shape.perimeter;
            maxPerimeterShape = &shape;
        }

        if (shape.area > maxArea) {
            maxArea = shape.area;
            maxAreaShape = &shape;
        }

        if (shape.perimeter < minPerimeter) {
            minPerimeter = shape.perimeter;
            minPerimeterShape = &shape;
        }

        if (shape.area < minArea) {
            minArea = shape.area;
            minAreaShape = &shape;
        }

        switch (shape.type) {
            case Shape::SQUARE:
                squareCount++;
                break;
            case Shape::CIRCLE:
                circleCount++;
                break;
            case Shape::RECTANGLE:
                rectangleCount++;
                break;
        }
    }

   cout << "\nHinh co chu vi lon nhat: ";
    printShapeInfo(*maxPerimeterShape);
    cout << " => perimeter=" << maxPerimeter << endl;

    cout << "Hinh co dien tich lon nhat: ";
    printShapeInfo(*maxAreaShape);
    cout << " => area=" << maxArea << endl;

    cout << "Hinh co chu vi nho nhat: ";
    printShapeInfo(*minPerimeterShape);
    cout << " => perimeter=" << minPerimeter << endl;

    cout << "Hinh co dien tich nho nhat: ";
    printShapeInfo(*minAreaShape);
    cout << " => area=" << minArea << endl;



    cout << "\nThong ke cac hinh da doc" << endl;
    cout << "+ Square: " << squareCount << endl;
    cout << "+ Circle: " << circleCount << endl;
    cout << "+ Rectangle: " << rectangleCount << endl;

    // Cleanup memory
    for (int i = 0; i < totalShapes; ++i) {
        Shape& shape = shapes[i];
        switch (shape.type) {
            case Shape::SQUARE:
                delete shape.square;
                break;
            case Shape::CIRCLE:
                delete shape.circle;
                break;
            case Shape::RECTANGLE:
                delete shape.rectangle;
                break;
        }
    }

    delete[] shapes;

    return 0;
}
