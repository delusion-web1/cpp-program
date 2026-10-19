#include "Question.h"
//静态成员类外初始化，题号从1开始
int Question::nextId = 1;
Question::Question(Shape* s)
    : id(nextId++), shape(s)
{
    correctArea = shape->getArea();
    correctPerimeter = shape->getPerimeter();
}
Question::~Question()//释放堆对象
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