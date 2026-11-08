#ifndef QUESTION_H
#define QUESTION_H
#include "Shape.h"
#include <fstream>
using namespace std;
class Question
{
private:
	static int nextId;//所有题目共享计数器
	int id;
	Shape* shape;
	double correctArea;
	double correctPerimeter;
	Question();//私有默认构造，仅供从文件加载时使用
public:
	Question(Shape* s);
	Question(const Question& other);
	Question& operator=(const Question& other);
	~Question();
	int getId() const;
	double getCorrectArea() const;
	double getCorrectPeri() const;
	Shape* getShape() const;
	bool operator==(const Question& other) const;//操作符重载：题目内容相同视为同一题
	void saveToFile(ofstream& out) const;
	static Question* loadFromFile(ifstream& in);
	static void updateNextId(int newId);//重新登陆加载完后，题号自己更新到原来的下一个id,保证不和旧的题目撞题号，方便删除
};
#endif
