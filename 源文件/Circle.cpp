#include"Circle.h"
#define PI 3.14
Circle::Circle(double radius) : r(radius) {}
double Circle::getArea() const
{
	return PI * r * r;
}
double Circle::getPerimeter() const
{
	return 2 * PI * r;
}
string Circle::showQuestion() const
{
	return "圆形的半径=" + to_string(r);
}
Shape* Circle::clone() const
{
	return new Circle(*this);
}