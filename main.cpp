#define _USE_MATH_DEFINES

#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <math.h>

#include "biblio.h"

void CheckNegative()
{
    bool success;
    try
    {
        Circle circle(-2);
        success = true;
    }
    catch (std::logic_error &err)
    {
        success = false;
    }
    assert(success == false);

    try
    {
        Circle circle;
        circle.SetRadius(-100);
        success = true;
    }
    catch (std::logic_error &err)
    {
        success = false;
    }
    assert(success == false);

    try
    {
        Ellipse ellipse(-2, -3);
        success = true;
    }
    catch (std::logic_error &err)
    {
        success = false;
    }
    assert(success == false);

    try
    {
        Ellipse ellipse;
        ellipse.SetParameters(-100, 2);
        success = true;
    }
    catch (std::logic_error &err)
    {
        success = false;
    }
    assert(success == false);

    try
    {
        Helix helix(-2, -3);
        success = true;
    }
    catch (std::logic_error &err)
    {
        success = false;
    }
    assert(success == false);

    try
    {
        Helix helix;
        helix.SetParameters(0, -20);
        success = true;
    }
    catch (std::logic_error &err)
    {
        success = false;
    }
    assert(success == false);

    std::cout << "OK!" << std::endl;
}

void PrintingCircleTest(std::ofstream &out)
{
    Circle circle(2);
    Circle circle_1;
    Circle circle_2;

    circle.Print(out);
    circle_1.SetRadius(3).Print(out);
    circle_2.Print(out);
}

void PrintingEllipseTest(std::ofstream &out)
{
    Ellipse ellpise(3, 4);
    Ellipse ellpise_1;
    Ellipse ellpise_2;

    ellpise.Print(out);
    ellpise_1.SetParameters(5, 1).Print(out);
    ellpise_2.Print(out);
}

void PrintingHelixTest(std::ofstream &out)
{
    Helix helix(2, 2);
    Helix helix_1;
    Helix helix_2;

    helix.Print(out);
    helix_1.SetParameters(5, 1).Print(out);
    helix_2.Print(out);
}

void GenerateRandomCurves(Curves &curves)
{
    srand(time(0));
    int curves_count = rand() % (20);
    for (int i = 0; i < curves_count; ++i)
    {
        int curve = rand() % (3);
        switch (curve)
        {
        case 0:
        {
            double r = (double)rand() / RAND_MAX * (100);
            curves.AddCurve(std::move(Circle{r}));
            break;
        }
        case 1:
        {
            double a = (double)rand() / RAND_MAX * (100);
            double b = (double)rand() / RAND_MAX * (100);
            curves.AddCurve(std::move(Ellipse{a, b}));
            break;
        }
        case 2:
        {
            double r = (double)rand() / RAND_MAX * (100);
            double h = (double)rand() / RAND_MAX * (100);
            curves.AddCurve(std::move(Helix{r, h}));
            break;
        }
        default:
            break;
        }
    }
}

int main()
{

    CheckNegative();

    std::ofstream out;
    out.open("output.txt");
    // PrintingCircleTest(out);
    // PrintingEllipseTest(out);
    // PrintingHelixTest(out);

    Curves curves;
    GenerateRandomCurves(curves);

    out << "    Info about all curves" << std::endl;
    curves.PrintCurves(out);
    out << "    Points and first derivative of all curves at t =PI/4" << std::endl;
    curves.PrintPointsAndDerivative(out);

    curves.CollectOnlyCircles();
    out << "    Info about only circles" << std::endl;
    curves.PrintCircles(out);

    out << "    Info about sorted circles" << std::endl;
    curves.SortCircles().PrintCircles(out);

    out << "    Total sum of circles raduii " << curves.ComputeTotalRadiusSum() << std::endl;
    out.close();
}