// Main.cpp

#include <iostream>
#include <vector>
#include <algorithm>
#include "Curves.h"

int main() {
    // Step 2: Create a container and fill it with random curves
    std::vector<std::unique_ptr<Curve3D>> curves;

    try {
        curves.push_back(std::make_unique<Circle>(8.0));
        curves.push_back(std::make_unique<Ellipse>(3.0, 2.0));
        curves.push_back(std::make_unique<Helix>(1.0, 1.33));
        curves.push_back(std::make_unique<Circle>(2.5));
        curves.push_back(std::make_unique<Ellipse>(1.0, 1.0));
        curves.push_back(std::make_unique<Helix>(3.0, 0.5));
    }
    catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        system("pause");
        return 1;
    }

    // Step 3: Output coordinates of points and vectors of derivatives for all curves at t = PI/4
    std::cout << "Coordinates of points and vectors of derivatives at t = PI/4:" << std::endl;
    for (const auto& curve : curves) {
        double t = PI / 4.0;
        std::vector<double> point = curve->getPoint(t);
        std::vector<double> derivative = curve->getDerivative(t);
        std::cout << "Point: (" << point[0] << ", " << point[1] << ", " << point[2] << ") ";
        std::cout << "Derivative: (" << derivative[0] << ", " << derivative[1] << ", " << derivative[2] << ")" << std::endl;
    }

    // Step 4: Create a second container containing only circles (using pointers)
    std::vector<Circle*> circlesOnly;
    for (const auto& curve : curves) {
        if (auto circle = dynamic_cast<Circle*>(curve.get())) {
            circlesOnly.push_back(circle);
        }
    }

    // Step 5: Sort the second container in ascending order of circle radii
    std::sort(circlesOnly.begin(), circlesOnly.end(),
        [](const Circle* a, const Circle* b) {
            return a->getRadius() < b->getRadius();
        });

    // Step 6: Calculate the total sum of the radii of all circles using parallel computations
    double totalRadiiSum = computeTotalRadiiSum(curves);

    std::cout << "The total sum of the radii of all circles: " << totalRadiiSum << std::endl;

    system("pause");
    return 0;
}