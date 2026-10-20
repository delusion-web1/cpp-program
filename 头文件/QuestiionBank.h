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
    vector<Question*> wrongList;
    string bankName;
    double totalScore;
    int FinishCount;
public:
    QuestionBank(string name);
    QuestionBank();
    QuestionBank(const QuestionBank& other);
    QuestionBank& operator=(const QuestionBank& other);
    ~QuestionBank();
    string getBankName() const
    {
        return bankName;
    }
    Question* RandomQ();//生成随机题目
    void showAllQuestion() const;
    void startAns();//开始答题
    void reviewHistory() const;
    void reviewWrongQuestions() const;
    bool deleteQuestion(int qid);
    void generateN(int n);
};
#endif