#ifndef CIRCLE_H
#define CIRCLE_H
#include"Shape.h"
class Circle : public Shape
{
private:
	double r;
public:
	Circle(double radius);
	double getArea() const override;
	double getPerimeter() const override;
	void showInfo() const override;
};

#endif