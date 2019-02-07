#include <iostream>
#include <stack>
#include <cctype>
#include <bits/stdc++.h>
using namespace std;

int Priority(char C)
{
    if (C == '-' || C == '+')
        return 1;
    else if (C == '*' || C == '/')
        return 2;
    else if (C == '^')
        return 3;
    else
        return 0;
}

string infixToPostfix(string s) {
    stack<char> operators;
    string output;


    for (int i = 0; i < s.length(); i++) {                  //takes infix and returns postfix
        if (s[i] == '(') {
            operators.push(s[i]);

        } else if (isdigit(s[i]) || isalpha(s[i])) {
            output = output + s[i];

        } else if (s[i] == '*' || s[i] == '+' || s[i] == '/' || s[i] == '-') {
            if(!isalpha(operators.top()) && !isdigit(operators.top())) {

                while (!operators.empty() && s[i] != '(' && Priority(s[i]) <= Priority(operators.top())) {
                    output = output + operators.top();
                    operators.pop();
                }
                operators.push(s[i]);
            }
        } else {       //for this case s[i]=')'
            while (operators.top() != '(') {
                output = output + operators.top();
                operators.pop();
            }
            operators.pop();
        }
    }
    return output;
}


    void recursive (string &output, stack<string> &characters){
        if(characters.size() > 0) {
            string temp = characters.top();
            characters.pop();
            if (temp == "*" || temp == "+" || temp == "/" || temp == "-") {
                output = output + '(';
                recursive(output, characters);
                output = output + temp;
                recursive(output, characters);
                output = output + ')';
            } else {
                output = output + temp;
            }
        }
    }

    string reverse(string &str){
        stack<string> characters;
        string output;
        for(int i = 0; i<str.length(); i++) {
            string temp = "";
            if (str[i] == '['){
                while(str[i]!=']'){
                    temp = temp + str[i];
                }
            }
            characters.push(temp);
        }
        while (!characters.empty()){
            output = output + characters.top();
            characters.pop();
        }
        return output;
    }

    string prefixToInfix(string s)
    {
        stack<string> characters;
        string output;

        //s = reverse(s);
        for(int i=s.length()-1; i>=0; i--) {
            string temp;
            temp.push_back(s[i]);
            characters.push(temp);
        }
        while(!characters.empty()){
            recursive(output, characters);
        }
        return output;
    }


    string infixToPrefix(string s)
    {
        reverse(s.begin(), s.end());

        for (int i = 0; i < s.length(); i++) {      //reverses the orientation of '(' and ')'

            if (s[i] == '(') {
                s[i] = ')';
                i++;
            }
            else if (s[i] == ')') {
                s[i] = '(';
                i++;
            }
        }
        string output = infixToPostfix(s);
        reverse(output.begin(), output.end());
        return output;
    }

    int main()
    {
        string s = "(c/d+b)";
        string m = "(5*2-7)";
        string str =  "+/[c][d][b]";
        cout << s <<endl;
        cout << infixToPostfix(s) <<endl;
        cout << infixToPrefix(s) <<endl;
        cout << prefixToInfix(s) <<endl;
        cout << prefixToInfix(str) <<endl;
        cout << endl;
        cout << m <<endl;
        cout << infixToPostfix(m) <<endl;
        cout << infixToPrefix(m) <<endl;
        cout << prefixToInfix(m) <<endl;
        return 0;
    }
