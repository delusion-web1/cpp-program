#ifndef CIRCLE_H
#define CIRCLE_H
#include"Shape.h"
class Circle : public Shape
{
private:
	double r;
public:
	Circle(double radius);//构造函数声明
	double getArea() const override;
	double getPerimeter() const override;
	string showQuestion() const override;
	Shape* clone() const override;
	void saveToFile(ofstream& out) const override;
	string getShapeType() const override;
	void printFormula() const override;
};
#endif
