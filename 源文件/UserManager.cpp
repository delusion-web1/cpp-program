#include "UserManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include <cmath>  
using namespace std;

bool cmpByAccuracy(const User& a, const User& b)
{
	if (fabs(a.getAccuracy() - b.getAccuracy()) > 0.0001)
		return a.getAccuracy() > b.getAccuracy();
	if (fabs(a.getAvgTime() - b.getAvgTime()) > 0.0001)
		return a.getAvgTime() < b.getAvgTime();
	return a.getName() < b.getName();
}
bool cmpByTime(const User& a, const User& b)
{
	if (fabs(a.getAvgTime() - b.getAvgTime()) > 0.0001)
		return a.getAvgTime() < b.getAvgTime();
	if (fabs(a.getAccuracy() - b.getAccuracy()) > 0.0001)
		return a.getAccuracy() > b.getAccuracy();
	return a.getName() < b.getName();
}

UserManager::UserManager(const string& f) : filename(f) {}

void UserManager::loadUsers()
{
	ifstream in(filename);
	if (!in.is_open()) return;
	int cnt;
	in >> cnt;
	for (int i = 0; i < cnt; i++)
	{
		User u;
		u.loadFromFile(in);
		users.push_back(u);
	}
	in.close();
}
void UserManager::saveUsers() const
{
	ofstream out(filename);
	if (!out.is_open()) return;
	out << users.size() << endl;
	for (auto u : users)
		u.saveToFile(out);
	out.close();
}
bool UserManager::login(const string& name, const string& pwd)
{
	for (auto& u : users)
		if (u.getName() == name && u.checkPassword(pwd)) return true;
	return false;
}
bool UserManager::registerUser(const string& name, const string& pwd)
{
	for (auto& u : users)
		if (u.getName() == name) return false;//用户名已存在
	if (!checkPasswordRule(pwd)) return false;//密码不符合规则
	users.push_back(User(name, pwd));
	saveUsers();
	return true;
}
bool UserManager::checkPasswordRule(const string& pwd) const
{
	if (pwd.length() < 6 || pwd.length() > 20)
	{
		cout << "密码长度需为6~20位！" << endl;
		return false;
	}
	bool hasLetter = false;
	bool hasDigit = false;
	for (size_t i = 0; i < pwd.length(); i++)
	{
		char c = pwd[i];
		if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) hasLetter = true;
		if (c >= '0' && c <= '9') hasDigit = true;
	}
	if (!hasLetter || !hasDigit)
	{
		cout << "密码必须同时包含字母和数字！" << endl;
		return false;
	}
	return true;
}
bool UserManager::deleteUser(const string& name, const string& pwd)
{
	for (auto it = users.begin(); it != users.end(); ++it)
	{
		if (it->getName() == name && it->checkPassword(pwd))
		{
			remove(("data/bank_" + name + ".txt").c_str());//同时删除该用户的题目存档
			users.erase(it);
			saveUsers();
			return true;
		}
	}
	return false;
}
void UserManager::addResult(const string& name, int correct, int answered, int secs)
{
	for (auto& u : users)
		if (u.getName() == name) { u.addResult(correct, answered, secs); break; }
	saveUsers();
}
void UserManager::showRankByAccuracy() const
{
	vector<User> tmp;
	for (auto& u : users)
		if (u.getTotalAnswered() > 0) tmp.push_back(u);
	if (tmp.empty()) { cout << "暂无做题记录，正确率排行榜为空" << endl; return; }
	sort(tmp.begin(), tmp.end(), cmpByAccuracy);
	cout << "\n===== 正确率排行榜=====" << endl;
	int rank = 1;
	for (auto& u : tmp)
	{
		cout << "第" << rank++ << "名：" << u.getName()
			<< "  正确率" << u.getAccuracy() << "%"
			<< "（答对" << u.getCorrectCount() << "/" << u.getTotalAnswered() << "题）"
			<< "  平均每题" << u.getAvgTime() << "秒" << endl;
	}
}
void UserManager::showRankByTime() const
{
	vector<User> tmp;
	for (auto& u : users)
		if (u.getTotalAnswered() > 0) tmp.push_back(u);
	if (tmp.empty()) { cout << "暂无做题记录，做题速度排行榜为空" << endl; return; }
	sort(tmp.begin(), tmp.end(), cmpByTime);
	cout << "\n===== 做题速度排行榜=====" << endl;
	int rank = 1;
	for (auto& u : tmp)
	{
		cout << "第" << rank++ << "名：" << u.getName()
			<< "  平均每题" << u.getAvgTime() << "秒"
			<< "（正确率" << u.getAccuracy() << "%）" << endl;
	}
}
