//
// Created by whalesea on 2023/5/15.
//

#include <bits/stdc++.h>

using namespace std;

int eval(string expression)
{
    stack<int> num;
    stack<char> op;

    int i = 0;

    int data = 0;
    while(i < expression.size())
    {
        if(expression[i] == '+')
        {
            num.push(data);
            data = 0;

            while(!op.empty() && op.top() == '*')
            {
                op.pop();
                int a = num.top();
                num.pop();
                int b = num.top();
                num.pop();
                num.push(a * b);
            }


            op.push('+');
        }
        else if (expression[i] == '*')
        {
            num.push(data);
            data = 0;
            op.push('*');
        }
        else
        {
            data = 10 * data + expression[i] - '0';
        }

        i++;
    }

    num.push(data);

    while(!op.empty())
    {
        char cur_op = op.top();
        op.pop();

        int a = num.top();
        num.pop();
        int b = num.top();
        num.pop();

        if(cur_op == '+')
        {
            num.push(a + b);
        }
        else
        {
            num.push(a * b);
        }
    }

    return num.top();
}

bool functionRight(string func)
{
    int eq= -1;

    for (int i = 0; i < func.size(); ++i)
    {
        if(func[i] == '=')
        {
            eq = i;
            break;
        }
    }

    string left = func.substr(0, eq);
    string right = func.substr(eq + 1);

    return eval(left) == eval(right);
}

bool final_verify(string func)
{
    for (int i = 0; i <= func.size(); ++i)
    {
        string prev = func.substr(0, i);
        string next = i == func.size() ? "" : func.substr(i);

        int start = 0;

        if(prev.size() == 0 || prev.back() == '+' || prev.back() == '*')
        {
            start = 1;
        }

        for (int j = start; j <= 9; ++j)
        {
            string to_veritfy = prev + to_string(j) + next;
            if(functionRight(to_veritfy))
            {
                return true;
            }
        }
    }

    return false;
}


int main() {

    cout << eval("16") << endl;
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
    {
        string func;
        cin >> func;
        if(final_verify(func))
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
    }


    return 0;
}
