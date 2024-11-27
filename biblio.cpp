#define _USE_MATH_DEFINES

#include "biblio.h"
#include <algorithm>
#include <math.h>

Curves &Curves::AddCurve(std::variant<std::shared_ptr<Circle>, std::shared_ptr<Ellipse>, std::shared_ptr<Helix>> curve)
{
    curves_.push_back(curve);
    return *this;
}

Curves &Curves::CollectOnlyCircles()
{
    for (size_t i = 0; i < curves_.size(); ++i)
    {
        if (std::holds_alternative<std::shared_ptr<Circle>>(curves_[i]))
        {
            circles_.push_back(std::get<std::shared_ptr<Circle>>(curves_[i]));
        }
    }
    return *this;
}

std::vector<std::variant<std::shared_ptr<Circle>, std::shared_ptr<Ellipse>, std::shared_ptr<Helix>>> &Curves::GetCurves()
{
    return curves_;
}

Curves &Curves::SortCircles()
{
    std::sort(circles_.begin(), circles_.end(), [](const std::shared_ptr<Circle>lhs, const std::shared_ptr<Circle> rhs)
              { return lhs->GetRadius() < rhs->GetRadius(); });
    return *this;
}

double Curves::ComputeTotalRadiusSum() const
{
    double answ = 0.0;
    for (size_t i = 0; i < circles_.size(); ++i)
    {
        answ+= circles_[i]->GetRadius();
    }
    return answ;
};

void Curves::PrintPointsAndDerivative(std::ostream &out)
{
    for (size_t i = 0; i < curves_.size(); ++i)
    {
        if (std::holds_alternative<std::shared_ptr<Circle>>(curves_[i]))
        {
            out << std::get<std::shared_ptr<Circle>>(curves_[i])->GetPoint(M_PI / 4) << " " << std::get<std::shared_ptr<Circle>>(curves_[i])->GetDerivative(M_PI / 4);
        }
        else if (std::holds_alternative<std::shared_ptr<Ellipse>>(curves_[i]))
        {
            out << std::get<std::shared_ptr<Ellipse>>(curves_[i])->GetPoint(M_PI / 4) << " " << std::get<std::shared_ptr<Ellipse>>(curves_[i])->GetDerivative(M_PI / 4);
        }
        else
        {
            out << std::get<std::shared_ptr<Helix>>(curves_[i])->GetPoint(M_PI / 4) << " " << std::get<std::shared_ptr<Helix>>(curves_[i])->GetDerivative(M_PI / 4);
        }
        out << std::endl;
    }
}

void Curves::PrintCurves(std::ostream &out)
{
    for (size_t i = 0; i < curves_.size(); ++i)
    {
        if (std::holds_alternative<std::shared_ptr<Circle>>(curves_[i]))
        {
            out << "Circle with radius " << std::get<std::shared_ptr<Circle>>(curves_[i])->GetRadius();
        }
        else if (std::holds_alternative<std::shared_ptr<Ellipse>>(curves_[i]))
        {
            out << "Ellipse with parameters " << std::get<std::shared_ptr<Ellipse>>(curves_[i])->GetParameters().first << " " << std::get<std::shared_ptr<Ellipse>>(curves_[i])->GetParameters().second;
        }
        else
        {
            out << "Helix with parameters " << std::get<std::shared_ptr<Helix>>(curves_[i])->GetParameters().first << " " << std::get<std::shared_ptr<Helix>>(curves_[i])->GetParameters().second;
        }
        out << std::endl;
    }
}

void Curves::PrintCircles(std::ostream &out)
{
    for (size_t i = 0; i < circles_.size(); ++i)
    {
        out << "Circle with radius " << circles_[i]->GetRadius();
        out << std::endl;
    }
}

Circle::Circle() : radius_(1.0) {}

Circle::Circle(double r)
{
    if (r <= 0)
    {
        throw std::logic_error("Radius can not be negative or zero");
    }
    else
    {
        radius_ = r;
    }
}

Circle &Circle::SetRadius(double r)
{
    if (r <= 0)
    {
        throw std::logic_error("Radius can not be negative or zero");
    }
    else
    {
        radius_ = r;
    }
    return *this;
}

double Circle::GetRadius() const
{
    return radius_;
}

void Circle::Print(std::ostream &out)
{
    for (double t = 0; t < 2 * M_PI; t += 1E-03)
    {
        out << Point{radius_ * cos(t), radius_ * sin(t), 0} << std::endl;
    }
};

Point Circle::GetPoint(double t)
{
    return Point{radius_ * cos(t), radius_ * sin(t), 0};
}

Point Circle::GetDerivative(double t)
{
    return Point{radius_ * sin(t) * (-1), radius_ * cos(t), 0};
}

Ellipse::Ellipse() : half_width_(2.0), half_height_(1.0) {}

Ellipse::Ellipse(double a, double b)
{
    if (a <= 0 || b <= 0)
    {
        throw std::logic_error("Parameters can not be negative or zero");
    }
    else
    {
        half_width_ = a;
        half_height_ = b;
    }
}

Ellipse &Ellipse::SetParameters(double a, double b)
{
    if (a <= 0 || b <= 0)
    {
        throw std::logic_error("Parameters can not be negative or zero");
    }
    else
    {
        half_width_ = a;
        half_height_ = b;
    }
    return *this;
}

std::pair<double, double> Ellipse::GetParameters() const
{
    return std::make_pair(half_width_, half_height_);
}

void Ellipse::Print(std::ostream &out)
{
    for (double t = 0; t < 2 * M_PI; t += 1E-03)
    {
        out << Point{half_width_ * cos(t), half_height_ * sin(t), 0} << std::endl;
    }
};

Point Ellipse::GetPoint(double t)
{
    return Point{half_width_ * cos(t), half_height_ * sin(t), 0};
}

Point Ellipse::GetDerivative(double t)
{
    return Point{half_width_ * sin(t) * (-1), half_height_ * cos(t), 0};
}

Helix::Helix() : radius_(1.0), h_(1.0) {}

Helix::Helix(double r, double h)
{
    if (r <= 0 || h <= 0)
    {
        throw std::logic_error("Parameters can not be negative or zero");
    }
    else
    {
        radius_ = r;
        h_ = h;
    }
}

Helix &Helix::SetParameters(double r, double h)
{
    if (r <= 0 || h <= 0)
    {
        throw std::logic_error("Parameters can not be negative or zero");
    }
    else
    {
        radius_ = r;
        h_ = h;
    }
    return *this;
}

std::pair<double, double> Helix::GetParameters() const
{
    return std::make_pair(radius_, h_);
}

void Helix::Print(std::ostream &out)
{
    for (double t = 0; t < 4 * M_PI; t += 1E-03)
    {
        out << Point{radius_ * cos(t), radius_ * sin(t), h_ / (2 * M_PI) * t} << std::endl;
    }
};

Point Helix::GetPoint(double t)
{
    return Point{radius_ * cos(t), radius_ * sin(t), h_ / (2 * M_PI) * t};
}

Point Helix::GetDerivative(double t)
{
    return Point{radius_ * sin(t) * (-1), radius_ * cos(t), h_ / (2 * M_PI)};
}