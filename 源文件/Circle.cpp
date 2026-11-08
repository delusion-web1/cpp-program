#include"Circle.h"
#include<iostream>
#include<iomanip>
#define PI 3.14
Circle::Circle(double radius) : r(radius) {}//构造函数，初始化
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
	return "圆形的半径=" + to_string((int)r);
}
Shape* Circle::clone() const
{
	return new Circle(*this);
}
void Circle::saveToFile(ofstream& out) const//写入
{
	out << getShapeType() << " " << r << endl;
}
string Circle::getShapeType() const
{
	return "Circle";
}
void Circle::printFormula() const
{
	cout << fixed << setprecision(2);
	cout << "  面积 = pi * r^2 = 3.14 * " << r << "^2 = " << getArea() << endl;
	cout << "  周长 = 2 * pi * r = 2 * 3.14 * " << r << " = " << getPerimeter() << endl;
}