#ifndef SHAPE_H
#define SHAPE_H 
class Shape
{
public:
	virtual double getArea() const = 0; //求面积
	virtual double getPerimeter() const = 0;//求周长
	virtual ~Shape() {};
};
#endif
