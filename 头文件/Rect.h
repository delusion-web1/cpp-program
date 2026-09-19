#ifndef RECT_H
#define RECT_H
#include"Shape.h"
class Rect : public Shape
{
private:
	double w, h;//¿íºÍ¸ß
public:
	Rect(double width, double height);
	double getArea() const override;
	double getPerimeter() const override;
	void showInfo() const override;
};

#endif