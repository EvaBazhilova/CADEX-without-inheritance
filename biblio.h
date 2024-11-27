#pragma once

#include <iostream>
#include <iomanip>
#include <variant>
#include <vector>

struct Point
{
    Point() = default;
    Point(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}

    double x = 0.0;
    double y = 0.0;
    double z = 0.0;
};

class Circle;
class Ellipse;
class Helix;

inline std::ostream &operator<<(std::ostream &out, const Point point)
{
    out << std::setprecision(9) << point.x << " " << point.y << " " << point.z;
    return out;
};

class Curves
{
public:
    Curves() = default;
    Curves &AddCurve(std::variant<Circle, Ellipse, Helix>);
    Curves &CollectOnlyCircles();

    std::vector<std::variant<Circle, Ellipse, Helix>> &GetCurves();

    Curves &SortCircles();

    double ComputeTotalRadiusSum() const;

    void PrintPointsAndDerivative(std::ostream &out);

    void PrintCurves(std::ostream &out);
    void PrintCircles(std::ostream &out);

private:
    std::vector<std::variant<Circle, Ellipse, Helix>> curves_;
    std::vector<Circle *> circles_;
};

/*
Circle
    Parametric equation
    x=R*cos(t);
    y=R*sin(t);
    z=0;

    First derivative parametric equation
    x=-R*sin(t);
    y=R*cos(t);
    z=0;

    Here, R is radius_
*/

class Circle
{
public:
    Circle();
    Circle(double r);

    Circle &SetRadius(double r);

    double GetRadius() const;

    void Print(std::ostream &out);

    Point GetPoint(double t);
    Point GetDerivative(double t);

private:
    double radius_ = 1.0;
};

/*
Ellipse
    Parametric equation
    x=a*cos(t);
    y=b*sin(t);
    z=0;

    first derivative parametric equation
    x=-a*sin(t);
    y=b*cos(t);
    z=0;

    Here, a is half_width_ and b is half_height_
*/
class Ellipse
{
public:
    Ellipse();
    Ellipse(double a, double b);

    Ellipse &SetParameters(double a, double b);

    std::pair<double, double> GetParameters() const;

    void Print(std::ostream &out);

    Point GetPoint(double t);
    Point GetDerivative(double t);

private:
    double half_width_ = 2.0;
    double half_height_ = 1.0;
};

/*
3D Helix
    Parametric equation
    x=R*cos(t);
    y=R*sin(t);
    z=H/(2*Pi)*t;

    first derivative parametric equation
    x=-R*sin(t);
    y=R*cos(t);
    z=H/(2*Pi);

    Here, R is radius_ and H is h_;
*/

class Helix
{
public:
    Helix();
    Helix(double r, double h);

    Helix &SetParameters(double r, double h);

    std::pair<double, double> GetParameters() const;

    void Print(std::ostream &out);

    Point GetPoint(double t);
    Point GetDerivative(double t);

private:
    double radius_ = 1.0;
    double h_ = 1.0;
    
};