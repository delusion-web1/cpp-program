#include "QuestionBank.h"
#include "Circle.h"
#include "Rect.h"
#include "Triangle.h"
#include "Trapezoid.h"
#include "Parallelogram.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;
QuestionBank::QuestionBank(string name)
	: bankName(name), totalScore(0), FinishCount(0), totalAnswered(0), correctCount(0)
{
}
QuestionBank::QuestionBank()
	: bankName("默认几何题库"), totalScore(0), FinishCount(0), totalAnswered(0), correctCount(0)
{
}
QuestionBank::QuestionBank(const QuestionBank& other)
	: bankName(other.bankName), totalScore(other.totalScore), FinishCount(other.FinishCount),
	totalAnswered(other.totalAnswered), correctCount(other.correctCount)
{
	for (auto q : other.quesList)
		quesList.push_back(new Question(*q));
	for (auto q : other.history)
		history.push_back(new Question(*q));
	for (auto q : other.wrongList)
		wrongList.push_back(new Question(*q));
}
QuestionBank& QuestionBank::operator=(const QuestionBank& other)
{
	if (this != &other)
	{
		for (auto q : quesList) delete q;
		for (auto q : history) delete q;
		for (auto q : wrongList) delete q;
		quesList.clear();
		history.clear();
		wrongList.clear();
		bankName = other.bankName;
		totalScore = other.totalScore;
		FinishCount = other.FinishCount;
		totalAnswered = other.totalAnswered;
		correctCount = other.correctCount;
		for (auto q : other.quesList)
			quesList.push_back(new Question(*q));
		for (auto q : other.history)
			history.push_back(new Question(*q));
		for (auto q : other.wrongList)
			wrongList.push_back(new Question(*q));
	}
	return *this;
}

QuestionBank::~QuestionBank()
{
	for (auto q : quesList) delete q;
	for (auto q : history) delete q;
	for (auto q : wrongList) delete q;
	quesList.clear();
	history.clear();
	wrongList.clear();
}

Question* QuestionBank::RandomQ(int forceType)
{
	int type = (forceType >= 0 && forceType <= 4) ? forceType : rand() % 5;
	Shape* sp = nullptr;
	switch (type)
	{
	case 0:
	{
		double r = 1 + rand() % 10;
		sp = new Circle(r);
		break;
	}
	case 1:
	{
		double w = 2 + rand() % 8;
		double h = 2 + rand() % 8;
		sp = new Rect(w, h);
		break;
	}
	case 2:
	{
		double a, b, c;
		while (true)
		{
			a = 3 + rand() % 5;
			b = 4 + rand() % 6;
			c = 5 + rand() % 7;
			if (a + b > c && a + c > b && b + c > a)
			{
				sp = new Triangle(a, b, c);
				break;
			}
		}
		break;
	}
	case 3:
	{
		double top = 1 + rand() % 12;
		double bot = 6 + rand() % 15;
		double hi = 2 + rand() % 7;
		sp = new Trapezoid(top, bot, hi);
		break;
	}
	case 4:
	{
		double b = 2 + rand() % 9;   //底 2~10
		double h = 2 + rand() % 7;   //高 2~8
		double s;
		while (true)
		{
			s = 3 + rand() % 10;     //斜边 3~12
			if (s > h) break;        //斜边必须大于高，几何上才成立
		}
		sp = new Parallelogram(b, h, s);
		break;
	}
	}
	return new Question(sp);
}
void QuestionBank::generateN(int n, int type)
{
	int added = 0;
	int tryCount = 0;
	while (added < n && tryCount < n * 200)
	{
		tryCount++;
		Question* q = RandomQ(type);
		bool dup = false;
		for (auto existing : quesList)
		{
			if (*existing == *q) { dup = true; break; }//内容相同则重新生成
		}
		if (dup)
		{
			delete q;//丢弃重复题
			continue;
		}
		quesList.push_back(q);
		added++;
	}
	cout << "成功生成 " << added << " 道随机题目！" << endl;
	if (added < n)
	{
		cout << "（提示：可用组合已用尽，实际生成 " << added << " 道）" << endl;
	}
}
void QuestionBank::showAllQuestion() const
{
	cout << "\n=======【" << bankName << "】全部题目列表=======" << endl;
	for (auto q : quesList)
	{
		cout << "题目" << q->getId() << "：" << q->getShape()->showQuestion() << endl;
	}
}
int QuestionBank::startAns()
{
	totalScore = 0;
	FinishCount = 0;
	if (quesList.empty())
	{
		cout << "题库为空，请先生成题目！" << endl;
		return 0;
	}
	int correctThis = 0;//本次答对数
	int remain = 0;
	for (auto q : quesList)
	{
		bool done = false;//假设题没做过
		for (auto h : history)//遍历历史记录
		{
			if (*h == *q) { done = true; break; }
		}
		if (!done) remain++;//没做过，数目加1
	}
	if (remain == 0)
	{
		cout << "所有题目都已经做过了！请先重新生成新题目。" << endl;
		return 0;
	}
	cout << "\n----------开始练习答题（剩余" << remain << "道未做）----------" << endl;
	for (auto q : quesList)
	{
		bool done = false;
		for (auto h : history)
		{
			if (*h == *q) { done = true; break; }
		}
		if (done) continue;//如果做过了就直接跳过本次循环，进入下一道题

		double userArea, userPeri;
		cout << "\n【题目" << q->getId() << "】" << q->getShape()->showQuestion() << endl;
		cout << "请输入你计算的面积、周长：";
		while (!(cin >> userArea >> userPeri))
		{
			cout << "输入无效，请重新输入面积和周长：";
			cin.clear();
			cin.ignore(1024, '\n');
		}

		FinishCount++;
		totalAnswered++;//累计答题数
		history.push_back(new Question(*q));
		bool areaRight = fabs(userArea - q->getCorrectArea()) < 0.01;
		bool periRight = fabs(userPeri - q->getCorrectPeri()) < 0.01;

		if (areaRight && periRight)
		{
			cout << "回答正确！本题得10分" << endl;
			totalScore += 10;
			correctCount++;//累计答对数
			correctThis++;//本次答对数
		}
		else
		{
			cout << "回答错误！正确面积：" << q->getCorrectArea() << " ，正确周长：" << q->getCorrectPeri() << endl;
			cout << "-------- 解析 --------" << endl;
			q->getShape()->printFormula();
			cout << "----------------------" << endl;
			bool alreadyIn = false;//假设错题本没有这道题

			for (auto w : wrongList)
			{
				if (*w == *q) { alreadyIn = true; break; }
			}
			if (!alreadyIn)
			{
				wrongList.push_back(new Question(*q));
			}
		}
	}
	cout << "\n========练习结束========" << endl;
	cout << "本次作答：" << FinishCount << " 道题目" << endl;
	cout << "你的总得分：" << totalScore << " 分" << endl;
	cout << "累计正确率：" << getAccuracy() << "%" << endl;
	showWrongAnalysis();
	return correctThis;
}
int QuestionBank::getFinishCount() const
{
	return FinishCount;
}
void QuestionBank::showWrongAnalysis() const
{
	if (wrongList.empty())
	{
		return;
	}
	int cnt[5] = { 0, 0, 0, 0, 0 };
	for (auto p : wrongList)
	{
		string t = p->getShape()->getShapeType();
		if (t == "Circle") cnt[0]++;
		else if (t == "Rect") cnt[1]++;
		else if (t == "Triangle") cnt[2]++;
		else if (t == "Trapezoid") cnt[3]++;
		else if (t == "Parallelogram") cnt[4]++;
	}
	string names[5] = { "圆形", "矩形", "三角形", "梯形", "平行四边形" };
	cout << "\n【错题分析】（共" << wrongList.size() << "道错题）：" << endl;
	int maxCnt = 0;
	for (int i = 0; i < 5; i++)
	{
		if (cnt[i] > 0)
		{
			cout << "  " << names[i] << " 错" << cnt[i] << "道" << endl;
			if (cnt[i] > maxCnt) maxCnt = cnt[i];
		}
	}
	//找出所有并列最多的
	cout << "\n【建议】你最薄弱的是：";
	bool first = true;
	for (int i = 0; i < 5; i++)
	{
		if (cnt[i] == maxCnt)
		{
			if (!first) cout << "、";
			cout << names[i];
			first = false;
		}
	}
	cout << "，建议专项练习突破！" << endl;
}

void QuestionBank::reviewHistory() const
{
	if (history.empty())
	{
		cout << "你还没有做过任何题目！" << endl;
		return;
	}
	int idx = 0;
	char c;
	while (true)
	{
		cout << "\n===== 回看题目（第 " << (idx + 1) << " / " << history.size() << " 题）=====" << endl;
		cout << "题目" << history[idx]->getId() << "：" << history[idx]->getShape()->showQuestion() << endl;
		cout << "标准答案 面积=" << history[idx]->getCorrectArea() << " 周长=" << history[idx]->getCorrectPeri() << endl;
		cout << "输入 n 看下一题 | p 看上一题 | q 退出回看：";
		cin >> c;
		if (c == 'n' && idx < (int)history.size() - 1) idx++;
		else if (c == 'p' && idx > 0) idx--;
		else if (c == 'q') { cout << "退出回看" << endl; break; }
		else cout << "（已是第一题/最后一题，或输入无效）" << endl;
	}
}
void QuestionBank::reviewWrongQuestions() const
{
	if (wrongList.empty())
	{
		cout << "太棒了！你还没有错题。" << endl;
		return;
	}
	cout << "\n=======错题本=======" << endl;
	int count = 1;
	for (auto q : wrongList)
	{
		cout << "错题" << count++ << "：" << q->getShape()->showQuestion() << endl;
	}
}
int QuestionBank::reviewWrongRetry()
{
	if (wrongList.empty())
	{
		cout << "太棒了！你还没有错题，无需重练。" << endl;
		return 0;
	}
	int correctThis = 0;//本次答对道数
	int idx = 0;//当前翻看的错题下标
	while (true)
	{
		if (wrongList.empty())
		{
			cout << "\n太棒了！所有错题都掌握了！" << endl;
			break;
		}
		cout << "\n===== 错题重练（第 " << (idx + 1) << " / " << wrongList.size() << " 道）=====" << endl;
		cout << "题目：" << wrongList[idx]->getShape()->showQuestion() << endl;
		cout << "操作：n下一题 | p上一题 | r练习这道题 | q退出重练：";
		char op;
		cin >> op;
		if (op == 'n' || op == 'N')
		{
			if (idx < (int)wrongList.size() - 1) idx++;
			else cout << "（已是最后一道错题）" << endl;
		}
		else if (op == 'p' || op == 'P')
		{
			if (idx > 0) idx--;
			else cout << "（已是第一道错题）" << endl;
		}
		else if (op == 'r' || op == 'R')
		{
			double userArea, userPeri;
			cout << "请输入你计算的面积、周长：";
			while (!(cin >> userArea >> userPeri))
			{
				cin.clear();
				cin.ignore(1024, '\n');
				cout << "输入无效！请输入两个数字。\n请重新输入面积、周长：";
			}
			bool areaRight = fabs(userArea - wrongList[idx]->getCorrectArea()) < 0.01;
			bool periRight = fabs(userPeri - wrongList[idx]->getCorrectPeri()) < 0.01;
			if (areaRight && periRight)
			{
				cout << "太棒了！那你已经掌握这道题了！本题将从错题本移除。" << endl;
				delete wrongList[idx];
				wrongList.erase(wrongList.begin() + idx);
				correctThis++;
				if (idx >= (int)wrongList.size()) idx = (int)wrongList.size() - 1;
			}
			else
			{
				cout << "回答错误！正确面积：" << wrongList[idx]->getCorrectArea()
					<< " ，正确周长：" << wrongList[idx]->getCorrectPeri() << endl;
				cout << "继续留在错题本，下次再练。" << endl;
			}
		}
		else if (op == 'q' || op == 'Q')
		{
			cout << "退出错题重练" << endl;
			break;
		}
		else
		{
			cout << "输入无效！请按 n/p/r/q 操作。" << endl;
		}
	}
	cout << "\n========错题重练结束========" << endl;
	cout << "本次答对 " << correctThis << " 道，剩余错题 " << wrongList.size() << " 道" << endl;
	showWrongAnalysis();
	return correctThis;
}
bool QuestionBank::deleteQuestion(int qid)
{
	for (auto it = quesList.begin(); it != quesList.end(); ++it)
	{
		if ((*it)->getId() == qid)
		{
			delete* it;//删除对象
			quesList.erase(it);//把指针这个元素移走，后面的往前移
			cout << "题目" << qid << "已删除！" << endl;
			return true;
		}
	}
	cout << "未找到编号为" << qid << "的题目！" << endl;
	return false;
}
void QuestionBank::resetRecords()
{
	for (auto q : history) delete q;
	history.clear();
	for (auto q : wrongList) delete q;
	wrongList.clear();//但正确率不清零
}
double QuestionBank::getAccuracy() const
{
	if (totalAnswered == 0) return 0.0;
	return static_cast<double>(correctCount) / totalAnswered * 100.0;
}
bool QuestionBank::saveData(const string& filename) const
{
	ofstream out(filename);
	if (!out.is_open())
	{
		cout << "【保存失败】无法打开文件:" << filename << endl;
		return false;
	}
	out << totalAnswered << " " << correctCount << endl;//累计答题数、答对数
	out << history.size() << endl;
	for (auto q : history)
		q->saveToFile(out);
	out << wrongList.size() << endl;
	for (auto q : wrongList)
		q->saveToFile(out);
	out.close();
	cout << "【保存成功】已保存到 " << filename << endl;
	return true;
}
bool QuestionBank::loadData(const string& filename, bool showMsg)
{
	ifstream in(filename);
	if (!in.is_open())
	{
		if (showMsg) cout << "【提示】未找到存档文件 " << filename << "，使用空数据" << endl;
		return false;
	}
	for (auto q : history) delete q;
	history.clear();
	for (auto q : wrongList) delete q;
	wrongList.clear();

	in >> totalAnswered >> correctCount;

	size_t hisCnt;
	in >> hisCnt;
	for (size_t i = 0; i < hisCnt; i++)
	{
		Question* q = Question::loadFromFile(in);
		if (q) history.push_back(q);
	}

	size_t wrongCnt;
	in >> wrongCnt;
	for (size_t i = 0; i < wrongCnt; i++)
	{
		Question* q = Question::loadFromFile(in);
		if (q) wrongList.push_back(q);
	}

	in.close();
	if (showMsg) cout << "【加载成功】历史题:" << history.size() << " 道，错题:" << wrongList.size() << " 道，累计正确率:" << getAccuracy() << "%" << endl;
	return true;
}
