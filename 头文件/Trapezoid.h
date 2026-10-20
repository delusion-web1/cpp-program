#ifndef TRAPEZOID_H
#define TRAPEZOID_H
#include"Shape.h"
class Trapezoid :public Shape//仅仅是指等腰梯形
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
	Shape* clone() const override;
};
#endif
