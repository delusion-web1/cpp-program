#include"Rect.h"
Rect::Rect(double width, double height) : w(width), h(height) {}
//计算矩形的面积
double Rect::getArea() const
{
	return w * h;
}
//计算矩形的周长
double Rect::getPerimeter() const
{
	return 2 * (w + h);
}
string Rect::showQuestion() const
{
	return "矩形的宽=" + to_string(w) + "，高=" + to_string(h) + "，请分别计算面积、周长：";
}
