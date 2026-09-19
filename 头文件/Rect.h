#ifndef RECT_H
#define RECT_H
#include"Shape.h"
class Rect : public Shape
{
private:
public:
	Rect(double width, double height);
	double getArea() const override;
	double getPerimeter() const override;
	void showInfo() const override;
};

#endif
