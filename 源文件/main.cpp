#include <iostream>
#include "QuestionBank.h"
using namespace std;

void showMenu()
{
    cout << "\n====几何题库练习系统====" << endl;
    cout << "1. 批量生成题目" << endl;
    cout << "2. 查看全部题目" << endl;
    cout << "3. 开始答题" << endl;
    cout << "4. 查看答题记录" << endl;
    cout << "0. 退出程序" << endl;
    cout << "========================" << endl;
}

int main()
{
    QuestionBank bank("几何练习题库");
    int op;
    int num;
    while (true)
    {
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
            cout << "输入要生成的题目数量：";
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
        default:
            cout << "输入错误，请重新选择！" << endl;
            break;
        }
    }
    return 0;
}