#include"Shape.h"
#include"Circle.h"
#include<iostream>
using namespace std;
#define PI 3.14159
Circle::Circle(double radius) : r(radius) {}
//计算圆的面积
double Circle::getArea() const
{
	return PI * r * r;
}
//计算圆的周长
double Circle::getPerimeter() const
{
	return 2 * PI * r;
}
void Circle::showInfo() const
{
	cout << "圆形半径为： " << r << endl;
}