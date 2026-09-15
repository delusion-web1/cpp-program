#ifndef SHAPE_H
#define SHAPE_H 
class Shape
{
public:
	virtual double getArea() const = 0; //ÇóĂćťý
	virtual double getPerimeter() const = 0;//ÇóÖÜł¤
	virtual ~Shape() {};
};
#endif
