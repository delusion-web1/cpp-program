#include"Triangle.h"
#include<cmath>
Triangle::Triangle(double x, double y, double z) : a(x), b(y), c(z) {}
//用海论公式计算三角形面积
double Triangle::getArea() const
{
	double p = (a + b + c) / 2.0;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}
//计算三角形周长
double Triangle::getPerimeter() const
{
	return a + b + c;
}
string Triangle::showQuestion() const
{
	return "三角形的三边分别为： " + to_string(a) + "，" + to_string(b) + "，" + to_string(c) + "，请分别计算面积、周长：";
}
