#include "Question.h"
#include <fstream>
using namespace std;
int Question::nextId = 1;
Question::Question(Shape* s)
	: id(nextId++), shape(s)
{
	correctArea = shape->getArea();
	correctPerimeter = shape->getPerimeter();
}
Question::Question() : id(0), shape(nullptr), correctArea(0), correctPerimeter(0) {}
Question::Question(const Question& other)//深拷贝
	: id(other.id),
	shape(other.shape ? other.shape->clone() : nullptr),
	correctArea(other.correctArea),
	correctPerimeter(other.correctPerimeter)
{
}
Question& Question::operator=(const Question& other)
{
	if (this != &other)
	{
		delete shape;
		shape = other.shape ? other.shape->clone() : nullptr;
		id = other.id;
		correctArea = other.correctArea;
		correctPerimeter = other.correctPerimeter;
	}
	return *this; //返回自身引用
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
bool Question::operator==(const Question& other) const
{
	return shape->showQuestion() == other.shape->showQuestion();//题目内容完全相同视为同一题
}
void Question::saveToFile(ofstream& out) const
{
	out << id << " " << correctArea << " " << correctPerimeter << endl;
	shape->saveToFile(out);//把图形对象写进文件里
}
Question* Question::loadFromFile(ifstream& in)
{
	Question* q = new Question();//新建一个空题目
	in >> q->id >> q->correctArea >> q->correctPerimeter;
	q->shape = Shape::loadFromFile(in);//从文件中加载图形对象
	updateNextId(q->id);//更新计数器
	return q;
}
void Question::updateNextId(int newId)
{
	if (newId >= nextId) nextId = newId + 1;//保证不和旧的题目撞题号，方便删除
}
