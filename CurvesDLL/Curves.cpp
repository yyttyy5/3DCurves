// Curves.cpp

#include "Curves.h"
#include <iostream>
#include <cmath>
#include <omp.h>

Circle::Circle(double radius) : radius(radius) {
    if (radius <= 0.0) {
        throw std::invalid_argument("The radius of the circle must be positive.");
    }
}

std::vector<double> Circle::getPoint(double t) const {
    return { radius * cos(t), radius * sin(t), 0.0 };
}

std::vector<double> Circle::getDerivative(double t) const {
    return { -radius * sin(t), radius * cos(t), 0.0 };
}

double Circle::getRadius() const {
    return radius;
}

Ellipse::Ellipse(double xRadius, double yRadius) : xRadius(xRadius), yRadius(yRadius) {
    if (xRadius <= 0.0 || yRadius <= 0.0) {
        throw std::invalid_argument("The radii of the ellipse must be positive.");
    }
}

std::vector<double> Ellipse::getPoint(double t) const {
    return { xRadius * cos(t), yRadius * sin(t), 0.0 };
}

std::vector<double> Ellipse::getDerivative(double t) const {
    return { -xRadius * sin(t), yRadius * cos(t), 0.0 };
}

Helix::Helix(double radius, double step) : radius(radius), step(step) {
    if (radius <= 0.0 || step <= 0.0) {
        throw std::invalid_argument("The radius of the helix and the step must be positive.");
    }
}

std::vector<double> Helix::getPoint(double t) const {
    return { radius * cos(t), radius * sin(t), step * t / (2.0 * PI) };
}

std::vector<double> Helix::getDerivative(double t) const {
    return { -radius * sin(t), radius * cos(t), step / (2.0 * PI) };
}

double computeTotalRadiiSum(const std::vector<std::unique_ptr<Curve3D>>& curves) {
    double totalRadiiSum = 0.0;
    #pragma omp parallel for reduction(+:totalRadiiSum)
    for (const auto& curve : curves) {
        if (auto circle = dynamic_cast<Circle*>(curve.get())) {
            totalRadiiSum += circle->getRadius();
        }
    }
    return totalRadiiSum;
}