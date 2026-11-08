#include "Shape.h"
#include "Circle.h"
#include "Rect.h"
#include "Triangle.h"
#include "Trapezoid.h"
#include"Parallelogram.h"
#include <string>

Shape* Shape::loadFromFile(ifstream& in)
{
	string type;
	in >> type;
	if (type == "Circle")
	{
		double r;
		in >> r;
		return new Circle(r);
	}
	else if (type == "Rect")
	{
		double w, h;
		in >> w >> h;
		return new Rect(w, h);
	}
	else if (type == "Triangle")
	{
		double a, b, c;
		in >> a >> b >> c;
		return new Triangle(a, b, c);
	}
	else if (type == "Trapezoid")
	{
		double t, b, h;
		in >> t >> b >> h;
		return new Trapezoid(t, b, h);
	}
	else if (type == "Parallelogram")
	{
		double b, h, s;
		in >> b >> h >> s;
		return new Parallelogram(b, h, s);
	}
	return nullptr;
}
