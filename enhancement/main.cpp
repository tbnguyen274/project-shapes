#include "utils.h"

int main() {
    // doc tap tin
    ifstream reader_in;
    reader_in.open("input.txt", ios::in);

    if (!reader_in.good()) {
        cout << "Loi khong mo duoc file." << endl;
        return 1;
    }

    // ghi tap tin
    ofstream reader_out;
    reader_out.open("output.txt", ios::out);

    if (!reader_out.good()) {
        cout << "Loi khong mo duoc file." << endl;
        return 1;
    }

    int totalShapes;
    // doc so luong hinh trong tap tin
    reader_in >> totalShapes;
    reader_in.ignore(numeric_limits<streamsize>::max(), '\n');

    Shape* shapes = new Shape[totalShapes];
    string line;

    /*doc va xu ly du lieu*/
    for (int i = 0; i < totalShapes; ++i) {
        getline(reader_in, line);
        Shape& shape = shapes[i];

        if (line.find("Square") != string::npos) {
            shape.type = Shape::SQUARE;
            shape.square = new Square;
            shape.square->side = extractNumber(line);
        } 
        
        else if (line.find("Circle") != string::npos) {
            shape.type = Shape::CIRCLE;
            shape.circle = new Circle;
            shape.circle->radius = extractNumber(line);
        } 
        
        else if (line.find("Rectangle") != string::npos) {
            shape.type = Shape::RECTANGLE;
            shape.rectangle = new Rectangle;

            size_t posW = line.find("w=");
            size_t posH = line.find(", h=");
            shape.rectangle->width = extractNumber(line.substr(posW));
            shape.rectangle->height = extractNumber(line.substr(posH));
        }

        calculateAreaPerimeter(shape);
    }

    reader_in.close();

    double maxPerimeter = 0;
    double maxArea = 0;
    double minPerimeter = numeric_limits<double>::max();
    double minArea = numeric_limits<double>::max();

    Shape *maxPerimeterShape, *maxAreaShape, *minPerimeterShape, *minAreaShape;

    int squareCount = 0;
    int circleCount = 0;
    int rectangleCount = 0;

    /*Tinh toan va in thong tin*/
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
    reader_out << "Chu vi lon nhat la: " << maxPerimeter << endl;

    cout << "Hinh co dien tich lon nhat: ";
    printShapeInfo(*maxAreaShape);
    cout << " => area=" << maxArea << endl;
    reader_out << "Dien tich lon nhat la: " << maxArea << endl;

    cout << "Hinh co chu vi nho nhat: ";
    printShapeInfo(*minPerimeterShape);
    cout << " => perimeter=" << minPerimeter << endl;
    reader_out << "Chu vi nho nhat la: " << minPerimeter << endl;

    cout << "Hinh co dien tich nho nhat: ";
    printShapeInfo(*minAreaShape);
    cout << " => area=" << minArea << endl;
    reader_out << "Dien tich nho nhat la: " << minArea << endl;

    /*Thong ke so luong*/
    cout << "\nThong ke cac hinh da doc" << endl;
    cout << "+ Square: " << squareCount << endl;
    cout << "+ Circle: " << circleCount << endl;
    cout << "+ Rectangle: " << rectangleCount << endl;

    reader_out << "\nThong ke cac hinh da doc" << endl;
    reader_out << "+ Square: " << squareCount << endl;
    reader_out << "+ Circle: " << circleCount << endl;
    reader_out << "+ Rectangle: " << rectangleCount << endl;

    reader_out.close();

    /*Thu hoi bo nho*/
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
