#include"Rect.h"
Rect::Rect(double width, double height) : w(width), h(height) {}
double Rect::getArea() const
{
	return w * h;
}
double Rect::getPerimeter() const
{
	return 2 * (w + h);
}
string Rect::showQuestion() const
{
	return "¾ØÐÎµÄ¿í=" + to_string(w) + "£¬¸ß=" + to_string(h);
}
Shape* Rect::clone() const
{
	return new Rect(*this);
}
