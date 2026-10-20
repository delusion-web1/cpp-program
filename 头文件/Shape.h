#ifndef SHAPE_H
#define SHAPE_H
#include<string>
using namespace std;
class Shape
{
public:
	virtual double getArea() const = 0; //纯虚函数，Shape类是抽象类，不能实例化
	virtual double getPerimeter() const = 0;
	virtual string showQuestion() const = 0;//显示图形信息
	virtual Shape* clone() const = 0;
	virtual ~Shape() {};
};
#endif
