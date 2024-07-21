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




//Shunting-yard Algorithm
string ConvertInfixToPostfix(string infix) {
    stack<char> op;
    string output = "";
    for (int i = 0; i < infix.length();i++) {
        //check if the scanned token is operand?
        if (!IsOperator(infix[i])) {

            //to handle cases where operands have more than 1 digit
            while (!IsOperator(infix[i]) && i < infix.length()) {
                output += infix[i];
                i++;
            }
            //Make sure there is a space after each element (both operand and operator).
            if (IsOperator(infix[i]) || i == infix.length())
                output += ' ';
            --i;//Make sure the for loop goes through the entire element
        }

        //Just need to handle cases where it is an operator
        else if (op.empty() || infix[i] == '(' || op.top() == '(')
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
            //If the top of the stack and the scanned operator have equal precedence,
            //  then if the scanned operator is right-associative, it has higher precedence than
            //  the top of the stack.
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
        output += (op.size() == 1)? "" : " ";
        op.pop();
    }
    return output;
}


int BasicCalculator(int num1, int num2, char op) {
    switch (op) {
    case '^':
        return  pow(num2, num1);
    case '*':
        return num2 * num1;
    case '/':
        return num2 / num1;
    case '+':
        return num2 + num1;
    case '-':
        return num2 - num1;
    }
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
        else if (number > 0 || check) {
            output.push(number);
            number = 0;
            check = false;
        }
        else if (postfix[i] != ' ')
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
