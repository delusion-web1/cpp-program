#include <iostream>
#include "QuestionBank.h"
#include "UserManager.h"
#include <ctime>
#include<iomanip> 
using namespace std;
void showBankMenu()
{
	cout << "\n====几何题库练习系统====" << endl;
	cout << "1. 批量生成题目" << endl;
	cout << "2. 查看全部题目" << endl;
	cout << "3. 开始答题" << endl;
	cout << "4. 回看答题记录（上一题/下一题）" << endl;
	cout << "5. 查看错题" << endl;
	cout << "6. 错题重练" << endl;
	cout << "7. 删除题目" << endl;
	cout << "8. 保存数据到文件" << endl;
	cout << "9. 加载数据" << endl;
	cout << "10. 重置历史记录" << endl;
	cout << "0. 保存并退出登录" << endl;
	cout << "========================" << endl;
}
int main()
{
	srand((unsigned int)time(NULL));
	cout << fixed << setprecision(2);
	UserManager um("data/users.txt");
	um.loadUsers();
	int op;
	while (true)
	{
		cout << "\n=====几何题库系统·用户管理=====" << endl;
		cout << "1. 用户登录" << endl;
		cout << "2. 用户注册" << endl;
		cout << "3. 用户注销" << endl;
		cout << "4. 查看排行榜" << endl;
		cout << "0. 退出系统" << endl;
		cout << "请选择：";
		if (!(cin >> op))
		{
			cin.clear();
			cin.ignore(1024, '\n');
			cout << "输入无效，请输入数字！" << endl;
			continue;
		}
		if (op == 0)
		{
			um.saveUsers();
			cout << "系统已退出，数据已保存" << endl;
			break;
		}
		else if (op == 1)//登录
		{
			string name, pwd;
			cout << "请输入用户名："; cin >> name;
			cout << "请输入密码："; cin >> pwd;
			if (!um.login(name, pwd))
			{
				cout << "用户名或密码错误！" << endl;
				continue;
			}
			cout << "登录成功！欢迎 " << name << endl;

			QuestionBank bank;
			string dataFile = "data/bank_" + name + ".txt";
			bank.loadData(dataFile);//静默加载该用户存档

			int op2;
			while (true)
			{
				cout << "\n当前用户：" << name << "\n题库：" << bank.getBankName();
				cout << "\n累计正确率：" << bank.getAccuracy() << "%" << endl;
				showBankMenu();
				cout << "请输入选项：";
				if (!(cin >> op2))
				{
					cin.clear();
					cin.ignore(1024, '\n');
					cout << "输入无效，请输入数字！" << endl;
					continue;
				}
				if (op2 == 0)
				{
					bank.saveData(dataFile);
					um.saveUsers();
					cout << "已保存并退出登录" << endl;
					break;
				}
				switch (op2)
				{
				case 1:
				{
					int num;
					cout << "请输入要生成的题目数量：";
					if (!(cin >> num))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "数量必须是数字！" << endl;
						break;
					}
					int typeSel = -1;
					cout << "图形类型（0全部 1圆 2矩形 3三角形 4梯形 5平行四边形）：";
					if (cin >> typeSel)
					{
						if (typeSel == 0) typeSel = -1;
						else if (typeSel >= 1 && typeSel <= 5) typeSel = typeSel - 1;
						else typeSel = -1;//范围外的按全部处理
					}
					else
					{
						cin.clear();//输入非数字则默认全部
						cin.ignore(1024, '\n');
					}
					bank.generateN(num, typeSel);
					break;
				}
				case 2:
					bank.showAllQuestion();
					break;
				case 3:
				{
					clock_t t1 = clock();//开始计时
					int correct = bank.startAns();
					clock_t t2 = clock();//结束计时
					int secs = (int)((t2 - t1) / CLOCKS_PER_SEC);
					if (bank.getFinishCount() > 0)//只有实际答了题才计入成绩，防止空跑拉高平均用时
						um.addResult(name, correct, bank.getFinishCount(), secs);//累加到用户成绩
					break;
				}
				case 4:
					bank.reviewHistory();
					break;
				case 5:
					bank.reviewWrongQuestions();
					break;
				case 6:
				{
					bank.reviewWrongRetry();//错题重练
					break;
				}
				case 7:
				{
					int qid;
					cout << "请输入要删除的题目编号：";
					if (!(cin >> qid))
					{
						cin.clear();
						cin.ignore(1024, '\n');
						cout << "编号必须是数字！" << endl;
						break;
					}
					bank.deleteQuestion(qid);
					break;
				}
				case 8:
					bank.saveData(dataFile);
					break;
				case 9:
					bank.loadData(dataFile, true);//加载数据,显示结果
					break;
				case 10:
				{
					char confirm;
					cout << "确定要清空做题记录（历史题、错题）吗？正确率与用时将保留。(y/n)：";
					cin >> confirm;
					if (confirm == 'y' || confirm == 'Y')
					{
						bank.resetRecords();//保留正确率和时间
						cout << "已重置题目记录！历史题、错题已清空。" << endl;
					}
					else cout << "已取消重置。" << endl;
					break;
				}
				default:
					cout << "请输入正确的菜单选项" << endl;
					break;
				}
			}
		}
		else if (op == 2)//注册
		{
			string name, pwd;
			cout << "请输入新用户名："; cin >> name;
			cout << "请输入密码："; cin >> pwd;
			if (um.registerUser(name, pwd)) cout << "注册成功！请登录使用" << endl;
			else cout << "注册失败！请检查用户名是否已存在、密码是否满足规则" << endl;
		}
		else if (op == 3)//注销
		{
			string name, pwd;
			cout << "请输入要注销的用户名："; cin >> name;
			cout << "请输入密码确认："; cin >> pwd;
			if (um.deleteUser(name, pwd)) cout << "用户已注销，相关存档已删除" << endl;
			else cout << "注销失败：用户名或密码错误" << endl;
		}
		else if (op == 4)//排行榜
		{
			um.showRankByAccuracy();
			um.showRankByTime();
		}
		else
		{
			cout << "请输入正确的选项" << endl;
		}
	}
	return 0;
}
