#include"Shape.h"
#include"Rect.h"
#include<iostream>
using namespace std;
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
void Rect::showInfo() const
{
	cout << "矩形的宽为： " << w << ",高为： " << h << endl;
}
