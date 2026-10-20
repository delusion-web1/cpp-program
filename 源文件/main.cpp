#include <iostream>
#include "QuestionBank.h"
#include <ctime>
using namespace std;

void showMenu()
{
	cout << "\n====几何题库练习系统====" << endl;
	cout << "1. 批量生成题目" << endl;
	cout << "2. 查看全部题目" << endl;
	cout << "3. 开始答题" << endl;
	cout << "4. 查看答题记录" << endl;
	cout << "5. 查看错题" << endl;
	cout << "6. 删除题目" << endl;
	cout << "0. 退出程序" << endl;
	cout << "========================" << endl;
}
int main()
{
	srand((unsigned int)time(NULL));
	string inputName;
	cout << "请输入题库名称： ";
	getline(cin, inputName);
	QuestionBank bank;
	if (!inputName.empty())
	{
		bank = QuestionBank(inputName);
	}
	int op;
	int num;
	while (true)
	{
		cout << "\n当前题库：" << bank.getBankName() << endl;
		showMenu();
		cout << "请输入选项：";
		cin >> op;
		if (op == 0)
		{
			cout << "程序退出" << endl;
			break;
		}
		switch (op)
		{
		case 1:
			cout << "请输入要生成的题目数量：";
			cin >> num;
			bank.generateN(num);
			cout << "成功生成" << num << "道题目！" << endl;
			break;
		case 2:
			bank.showAllQuestion();
			break;
		case 3:
			bank.startAns();
			break;
		case 4:
			bank.reviewHistory();
			break;
		case 5:
			bank.reviewWrongQuestions();
			break;
		case 6:
		{
			int qid;
			cout << "请输入要删除的题目编号：";
			cin >> qid;
			bank.deleteQuestion(qid);
			break;
		}
		default:
			cout << "请输入正确的菜单选项" << endl;
			break;
		}
	}
	return 0;
}