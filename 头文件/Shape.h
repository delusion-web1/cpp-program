#ifndef SHAPE_H
#define SHAPE_H
#include<string>
#include<fstream>
using namespace std;
class Shape
{
public:
	virtual double getArea() const = 0;
	virtual double getPerimeter() const = 0;
	virtual string showQuestion() const = 0;
	virtual Shape* clone() const = 0;
	virtual void saveToFile(ofstream& out) const = 0;
	virtual string getShapeType() const = 0;
	virtual void printFormula() const = 0;//展示解题步骤
	virtual ~Shape() {};//虚析构防内存泄漏
	static Shape* loadFromFile(ifstream& in);//从文件中加载，静态函数，根据type类型自己new出对象
};
#endif
