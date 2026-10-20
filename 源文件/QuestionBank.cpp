#include "QuestionBank.h"
#include "Circle.h"
#include "Rect.h"
#include "Triangle.h"
#include "Trapezoid.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
QuestionBank::QuestionBank(string name)
	: bankName(name), totalScore(0), FinishCount(0)
{
}
QuestionBank::QuestionBank()
	: bankName("默认几何题库"), totalScore(0), FinishCount(0)
{
}
QuestionBank::QuestionBank(const QuestionBank& other)
	: bankName(other.bankName), totalScore(other.totalScore), FinishCount(other.FinishCount)
{
	for (auto q : other.quesList)
		quesList.push_back(new Question(*q));
	for (auto q : other.history)
		history.push_back(new Question(*q));
	for (auto q : other.wrongList)
		wrongList.push_back(new Question(*q));
}
QuestionBank& QuestionBank::operator=(const QuestionBank& other)
{
	if (this != &other)
	{
		for (auto q : quesList) delete q;
		for (auto q : history) delete q;
		for (auto q : wrongList) delete q;
		quesList.clear();
		history.clear();
		wrongList.clear();
		bankName = other.bankName;
		totalScore = other.totalScore;
		FinishCount = other.FinishCount;
		for (auto q : other.quesList)
			quesList.push_back(new Question(*q));
		for (auto q : other.history)
			history.push_back(new Question(*q));
		for (auto q : other.wrongList)
			wrongList.push_back(new Question(*q));
	}
	return *this;
}

QuestionBank::~QuestionBank()
{
	for (auto q : quesList) delete q;
	for (auto q : history) delete q;
	for (auto q : wrongList) delete q;
	quesList.clear();
	history.clear();
	wrongList.clear();
}

// 随机生成一道题：0圆，1矩形，2三角形，3梯形
Question* QuestionBank::RandomQ()
{
	int type = rand() % 4;
	Shape* sp = nullptr;

	switch (type)
	{
	case 0:
	{
		double r = 1 + rand() % 10;
		sp = new Circle(r);
		break;
	}
	case 1:
	{
		double w = 2 + rand() % 8;
		double h = 2 + rand() % 8;
		sp = new Rect(w, h);
		break;
	}
	case 2:
	{
		double a, b, c;
		while (true)
		{
			a = 3 + rand() % 5;
			b = 4 + rand() % 6;
			c = 5 + rand() % 7;
			if (a + b > c && a + c > b && b + c > a)
			{
				sp = new Triangle(a, b, c);
				break;
			}
		}
		break;
	}
	case 3:
	{
		double top = 1 + rand() % 12;
		double bot = 6 + rand() % 15;
		double hi = 2 + rand() % 7;
		sp = new Trapezoid(top, bot, hi);
		break;
	}
	}
	return new Question(sp);
}
void QuestionBank::generateN(int n)
{
	for (int i = 0; i < n; i++)
	{
		Question* q = RandomQ();
		quesList.push_back(q);
	}
	cout << "成功生成 " << n << " 道随机几何题目！" << endl;
}
void QuestionBank::showAllQuestion() const
{
	cout << "\n=======【" << bankName << "】全部题目列表=======" << endl;
	for (auto q : quesList)
	{
		cout << "题目" << q->getId() << "：" << q->getShape()->showQuestion() << endl;
	}
}
void QuestionBank::startAns()
{
	totalScore = 0;
	FinishCount = 0;
	if (quesList.empty())
	{
		cout << "题库为空，请先生成题目！" << endl;
		return;
	}
	int remain = 0;
	for (auto q : quesList)
	{
		bool done = false;
		for (auto h : history)
		{
			if (h->getId() == q->getId()) { done = true; break; }
		}
		if (!done) remain++;
	}
	if (remain == 0)
	{
		cout << "所有题目都已经做过了！请先重新生成新题目。" << endl;
		return;
	}
	cout << "\n----------开始练习答题（剩余" << remain << "道未做）----------" << endl;
	for (auto q : quesList)
	{
		bool done = false;
		for (auto h : history)
		{
			if (h->getId() == q->getId()) { done = true; break; }
		}
		if (done) continue;

		double userArea, userPeri;
		cout << "\n【题目" << q->getId() << "】" << q->getShape()->showQuestion() << endl;
		cout << "请输入你计算的面积、周长：";
		cin >> userArea >> userPeri;

		FinishCount++;
		history.push_back(new Question(*q));
		bool areaRight = fabs(userArea - q->getCorrectArea()) < 1e-3;
		bool periRight = fabs(userPeri - q->getCorrectPeri()) < 1e-3;

		if (areaRight && periRight)
		{
			cout << "回答正确！本题得10分" << endl;
			totalScore += 10;
		}
		else
		{
			cout << "回答错误！正确面积：" << q->getCorrectArea() << " ，正确周长：" << q->getCorrectPeri() << endl;
			bool alreadyIn = false;
			for (auto w : wrongList)
			{
				if (w->getId() == q->getId()) { alreadyIn = true; break; }
			}
			if (!alreadyIn)
			{
				wrongList.push_back(new Question(*q));
			}
		}
	}
	cout << "\n========练习结束========" << endl;
	cout << "本次作答：" << FinishCount << " 道题目" << endl;
	cout << "你的总得分：" << totalScore << " 分" << endl;
	if (FinishCount > 0)
	{
		double avg = static_cast<double>(totalScore) / FinishCount;
		cout << "平均每题得分：" << avg << endl;
	}
}
void QuestionBank::reviewHistory() const
{
	if (history.empty())
	{
		cout << "你还没有做过任何题目！" << endl;
		return;
	}
	cout << "\n=======回看已完成的题目=======" << endl;
	for (auto q : history)
	{
		cout << "题目" << q->getId() << " " << q->getShape()->showQuestion();
		cout << "\n标准答案 面积=" << q->getCorrectArea() << " 周长=" << q->getCorrectPeri() << endl;
		cout << endl;
	}
}
void QuestionBank::reviewWrongQuestions() const
{
	if (wrongList.empty())
	{
		cout << "太棒了！你还没有错题。" << endl;
		return;
	}
	cout << "\n=======错题本=======" << endl;
	for (auto q : wrongList)
	{
		cout << "题目" << q->getId() << " " << q->getShape()->showQuestion();
		cout << "\n正确答案 面积=" << q->getCorrectArea() << " 周长=" << q->getCorrectPeri() << endl;
		cout << endl;
	}
}
bool QuestionBank::deleteQuestion(int qid)
{
	for (auto it = quesList.begin(); it != quesList.end(); ++it)
	{
		if ((*it)->getId() == qid)
		{
			delete* it;
			quesList.erase(it);
			cout << "题目" << qid << "已删除！" << endl;
			return true;
		}
	}
	cout << "未找到编号为" << qid << "的题目！" << endl;
	return false;
}