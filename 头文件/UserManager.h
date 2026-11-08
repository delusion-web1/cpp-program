#ifndef USERMANAGER_H
#define USERMANAGER_H
#include <vector>
#include <string>
#include "User.h"
using namespace std;
class UserManager
{
private:
	vector<User> users;
	string filename;//用户信息文件 data/users.txt
	bool checkPasswordRule(const string& pwd) const;
public:
	UserManager(const string& f);
	void loadUsers();
	void saveUsers() const;
	bool login(const string& name, const string& pwd);
	bool registerUser(const string& name, const string& pwd);
	bool deleteUser(const string& name, const string& pwd);//注销
	void addResult(const string& name, int correct, int answered, int secs);//累计用户成绩
	void showRankByAccuracy() const;//正确率排行榜
	void showRankByTime() const;//做题速度排行榜
};
#endif
