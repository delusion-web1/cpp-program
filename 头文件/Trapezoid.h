#ifndef TRAPEZOID_H
#define TRAPEZOID_H
#include"Shape.h"
class Trapezoid :public Shape
{
private:
	double top;
	double bottom;
	double height;
public:
	Trapezoid(double t, double b, double h);
	double getArea() const override;
	double getPerimeter() const override;
	string showQuestion() const override;
};
#endif
