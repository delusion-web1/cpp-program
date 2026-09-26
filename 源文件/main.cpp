#include <iostream>
#include "Triangle.h"
#include "QuestionBank.h"
using namespace std;
void shouMenu()
{
    cout << "==========================" << endl;
    cout << "1. 添加题目" << endl;
    cout << "2. 删除题目(输入题号)" << endl;
    cout << "3. 显示所有题目" << endl;
    cout << "4. 显示题目总数" << endl;
    cout << "5. 开始做题" << endl;
    cout << "0. 退出" << endl;
    cout << "请输入选择：" << endl;
}
int main()
{
    QuestionBank bank("几何三角形题库");
    int op;
    while (true) {
        shouMenu();
        cin >> op;
        //若输入非数字，全清空
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "输入无效，请输入数字!" << endl;
            continue;
        }
        if (op == 0)
        {
            cout << "程序结束" << endl;
            break;
        }
        switch (op) {
        case 1:
        {
            int id;
            double x, y, z;
            cout << "请输入题号和三条边： ";
            cin >> id >> x >> y >> z;
            Triangle t(id, x, y, z);
            if (bank.hasQuestions(id))
            {
                cout << "题号为 " << id << " 的题目已存在，题目添加失败!重新输入" << endl;
                continue;
            }
            if (!t.isLegal())
            {
                cout << "输入的三边长度不构成合法三角形，题目添加失败!" << endl;
                continue;
            }
            bank.addQuestion(t);
            cout << "题目添加成功!" << endl;
            break;
        }
        case 2:
        {
            int id;
            cout << "请输入要删除的题号： ";
            cin >> id;
            bank.delQuestionById(id);
            break;
        }
        case 3:
            bank.showAllQuestion();
            break;
        case 4:
            cout << "题目总数: " << bank.getCount() << endl;
            break;
        case 5:
            bank.startQuiz();
            break;
        default:
            cout << "无效的选择，请重新输入!" << endl;
        }
    }
    return 0;
}