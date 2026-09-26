#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <iostream>
#include <string>
#include <cmath>
using namespace std;
class Triangle
{
private:
    int id;
    double a, b, c;
public:
    Triangle(int id_ = 0, double x = 3, double y = 4, double z = 5);
    void setId(int id_);//ÐÞ¸ÄÌâºÅ
    bool isLegal() const;
    double getArea() const;
    double getPerimeter() const;
    string getTriangleType() const;
    int getId() const {
        return id;
    };
    double getA() const {
        return a;
    }
    double getB() const {
        return b;
    }
    double getC() const {
        return c;
    }
    void showQuestionInfo() const;
};
#endif