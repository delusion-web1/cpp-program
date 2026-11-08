#ifndef QUESTIONBANK_H
#define QUESTIONBANK_H
#include <vector>
#include "Question.h"
#include<string>
#include <fstream>
using namespace std;
class QuestionBank
{
private:
	vector<Question*> history;//做题历史
	vector<Question*> quesList;
	vector<Question*> wrongList;
	string bankName;
	double totalScore;
	int FinishCount;
	int totalAnswered;//累计答题数
	int correctCount;//累计答对数
public:
	QuestionBank(string name);
	QuestionBank();
	QuestionBank(const QuestionBank& other);
	QuestionBank& operator=(const QuestionBank& other);
	~QuestionBank();
	string getBankName() const { return bankName; }
	Question* RandomQ(int forceType = -1);//forceType指定图形类型(-1=随机)
	void showAllQuestion() const;//打印所有题目格式
	int startAns();//返回本次答对数
	void reviewHistory() const;//回看：可看上一题/下一题
	void showWrongAnalysis() const;//错题按图形类型分析
	void reviewWrongQuestions() const;
	int reviewWrongRetry();//错题重练：答对自动移出错题本
	bool deleteQuestion(int qid);
	void resetRecords();//清空历史记录与错题本
	void generateN(int n, int type = -1);//产生几道题
	double getAccuracy() const;//返回累计正确率
	int getFinishCount() const;//返回最近一次答题的题数
	bool saveData(const string& filename) const;
	bool loadData(const string& filename, bool showMsg = false);//静默登录
};
#endif
