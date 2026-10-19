#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H
#include <vector>
#include "Question.h"
#include<string>
using namespace std;
class QuestionBank//题库
{
private:
    vector<Question*> history;//做题历史
    vector<Question*> quesList;
    string bankName;
    double totalScore;
    int FinishCount;
public:
    QuestionBank(string name);
    QuestionBank();
    ~QuestionBank();
    Question* RandomQ();//生成随机题目
    void showAllQuestion() const;
    void startAns();//开始答题
    void reviewHistory() const;
    void generateN(int n);
};
#endif