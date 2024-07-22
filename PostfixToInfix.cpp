// PostfixToInfix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <queue>
using namespace std;

bool IsOperand(char c) {
    if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c >= '0' && c <= '9') {
        return true;
    }
    return false;
}

string PostfixToInfix(string postfix) 
{
    queue<string> res;
    for (int i = 0; i < postfix.length();i++) {
        string exp = "";
        if (IsOperand(postfix[i])) {
            exp += postfix[i];
            res.push(exp);
        }
        else 
        {
            exp += (i == postfix.length()-1)?"":"(";
            while (!res.empty()) {
                exp += res.front();
                res.pop();
                if (!res.empty())
                    exp += postfix[i];
            }
            exp += (i == postfix.length() - 1) ? "" : ")";
            res.push(exp);
        }
    }
    return res.front();
}

int main()
{
    string s;
    cin >> s;
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
