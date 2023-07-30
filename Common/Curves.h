// Curves.h

#pragma once

#include <iostream>
#include <vector>

const double PI = 3.141592653589793238463;

class Curve3D {
public:
    virtual ~Curve3D() = default;

    virtual std::vector<double> getPoint(double t) const = 0;

    virtual std::vector<double> getDerivative(double t) const = 0;
};

class Circle : public Curve3D {
public:
    Circle(double radius);

    std::vector<double> getPoint(double t) const override;

    std::vector<double> getDerivative(double t) const override;

    double getRadius() const;

private:
    double radius;
};

class Ellipse : public Curve3D {
public:
    Ellipse(double xRadius, double yRadius);

    std::vector<double> getPoint(double t) const override;

    std::vector<double> getDerivative(double t) const override;

private:
    double xRadius, yRadius;
};

class Helix : public Curve3D {
public:
    Helix(double radius, double step);

    std::vector<double> getPoint(double t) const override;

    std::vector<double> getDerivative(double t) const override;

private:
    double radius, step;
};

double computeTotalRadiiSum(const std::vector<std::unique_ptr<Curve3D>>& curves);