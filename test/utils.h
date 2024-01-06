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

/*
Hàm tính diện tích, chu vi
*/
void calculateAreaPerimeter(Square* square, double& area, double& perimeter);
void calculateAreaPerimeter(Circle* circle, double& area, double& perimeter);
void calculateAreaPerimeter(Rectangle* rectangle, double& area, double& perimeter);
void calculateAreaPerimeter(void* shape, ShapeType type, double& area, double& perimeter);

/*
Hàm in thông tin hình
*/
void print(Square* square);
void print(Circle* circle);
void print(Rectangle* rectangle);
void print(void* shape, ShapeType type);

// Hàm trích xuất số từ chuỗi
double extractNumber(const string& s);

// Hàm in diện tích, chu vi
void printShapeSize(double area, double perimeter);

// Hàm tạo hình từ thông tin đọc
Square* createSquare(const string& buffer);
Circle* createCircle(const string& buffer);
Rectangle* createRectangle(const string& buffer);

// Hàm giải phóng bộ nhớ
void deleteShape(void* shape, ShapeType type);