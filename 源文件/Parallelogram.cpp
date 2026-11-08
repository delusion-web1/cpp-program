#include"Parallelogram.h"
#include<iostream>
#include<iomanip>
using namespace std;
Parallelogram::Parallelogram(double b, double h, double s) : bottom(b), height(h), side(s) {}
double Parallelogram::getArea() const
{
	return bottom * height;
}
double Parallelogram::getPerimeter() const
{
	return 2 * (bottom + side);
}
string Parallelogram::showQuestion() const
{
	return "平行四边形的底=" + to_string((int)bottom) + "，高=" + to_string((int)height) + "，斜边=" + to_string((int)side);
}
Shape* Parallelogram::clone() const
{
	return new Parallelogram(*this);
}
void Parallelogram::saveToFile(ofstream& out) const
{
	out << getShapeType() << " " << bottom << " " << height << " " << side << endl;
}
string Parallelogram::getShapeType() const
{
	return "Parallelogram";
}
void Parallelogram::printFormula() const
{
	cout << fixed << setprecision(2);
	cout << "  面积 = 底 × 高 = " << bottom << " × " << height << " = " << getArea() << endl;
	cout << "  周长 = 2×(底+斜边) = 2×(" << bottom << " + " << side << ") = " << getPerimeter() << endl;
}
