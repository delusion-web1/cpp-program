#include"Shape.h"
#include"Triangle.h"
#include<cmath>
Triangle::Triangle(double x,double y,double z):a(x),b(y),c(z){}
//用海论公式计算三角形面积
double Triangle::getArea() const
{
	double p = (a + b + c) / 2;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}
//计算三角形周长
double Triangle :: getPerimeter() const
{
	return a + b + c;
}
