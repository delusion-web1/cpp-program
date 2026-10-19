#include<cmath>
#include"Trapezoid.h"
#include<iostream>
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
	return "梯形的上底为： " + to_string(top) + ",下底为： " + to_string(bottom) + "，高为： " + to_string(height) + "请算出面积和周长：";
}