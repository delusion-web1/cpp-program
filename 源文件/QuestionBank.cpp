#include "QuestionBank.h"
#include"Circle.h"
#include"Rect.h"
#include"Triangle.h"
#include"Trapezoid.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
QuestionBank::QuestionBank(string name)
    : bankName(name), totalScore(0), FinishCount(0)
{
    srand((unsigned)time(NULL));//设随机种子
}
QuestionBank::QuestionBank()
    : bankName("默认几何题库"), totalScore(0), FinishCount(0)
{
    srand((unsigned)time(NULL));
}
QuestionBank::~QuestionBank()
{
    for (auto q : quesList)
    {
        delete q;
    }
    quesList.clear();
    history.clear();
}
Question* QuestionBank::RandomQ()
{
    int type = rand() % 4; //0圆，1矩形，2三角形，3梯形
    Shape* sp = nullptr;

    switch (type)
    {
    case 0:
    {
        double r = 1 + rand() % 6;
        sp = new Circle(r);
        break;
    }
    case 1:
    {
        double w = 2 + rand() % 5;
        double h = 2 + rand() % 5;
        sp = new Rect(w, h);
        break;
    }
    case 2:
    {
        double a = 3, b = 4, c = 5; //3‑4‑5直角三角形，保证合法
        sp = new Triangle(a, b, c);
        break;
    }
    case 3:
    {
        double top = 2, bot = 6, hi = 3;
        sp = new Trapezoid(top, bot, hi);
        break;
    }
    }
    return new Question(sp);
}

//循环生成n道随机题目加入题库
void QuestionBank::generateN(int n)
{
    for (int i = 0; i < n; i++)
    {
        Question* q = RandomQ();
        quesList.push_back(q);
    }
    cout << "成功生成 " << n << " 道随机几何题目！" << endl;
}

//打印题库所有题目
void QuestionBank::showAllQuestion() const
{
    cout << "\n=======【" << bankName << "】全部题目列表=======" << endl;
    for (auto q : quesList)
    {
        cout << "题目" << q->getId() << "：" << q->getShape()->showQuestion() << endl;
    }
}

//开始答题（原startQuiz，改名starAns，无错题）
void QuestionBank::startAns()
{
    totalScore = 0;
    FinishCount = 0;
    history.clear();

    if (quesList.empty())
    {
        cout << "题库为空，请先生成题目！" << endl;
        return;
    }

    cout << "\n----------开始练习答题----------" << endl;
    for (auto q : quesList)
    {
        double userArea, userPeri;
        cout << "\n【题目" << q->getId() << "】" << q->getShape()->showQuestion() << endl;
        cout << "请输入你计算的面积、周长：";
        cin >> userArea >> userPeri;

        FinishCount++;
        history.push_back(q);

        //浮点数不能直接==比较，允许0.001的误差
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
        }
    }

    cout << "\n========练习结束========" << endl;
    cout << "一共作答：" << FinishCount << " 道题目" << endl;
    cout << "你的总得分：" << totalScore << " 分" << endl;
    double avg = static_cast<double>(totalScore) / FinishCount;
    cout << "平均每题得分：" << avg << endl;
}

//回看已经做过的全部题目与标准答案
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
        cout << " 标准答案 面积=" << q->getCorrectArea() << " 周长=" << q->getCorrectPeri() << endl;
    }
}