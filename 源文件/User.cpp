#include "User.h"
User::User() : totalAnswered(0), correctCount(0), totalTime(0) {}
User::User(string n, string pwd) : name(n), password(pwd), totalAnswered(0), correctCount(0), totalTime(0) {}
string User::getName() const { return name; }
string User::getPassword() const { return password; }
int User::getTotalAnswered() const { return totalAnswered; }
int User::getCorrectCount() const { return correctCount; }
int User::getTotalTime() const { return totalTime; }
double User::getAccuracy() const
{
	if (totalAnswered == 0) return 0.0;
	return static_cast<double>(correctCount) / totalAnswered * 100.0;
}
double User::getAvgTime() const
{
	if (totalAnswered == 0) return 0.0;
	return static_cast<double>(totalTime) / totalAnswered;
}
bool User::checkPassword(const string& pwd) const
{
	return password == pwd;
}
void User::addResult(int correct, int answered, int secs)
{
	correctCount += correct;
	totalAnswered += answered;
	totalTime += secs;
}
void User::saveToFile(ofstream& out) const
{
	out << name << " " << password << " " << totalAnswered << " " << correctCount << " " << totalTime << endl;
}
bool User::loadFromFile(ifstream& in)
{
	in >> name >> password >> totalAnswered >> correctCount >> totalTime;
	return true;
}
