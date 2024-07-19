// InfixToPostfixCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<stack>
#include <cmath>
using namespace std;

bool IsOperator(char token) {
    switch (token) {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    case '^':
    case ' ':
        return true;
    default:
        return false;
    }
    
}

int GetPrecedence(char token) { 
    if (token == '^')
        return 3;
    else if (token == '*' || token == '/')
        return 2;
    else if (token = '+' || token == '-')
        return 1;
    else
        return -1; 
}

char Associativity(char token) {
    if (token == '^')
        return 'r';
}

string ValidString(string postfix) {
    string res = "";
    for (int i = 0; i < postfix.length() - 1; i++) {
        res += postfix[i];
    }
    return res;
}


//Shunting-yard Algorithm
string ConvertInfixToPostfix(string infix) {
    stack<char> op;
    string output;
    for (int i = 0; i < infix.length();i++) {
        string element = "";
        if (!IsOperator(infix[i])) {
            while (!IsOperator(infix[i]) && i < infix.length()) {
                element += infix[i];
                i++;
            }
        }
        output += element+' ';
        if (op.empty() || infix[i] == '('||op.top()=='(')//luc nay scanned token da la operator
        {
            op.push(infix[i]);
        }
        else if (infix[i] == ')') {
            while (op.top() != '(') {
                output += op.top();
                output += ' ';
                op.pop();
            }
            op.pop();
        }
        else if (GetPrecedence(infix[i]) > GetPrecedence(op.top()))
        {
        Perform1: //lable Perform1
            op.push(infix[i]);
        }
        else if (GetPrecedence(infix[i]) <= GetPrecedence(op.top())) {
            if (Associativity(infix[i]) == 'r')
                goto Perform1;
            while (!op.empty() && op.top() != '(' && GetPrecedence(op.top()) >= GetPrecedence(infix[i])) {
                output += op.top();
                output += ' ';
                op.pop();
            }
            op.push(infix[i]);

        }

    }
    while (!op.empty()) {
        output += op.top();
        output += ' ';
        op.pop();
    }
    return ValidString(output);
}


int BasicCalculator(int num1, int num2, char op) {
    int res = 0;
    switch (op) {
    case '^':
        res = pow(num2, num1);
        break;
    case '*':
        res = num2 * num1;
        break;
    case '/':
        res = num2 / num1;
        break;
    case '+':
        res = num2 + num1;
        break;
    case '-':
        res = num2 - num1;
        break;
    }
    return res;
}



int PostfixCalculator(string postfix) {
    stack<int> output;
    int number = 0;
    bool check = false;
    for (int i = 0; i < postfix.length();i++) {
        if (!IsOperator(postfix[i])) {
            
            number = number * 10 + postfix[i] - '0';
            check = true;
        }
        else if (number > 0|| check) {
            output.push(number);
            number = 0;
            check = false;
        }
        else if(postfix[i] != ' ')
        {
            int num1 = output.top();
            output.pop();
            int num2 = output.top();
            output.pop();
            output.push(BasicCalculator(num1, num2, postfix[i]));
        }
    }
    return output.top();
}


int main()
{
    string s;
    cin >> s;
    cout << PostfixCalculator(ConvertInfixToPostfix(s)) << endl;
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
