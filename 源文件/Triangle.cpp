#include "Triangle.h"
#include<algorithm>
#include<cmath>
using namespace std;
Triangle::Triangle(int id_, double x, double y, double z)
    :id(id_), a(x), b(y), c(z)
{
}
void Triangle::setId(int id_)
{
    id = id_;
}
bool Triangle::isLegal() const
{
    return (a > 0 && b > 0 && c > 0) && (a + b > c) && (a + c > b) && (b + c > a);
}
double Triangle::getArea() const
{
    if (!isLegal()) return -1;
    double p = (a + b + c) / 2.0;
    return sqrt(p * (p - a) * (p - b) * (p - c));
}
double Triangle::getPerimeter() const
{
    if (!isLegal()) return -1;
    return a + b + c;
}
string Triangle::getTriangleType() const
{
    if (!isLegal()) return "不是合法三角形";
    const double eps = 1e-6;
    double maxSide = max({ a, b, c });
    double sumSq;//另外两条边的平方和
    if (fabs(maxSide - a) < eps)
    {
        sumSq = b * b + c * c;
    }
    else if (fabs(maxSide - b) < eps)
    {
        sumSq = a * a + c * c;
    }
    else
    {
        sumSq = a * a + b * b;
    }
    if (fabs(a - b) < eps && fabs(b - c) < eps)
        return "等边三角形";
    else if (fabs(a - b) < eps || fabs(b - c) < eps || fabs(a - c) < eps)
    {
        if (fabs(sumSq - maxSide * maxSide) < eps)
            return "等腰直角三角形";
        else if (sumSq > maxSide * maxSide)
            return "等腰锐角三角形";
        else
            return "等腰钝角三角形";
    }
    else
    {
        if (fabs(sumSq - maxSide * maxSide) < eps)
            return "直角三角形";
        else if (sumSq > maxSide * maxSide)
            return "锐角三角形";
        else
            return "钝角三角形";
    }
}
void Triangle::showQuestionInfo() const
{
    cout << "【题目" << id << "】三边："
        << a << "  " << b << "  " << c << endl;
    if (isLegal())
    {
        cout << "    周长：" << getPerimeter()
            << "  面积：" << getArea()
            << "  类型：" << getTriangleType() << std::endl;
    }
    else
    {
        cout << "    该三边不能构成三角形！" << endl;
    }
}