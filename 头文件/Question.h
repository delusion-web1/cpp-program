#ifndef QUESTION_H
#define QUESTION_H
#include "Shape.h"
class Question
{
private:
    static int nextId;
    int id;
    Shape* shape;
    double correctArea;
    double correctPerimeter;
public:
    Question(Shape* s);
    ~Question();
    int getId() const;
    double getCorrectArea() const;
    double getCorrectPeri() const;
    Shape* getShape() const;
};
#endif