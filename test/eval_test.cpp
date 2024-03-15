#include <iostream>
#include <stack>
#include <map>
#include <cmath>
#include <cstring>
using namespace std;

bool delim(char c) { return c == ' '; }

bool is_op(char c) { return c == '+' || c == '-' || c == '*' || c == '/'; }

int priority(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return -1;
}

void process_op(stack<int>& st, char op) {  // 也可以用于计算后缀表达式
    int r = st.top();                         // 取出栈顶元素，注意顺序
    st.pop();
    int l = st.top();
    st.pop();
    switch (op) {
        case '+':
            st.push(l + r);
            break;
        case '-':
            st.push(l - r);
            break;
        case '*':
            st.push(l * r);
            break;
        case '/':
            st.push(l / r);
            break;
    }
}

int evaluate(string& s) {  // 也可以改造为中缀表达式转换后缀表达式
    stack<int> st;
    stack<char> op;
    for (int i = 0; i < (int)s.size(); i++) {
        if (delim(s[i])) continue;

        if (s[i] == '(') {
            op.push('(');  // 2. 如果遇到左括号，那么将其放在运算符栈上
        } else if (s[i] == ')') {  // 3. 如果遇到右括号，执行一对括号内的所有运算符
            while (op.top() != '(') {
                process_op(st, op.top());
                op.pop();  // 不断输出栈顶元素，直至遇到左括号
            }
            op.pop();                // 左括号出栈
        } else if (is_op(s[i])) {  // 4. 如果遇到其他运算符
            char cur_op = s[i];
            while (!op.empty() && priority(op.top()) >= priority(cur_op)) {
                process_op(st, op.top());
                op.pop();  // 不断输出所有运算优先级大于等于当前运算符的运算符
            }
            op.push(cur_op);  // 新的运算符入运算符栈
        } else {            // 1. 如果遇到数字，直接输出该数字
            int number = 0;
            while (i < (int)s.size() && isalnum(s[i]))
                number = number * 10 + s[i++] - '0';
            --i;
            st.push(number);
        }
    }

    while (!op.empty()) {
        process_op(st, op.top());
        op.pop();
    }
    return st.top();
}

int main(int argc, char** argv) {

    string str;

    cin >> str;

    string tstr = str.substr(0,str.size()-1);
    cout << str << evaluate(tstr);
    return 0;
}