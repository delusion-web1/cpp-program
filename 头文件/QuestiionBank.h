#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H
#include <vector>
#include <string>
#include "Triangle.h"
class QuestionBank
{
private:
    std::string bankName;
    std::vector<Triangle> quesList;
    double totalScore;
    double avgScore;
public:
    QuestionBank(const std::string& name);
    bool addQuestion(const Triangle& q);
    bool delQuestionById(int Id);
    void showAllQuestion() const;
    int getCount() const;
    bool hasQuestions(int id) const;
    void startQuiz();//做题，算周长和面积
};

#endif
