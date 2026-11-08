#include<cmath>
#include"Trapezoid.h"
#include<iostream>
#include<iomanip>
using namespace std;
Trapezoid::Trapezoid(double t, double b, double h) :top(t), bottom(b), height(h) {}
double Trapezoid::getArea() const
{
	return (top + bottom) * height / 2.0;
}
double Trapezoid::getPerimeter() const
{
	double yao = sqrt(pow((bottom - top) / 2.0, 2) + pow(height, 2));
	return top + bottom + 2 * yao;
}
string Trapezoid::showQuestion() const {
	return "梯形的上底为：" + to_string((int)top) + " 下底为：" + to_string((int)bottom) + " 高为：" + to_string((int)height);
}
Shape* Trapezoid::clone() const
{
	return new Trapezoid(*this);
}
void Trapezoid::saveToFile(ofstream& out) const
{
	out << getShapeType() << " " << top << " " << bottom << " " << height << endl;
}
string Trapezoid::getShapeType() const
{
	return "Trapezoid";
}
void Trapezoid::printFormula() const
{
	cout << fixed << setprecision(2);
	double side = sqrt(((bottom - top) / 2.0) * ((bottom - top) / 2.0) + height * height);
	cout << "  面积 = (上底+下底)*高/2 = (" << top << " + " << bottom << ") * " << height << " / 2 = " << getArea() << endl;
	cout << "  周长 = 上底+下底+两腰 = " << top << " + " << bottom << " + " << side << " + " << side << " = " << getPerimeter() << endl;
}
