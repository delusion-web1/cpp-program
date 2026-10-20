#ifndef RECT_H
#define RECT_H
#include"Shape.h"
class Rect : public Shape
{
private:
	double w, h;
public:
	Rect(double width, double height);
	double getArea() const override;
	double getPerimeter() const override;
	string showQuestion() const override;
	Shape* clone() const override;
};
#endif

