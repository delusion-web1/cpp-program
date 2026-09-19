#ifndef TRIANGLE_H
#define TRIANGLE_H
#include"Shape.h"
class Triangle :public Shape
{
private:
	double a, b, c;
public:
	Triangle(double x, double y, double z);
	double getArea() const override;
	double getPerimeter() const override;
	void showInfo() const override;
};
#endif