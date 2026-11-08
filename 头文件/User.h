#ifndef USER_H
#define USER_H
#include<string>
#include<fstream>
using namespace std;
class User
{
private:
	string name;
	string password;
	int totalAnswered;//累计答题数
	int correctCount;//累计答对数
	int totalTime;//累计做题用时
public:
	User();
	User(string n, string pwd);
	string getName() const;
	string getPassword() const;
	int getTotalAnswered() const;
	int getCorrectCount() const;
	int getTotalTime() const;
	double getAccuracy() const;//正确率
	double getAvgTime() const;//平均每题用时
	bool checkPassword(const string& pwd) const;
	void addResult(int correct, int answered, int secs);//记录一次练习结果
	void saveToFile(ofstream& out) const;
	bool loadFromFile(ifstream& in);//判断是否读出用户的数据
};
#endif
