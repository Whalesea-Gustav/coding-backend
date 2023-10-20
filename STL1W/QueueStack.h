#pragma once
#include <queue>
#include <stack>
#include <optional>

using namespace std;

template<typename T>
class squeue
{
private:

    stack<T> A;
    stack<T> B;

public:
    void push(T value)
    {
        A.push(value);
    }

    void pop()
    {
        optional<T> mfront = front();

        if(!mfront.has_value()) throw std::runtime_error("squeue empty error");

        B.pop();
    }

    optional<T> front()
    {
        if(A.empty() && B.empty()) return nullptr;

        if(B.empty())
        {
            while(!A.empty())
            {
                B.push(A.top());
                A.pop();
            }
        }

        return B.top();
    }

    bool empty()
    {
        return A.empty() && B.empty();
    }
};

template<typename T>
class qstack
{
private:
    queue<T> reverseQ;
    queue<T> tmpQ;

public:

    void push(T value)
    {
        tmpQ.push(value);

        while(!reverseQ.empty())
        {
            tmpQ.push(reverseQ.front());
            reverseQ.pop();
        }

        swap(tmpQ, reverseQ);
    }

    void pop()
    {
        if(reverseQ.empty()) throw std::runtime_error("qstack empty error");

        reverseQ.pop();
    }

    optional<T> top()
    {
        if(reverseQ.empty()) return nullptr;

        return {reverseQ.front()};
    }


    bool empty()
    {
        return reverseQ.empty();
    }
};