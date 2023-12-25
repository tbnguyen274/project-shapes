// use void* pointers

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <limits>
#include <cctype>

using namespace std;

const int Max = 100;

enum ShapeType {
    SQUARE,
    CIRCLE,
    RECTANGLE
};

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

void calculateAreaPerimeter(void* shape, ShapeType type, double& area, double& perimeter) {
    switch (type) {
    case SQUARE: {
        Square* square = static_cast<Square*>(shape);
        area = square->side * square->side;
        perimeter = 4 * square->side;
        break;
    }
    case CIRCLE: {
        Circle* circle = static_cast<Circle*>(shape);
        area = 3.14 * circle->radius * circle->radius;
        perimeter = 2 * 3.14 * circle->radius;
        break;
    }
    case RECTANGLE: {
        Rectangle* rectangle = static_cast<Rectangle*>(shape);
        area = rectangle->width * rectangle->height;
        perimeter = 2 * (rectangle->width + rectangle->height);
        break;
    }
    }
}

double extractNumber(const string& s) {
    unsigned int i = 0;
    while (i < s.length() && !isdigit(s[i]) && s[i] != '.') {
        i++;
    }
    return stod(s.substr(i));
}

void printShapeInfo(void* shape, ShapeType type) {
    switch (type) {
    case SQUARE:
        cout << "Square a=" << static_cast<Square*>(shape)->side;
        break;
    case CIRCLE:
        cout << "Circle r=" << static_cast<Circle*>(shape)->radius;
        break;
    case RECTANGLE:
        cout << "Rectangle w=" << static_cast<Rectangle*>(shape)->width
                  << ", h=" << static_cast<Rectangle*>(shape)->height;
        break;
    }
}

void printShapeSize(double area, double perimeter) {
    cout << " => ";
    cout << "area=" << area << ", perimeter=" << perimeter << endl;
}

int main() {
    ifstream reader;
    reader.open("input.txt", ios::in);

    if (!reader.good()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    int totalShapes;
    reader >> totalShapes;  // the first line of input.txt is the total number of shapes
    reader.ignore(numeric_limits<streamsize>::max(), '\n');

    void** shapes = new void*[Max];
    ShapeType* types = new ShapeType[Max];

    for (int i = 0; i < totalShapes; ++i) {
        string buffer;
        getline(reader, buffer);

        if (buffer.find("Square") != string::npos) {
            shapes[i] = new Square;
            static_cast<Square*>(shapes[i])->side = extractNumber(buffer);
            types[i] = SQUARE;
        } else if (buffer.find("Circle") != string::npos) {
            shapes[i] = new Circle;
            static_cast<Circle*>(shapes[i])->radius = extractNumber(buffer);
            types[i] = CIRCLE;
        } else if (buffer.find("Rectangle") != string::npos) {
            shapes[i] = new Rectangle;
            unsigned int posW = buffer.find("w=");
            unsigned int posH = buffer.find(", h=");
            static_cast<Rectangle*>(shapes[i])->width = extractNumber(buffer.substr(posW));
            static_cast<Rectangle*>(shapes[i])->height = extractNumber(buffer.substr(posH));
            types[i] = RECTANGLE;
        }
    }

    reader.close();

    double maxPerimeter = 0;
    double maxArea = 0;
    double minPerimeter = numeric_limits<double>::max();
    double minArea = numeric_limits<double>::max();

    void* maxPerimeterShape = nullptr;
    void* maxAreaShape = nullptr;
    void* minPerimeterShape = nullptr;
    void* minAreaShape = nullptr;

    int squareCount = 0;
    int circleCount = 0;
    int rectangleCount = 0;

    for (int i = 0; i < totalShapes; ++i) {
        double area, perimeter;
        calculateAreaPerimeter(shapes[i], types[i], area, perimeter);

        printShapeInfo(shapes[i], types[i]);
        printShapeSize(area, perimeter);

        // Tracking max/min and counting shapes
        if (perimeter > maxPerimeter) {
            maxPerimeter = perimeter;
            maxPerimeterShape = shapes[i];
        }

        if (area > maxArea) {
            maxArea = area;
            maxAreaShape = shapes[i];
        }

        if (perimeter < minPerimeter) {
            minPerimeter = perimeter;
            minPerimeterShape = shapes[i];
        }

        if (area < minArea) {
            minArea = area;
            minAreaShape = shapes[i];
        }

        switch (types[i]) {
        case SQUARE:
            squareCount++;
            break;
        case CIRCLE:
            circleCount++;
            break;
        case RECTANGLE:
            rectangleCount++;
            break;
        }
    }

    if (maxPerimeterShape != nullptr) {
        cout << "\nHinh co chu vi lon nhat: ";
        printShapeInfo(maxPerimeterShape, types[0]);
        cout << " => perimeter=" << maxPerimeter << endl;
    }

    if (maxAreaShape != nullptr) {
        cout << "Hinh co dien tich lon nhat: ";
        printShapeInfo(maxAreaShape, types[0]);
        cout << " => area=" << maxArea << endl;
    }

    if (minPerimeterShape != nullptr) {
        cout << "Hinh co chu vi nho nhat: ";
        printShapeInfo(minPerimeterShape, types[0]);
        cout << " => perimeter=" << minPerimeter << endl;
    }

    if (minAreaShape != nullptr) {
        cout << "Hinh co dien tich nho nhat: ";
        printShapeInfo(minAreaShape, types[0]);
        cout << " => area=" << minArea << endl;
    }

    cout << "\nThong ke cac hinh da doc" << endl;
    cout << "+ Square: " << squareCount << endl;
    cout << "+ Circle: " << circleCount << endl;
    cout << "+ Rectangle: " << rectangleCount << endl;

    // Cleanup memory
    for (int i = 0; i < totalShapes; ++i) {
        switch (types[i]) {
        case SQUARE:
            delete static_cast<Square*>(shapes[i]);
            break;
        case CIRCLE:
            delete static_cast<Circle*>(shapes[i]);
            break;
        case RECTANGLE:
            delete static_cast<Rectangle*>(shapes[i]);
            break;
        }
    }

    delete[] shapes;
    delete[] types;

    return 0;
}
