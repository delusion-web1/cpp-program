#include "Question.h"
int Question::nextId = 1;
Question::Question(Shape* s)
	: id(nextId++), shape(s)
{
	correctArea = shape->getArea();
	correctPerimeter = shape->getPerimeter();
}
Question::Question(const Question& other)
	: id(other.id),
	shape(other.shape ? other.shape->clone() : nullptr),
	correctArea(other.correctArea),
	correctPerimeter(other.correctPerimeter)
{
}
Question& Question::operator=(const Question& other)
{
	if (this != &other)          // 防止自己给自己赋值
	{
		delete shape;
		shape = other.shape ? other.shape->clone() : nullptr;
		id = other.id;
		correctArea = other.correctArea;
		correctPerimeter = other.correctPerimeter;
	}
	return *this;
}
Question::~Question()
{
	delete shape;
}
int Question::getId() const
{
	return id;
}
double Question::getCorrectArea() const
{
	return correctArea;
}
double Question::getCorrectPeri() const
{
	return correctPerimeter;
}
Shape* Question::getShape() const
{
	return shape;
}