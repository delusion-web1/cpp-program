#ifndef PARALLELOGRAM_H
#define PARALLELOGRAM_H
#include"Shape.h"
class Parallelogram :public Shape//平行四边形
{
private:
	double bottom;
	double height;
	double side;
public:
	Parallelogram(double b, double h, double s);
	double getArea() const override;
	double getPerimeter() const override;
	string showQuestion() const override;
	Shape* clone() const override;
	void saveToFile(ofstream& out) const override;
	string getShapeType() const override;
	void printFormula() const override;
};
#endif
