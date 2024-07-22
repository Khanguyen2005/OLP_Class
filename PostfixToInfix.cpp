// PostfixToInfix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool IsOperand(char c) {
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9') {
        return true;
    }
    return false;
}



string PostfixToInfix(string postfix) 
{
    stack<string> res;
    for (int i = 0; i < postfix.length();i++) {
        string exp = "";
        if (IsOperand(postfix[i])) {
            while (IsOperand(postfix[i])) {
                exp += postfix[i];
                i++;
            }
            res.push(exp);
        }
        else if (postfix[i] == ' ') {
            continue;
        }
        else
        {
            string top1 = res.top();
            res.pop();
            string top2 = res.top();
            res.pop();
            res.push('(' + top2 + postfix[i] + top1 + ')');
        }
    }
    return res.top();
}

int main()
{
    string s;
    getline(cin, s);
    cout << PostfixToInfix(s);
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
