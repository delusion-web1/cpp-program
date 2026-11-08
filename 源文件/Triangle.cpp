#include"Triangle.h"
#include<cmath>
#include<iomanip>
#include<iostream>
Triangle::Triangle(double x, double y, double z) : a(x), b(y), c(z) {}
double Triangle::getArea() const
{
	double p = (a + b + c) / 2.0;
	return sqrt(p * (p - a) * (p - b) * (p - c));
}
double Triangle::getPerimeter() const
{
	return a + b + c;
}
string Triangle::showQuestion() const
{
	return "三角形的三边分别为：" + to_string((int)a) + "，" + to_string((int)b) + "，" + to_string((int)c);
}
Shape* Triangle::clone() const
{
	return new Triangle(*this);
}
void Triangle::saveToFile(ofstream& out) const
{
	out << getShapeType() << " " << a << " " << b << " " << c << endl;
}
string Triangle::getShapeType() const
{
	return "Triangle";
}
void Triangle::printFormula() const
{
	cout << fixed << setprecision(2);
	double s = (a + b + c) / 2.0;
	cout << "  周长 = 三边之和 = " << a << " + " << b << " + " << c << " = " << getPerimeter() << endl;
	cout << "  面积 = 海伦公式 sqrt[s(s-a)(s-b)(s-c)]，半周长s=" << s << endl;
	cout << "        = sqrt[" << s << "*" << (s - a) << "*" << (s - b) << "*" << (s - c) << "] = " << getArea() << endl;
}

