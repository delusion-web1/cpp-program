#include<iostream>
#include<vector>
#include<cstdlib>
#include<fstream>
#include<ctime>
#include<string>
#include<cmath>
#include"Shape.h"
#include"Circle.h"
#include"Rect.h"
#include"Triangle.h"
#include<memory>
using namespace std;
using Ptr = std::shared_ptr<Shape>;
//结构体用来保存错题的全部信息：图形，用户的输入（面积和周长）
struct WrongItem
{
	Ptr shape;
	double userArea;
	double userPeri;
};
vector<Ptr> problemList;
vector<WrongItem> wrongItems;//错题列表里面的表示形式
Ptr createRandomShape();
int main()
{
	srand(time(0));//设置随机种子，保证每次随机图案不一样
	int choice;
	while (true)
	{
		cout << "n========几何图形题库系统========" << endl;
		cout << "1.开始答题" << endl;
		cout << "2.查看历史错题" << endl;
		cout << "0.退出程序" << endl;
		cout << "请输入功能选项: ";
		cin >> choice;
		if (choice == 0)
		{
			cout << "程序退出" << endl;
			break;
		}
		else if (choice == 1)
		{
			problemList.clear();
			wrongItems.clear();
			//每一轮开始前清空上一轮的错题
			int total = 7;//一共输出七道题
			int correct = 0;//答对的题目数量
			for (int i = 0;i < total;i++)
			{
				cout << "\n第" << i + 1 << "题" << endl;
				Ptr p = createRandomShape();
				problemList.push_back(p);//存入vector容器当中
				double userArea, userPeri;
				cout << "请输入面积，周长： ";
				cin >> userArea >> userPeri;
				//如果输入的是字符，则跳过这一题
				if (cin.fail())
				{
					cout << "输入错误，跳过这一题" << endl;
					cin.clear();
					cin.ignore(10000, '\n');//清空输入缓冲区
					continue;
				}
				double trueArea = p->getArea();
				double truePeri = p->getPerimeter();
				//浮点数不能直接比较，允许误差0.5
				bool right = (fabs(userArea - trueArea) < 0.5) && (fabs(userPeri - truePeri) < 0.5);
				if (right)
				{
					cout << "回答正确" << endl;
					correct++;
				}
				else
				{
					cout << "回答错误! 正确面积是： " << trueArea << "  正确周长是： " << truePeri << endl;
					wrongItems.push_back({ p, userArea, userPeri });
				}
			}
			cout << "\n答题结束，您一共答对：" << correct << "/" << total << "题" << endl;
			//释放堆内存，防止内存泄漏
			problemList.clear();
		}
		else if (choice == 2)
		{
			if (wrongItems.empty())
			{
				cout << "暂无错题记录" << endl;
				continue;
			}
			cout << "=======历史错题记录======" << endl;
			for (auto& item : wrongItems)
			{
				cout << "题目是：" << endl;
				item.shape->showInfo();
				cout << "你的答案：面积：" << item.userArea << "  周长：" << item.userPeri << endl;
				cout << "正确答案：面积：" << item.shape->getArea() << "  正确周长：" << item.shape->getPerimeter() << endl;
				cout << "------------------------" << endl;
			}
		}
	}
	return 0;
}
Ptr createRandomShape()
{
	int type = rand() % 3;//0是圆形，1是矩形，2是三角形
	if (type == 0)
	{
		double r = rand() % 5 + 1;
		cout << "圆形半径为：" << r << endl;
		return std::make_shared<Circle>(r);
	}
	else if (type == 1)
	{
		double w = rand() % 5 + 1;
		double h = rand() % 5 + 1;
		cout << "矩形的宽为：" << w << "  长为：" << h << endl;
		return std::make_shared<Rect>(w, h);
	}
	else
	{
		double a, b, c;
		//保证三角形三边满足三角不等式
		do {
			a = rand() % 4 + 2;
			b = rand() % 4 + 2;
			c = rand() % 4 + 2;
		} while (a + b <= c || a + c <= b || b + c <= a);
		cout << "三角形的三边为：" << a << " " << b << " " << c << endl;
		return std::make_shared<Triangle>(a, b, c);
	}
}