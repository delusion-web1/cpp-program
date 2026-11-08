#include"Rect.h"
#include<iostream>
#include<iomanip>
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
	return "矩形的宽=" + to_string((int)w) + " 高=" + to_string((int)h);
}
Shape* Rect::clone() const
{
	return new Rect(*this);
}
void Rect::saveToFile(ofstream& out) const
{
	out << getShapeType() << " " << w << " " << h << endl;
}
string Rect::getShapeType() const
{
	return "Rect";
}
void Rect::printFormula() const
{
	cout << fixed << setprecision(2);
	cout << "  面积 = 宽 * 高 = " << w << " * " << h << " = " << getArea() << endl;
	cout << "  周长 = 2*(宽+高) = 2*(" << w << " + " << h << ") = " << getPerimeter() << endl;
}

