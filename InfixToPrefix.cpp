// InfixToPrefix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


//De convert tu infix sang prefix ta thuc hien cac steps sau:
//step 1: dao nguoc infix expression
//step 2: thuc hien convert infix expression da reversed sang postfix expression
//Qua trinh thuc hien giong nhu convert infix sang postfix thong thuong chi la: can custom 1 vai cho sau day:
//2.1 Khi gap toan tu co precedence thap hon top cua stack thi ta ta chi pop cac toan tu co precedence
//  cao hon no trong stack, nghia la khi gap top co precedence tuong duong/ nho hon ta deu dung lai
//  va push toan tu dang duyet vao
//2.2 co 1 ngoai le voi toan tu ^ co right-associative nghia la tinh tu phai sang trai, neu gap toan tu nay
//  va top bang nhau(top cung la '^') thi ta phai pop ca top do ra roi push toan tu nay vao 
#include <iostream>
#include <stack>
#include<string>
#include <cmath>

using namespace std;

bool IsOperand(char op) {
    if (op >= 'a' && op <= 'z' || op >= 'A' && op <= 'Z' || op >= '0' && op <= '9')
        return true;
    return false;
}

int Pre(char op) {
    if (op == '^')
        return 3;
    else if (op == '/' || op == '*')
        return 2;
    else if (op == '+' || op == '-')
        return 1;
    else
        return -1;
}

string Reverse(string infix) {
    string reverse = "";
    for (int i = infix.length()-1; i >= 0;i--) {
        if (infix[i] == ')') {
            reverse += '(';
        }
        else if (infix[i] == '(') {
            reverse += ')';
        }
        else {
            reverse += infix[i];
        }
    }
    return reverse;
}


//sau khi reverse infix expression thi thuc hien shunting yard algorithm chuyen chuoi reversed do
//  sang postfix expression, sau do ta lai reverse ket qua(dang la chuoi postfix expression) 
// de co duoc prefix expression
string InfixToPrefix(string infix) {
    infix = Reverse(infix);
    stack<char> operators;
    string res = "";
    for (int i = 0; i < infix.length();i++) {
        if (IsOperand(infix[i])) {
            res += infix[i];
        }
        else if (operators.empty() || operators.top() == '(' || infix[i] == '(' 
            || Pre(infix[i]) > Pre(operators.top())) {
            operators.push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (operators.top()!= '(') {
                res += operators.top();
                operators.pop();
            }
            operators.pop();
        }
        else if(infix[i] == '^') {
            while (!operators.empty() &&  Pre(operators.top()) >= Pre(infix[i])) {
                res += operators.top();
                operators.pop();
            }
            operators.push(infix[i]);
        }
        else {
            while (!operators.empty() && Pre(operators.top()) > Pre(infix[i]) && operators.top()!= '(') {
                res += operators.top();
                operators.pop();
            }
            operators.push(infix[i]);
        }
    }
    while (!operators.empty()) {
        res += operators.top();
        operators.pop();
    }
    return Reverse(res);
}

int Calculator(int top1, int top2, char op) {
    switch (op) {
    case '+':
        return top1 + top2;
    case '-':
        return top1 - top2;
    case '*':
        return top1 * top2;
    case '/':
        return top1 / top2;
    case '^':
        return (int)pow(top1, top2);
    }
}

int PrefixCalculator(string prefix) {
    stack<int> res;
    for (int i = prefix.length()-1;i >= 0;i--) {
        if (IsOperand(prefix[i])) {
            res.push(prefix[i]-'0');
        }
        else {
            int top1 = res.top();
            res.pop();
            int top2 = res.top();
            res.pop();
            res.push(Calculator(top1, top2, prefix[i]));
        }
    }
    return res.top();
}

int main()
{
    string s;
    getline(cin, s);
    cout << PrefixCalculator(InfixToPrefix(s));
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
