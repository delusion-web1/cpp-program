#include "QuestionBank.h"
#include <iostream>
#include<cmath>
using namespace std;
void QuestionBank::startQuiz()
{
    int correct = 0;
    int total = quesList.size();
    if (total == 0)
    {
        cout << "题库中没有题目，请先添加题目!" << endl;
        return;
    }
    for (auto& q : quesList)
    {
        cout << "题号: " << q.getId() << ", 三边长度: " << q.getA() << ", " << q.getB() << ", " << q.getC() << endl;
        double userPerimeter, userArea;
        string userType;
        cout << "请输入你计算的周长和面积: ";
        cin >> userPerimeter >> userArea;
        cout << "输入你判断的三角形类型：";
        cin >> userType;
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "输入无效，本题跳过" << endl;
            continue;
        }
        bool perimeterCorrect = fabs(userPerimeter - q.getPerimeter()) < 1e-6;
        bool areaCorrect = fabs(userArea - q.getArea()) < 1e-6;
        bool typeCorrect = (userType == q.getTriangleType());
        if (perimeterCorrect && areaCorrect && typeCorrect)
        {
            cout << "回答正确!" << endl;
            correct++;
        }
        else
        {
            cout << "回答错误!" << endl;
            cout << "正确周长: " << q.getPerimeter() << ", 正确面积 : " << q.getArea() << ", 正确类型: " << q.getTriangleType() << endl;
        }
    }
    totalScore = correct;
    avgScore = total > 0 ? (double)correct / total : 0;
    cout << "==========成绩报告===========" << endl;
    cout << "总题数: " << total << endl;
    cout << " 正确题数: " << correct << endl;
    cout << " 总分: " << totalScore << endl;
    cout << "平均分: " << avgScore << endl;
}
QuestionBank::QuestionBank(const std::string& name)
    :bankName(name), totalScore(0), avgScore(0)
{
}
bool QuestionBank::addQuestion(const Triangle& q)
{
    quesList.push_back(q);
    return true;
}
bool QuestionBank::delQuestionById(int Id)
{
    for (auto it = quesList.begin(); it != quesList.end(); ++it)
    {
        if (it->getId() == Id)
        {
            quesList.erase(it);
            cout << "题号为 " << Id << " 的题目已删除" << endl;
            return true;
        }
    }
    cout << "题号为 " << Id << " 的题目不存在" << endl;
    return false;
}
void QuestionBank::showAllQuestion() const
{
    cout << "题库名称: " << bankName << endl;
    cout << "题目总数: " << quesList.size() << endl;
    for (const auto& q : quesList)
    {
        q.showQuestionInfo();
    }
}
int QuestionBank::getCount() const
{
    return (int)quesList.size();
}
bool QuestionBank::hasQuestions(int id) const
{
    for (const auto& q : quesList)
    {
        if (q.getId() == id)
            return true;
    }
    return false;
}