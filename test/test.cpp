#include "utils.h"

int main() {
    ifstream reader;
    reader.open("input.txt", ios::in);

    if (!reader.good()) {
        cout << "Error opening file." << endl;
        return 1;
    }

    ofstream reader_out;
    reader_out.open("output.txt", ios::out);

    if (!reader_out.good()) {
        cout << "Error opening output file." << endl;
        return 1;
    }


    int totalShapes;
    // the first line of input.txt is the total number of shapes
    reader >> totalShapes;  
    reader.ignore(numeric_limits<streamsize>::max(), '\n');

    void** shapes = new void* [Max];
    ShapeType* types = new ShapeType[Max];

    for (int i = 0; i < totalShapes; ++i) {
        string buffer;
        getline(reader, buffer);

        if (buffer.find("Square") != string::npos) {
            shapes[i] = createSquare(buffer);
            types[i] = SQUARE;
        }
        else if (buffer.find("Circle") != string::npos) {
            shapes[i] = createCircle(buffer);
            types[i] = CIRCLE;
        }
        else if (buffer.find("Rectangle") != string::npos) {
            shapes[i] = createRectangle(buffer);
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

    ShapeType maxPerimeterType;
    ShapeType maxAreaType;
    ShapeType minPerimeterType;
    ShapeType minAreaType;

    int squareCount = 0;
    int circleCount = 0;
    int rectangleCount = 0;

    for (int i = 0; i < totalShapes; ++i) {
        double area, perimeter;

        calculateAreaPerimeter(shapes[i], types[i], area, perimeter);
        print(shapes[i], types[i]);
        printShapeSize(area, perimeter);

        // Tracking max/min and counting shapes
        if (perimeter > maxPerimeter) {
            maxPerimeter = perimeter;
            maxPerimeterShape = shapes[i];
            maxPerimeterType = types[i];
        }

        if (area > maxArea) {
            maxArea = area;
            maxAreaShape = shapes[i];
            maxAreaType = types[i];
        }

        if (perimeter < minPerimeter) {
            minPerimeter = perimeter;
            minPerimeterShape = shapes[i];
            minPerimeterType = types[i];
        }

        if (area < minArea) {
            minArea = area;
            minAreaShape = shapes[i];
            minAreaType = types[i];
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
        print(maxPerimeterShape, maxPerimeterType);
        cout << " => perimeter=" << maxPerimeter << endl;

        reader_out << "Chu vi lon nhat la : " << maxPerimeter << endl;
    }

    if (maxAreaShape != nullptr) {
        cout << "Hinh co dien tich lon nhat: ";
        print(maxAreaShape, maxAreaType);
        cout << " => area=" << maxArea << endl;
        
        reader_out << "Dien tich lon nhat la: " << maxArea << endl;
    }

    if (minPerimeterShape != nullptr) {
        cout << "Hinh co chu vi nho nhat: ";
        print(minPerimeterShape, minPerimeterType);
        cout << " => perimeter=" << minPerimeter << endl;

        reader_out << "Chu vi nho nhat la : " << minPerimeter << endl;
    }

    if (minAreaShape != nullptr) {
        cout << "Hinh co dien tich nho nhat: ";
        print(minAreaShape, minAreaType);
        cout << " => area=" << minArea << endl;

        reader_out << "Dien tich nho nhat la: " << minArea << endl;
    }

    cout << "\nThong ke cac hinh da doc" << endl;
    cout << "+ Square: " << squareCount << endl;
    cout << "+ Circle: " << circleCount << endl;
    cout << "+ Rectangle: " << rectangleCount << endl;

    reader_out << "\nThong ke cac hinh da doc" << endl;
    reader_out << "+ Square: " << squareCount << endl;
    reader_out << "+ Circle: " << circleCount << endl;
    reader_out << "+ Rectangle: " << rectangleCount << endl;

    reader_out.close();



    // Cleanup memory
    for (int i = 0; i < totalShapes; ++i) {
        deleteShape(shapes[i], types[i]);
    }

    delete[] shapes;
    delete[] types;

    return 0;
}
