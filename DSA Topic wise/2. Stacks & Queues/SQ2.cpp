/*

Implement a last-in-first-out (LIFO) stack using only two queues. The implemented stack should support all the functions of a normal stack (push, top, pop, and empty).

Implement the MyStack class:

void push(int x) Pushes element x to the top of the stack.
int pop() Removes the element on the top of the stack and returns it.
int top() Returns the element on the top of the stack.
boolean empty() Returns true if the stack is empty, false otherwise.

Notes:

You must use only standard operations of a queue, which means that only push to back, peek/pop from front, size and is empty operations are valid.
Depending on your language, the queue may not be supported natively.
You may simulate a queue using a list or deque (double-ended queue) as long as you use only a queue's standard operations.

*/


#include<iostream>
#include<stack>
#include<queue>

class MyStack
{
    std::queue<int> q1, q2;

    public:
    void push(int x);
    int pop();
    int top();
    bool isEmpty();

    void push2(int x);
    int pop2();
    int top2();
    bool isEmpty2();
};


int main()
{
    int choice, x, flag = 1;
    MyStack *obj = new MyStack();

    obj->push(1);
    obj->push(2);
    obj->push(3);
    obj->push(4);

    while(flag)
    {
        std::cout << "\n1. Push\t2. Pop\t3. Top\t4. IsEmpty:\n";
        std::cout <<"Enter your choice:\n";
        std::cin >> choice;

        switch(choice)
        {
        case 1:
            std::cout << "\nEnter element to be inserted:\n";
            std::cin >> x;

            obj->push(x);
            break;

        case 2:
            x = obj->pop();
            std::cout <<"\n " << x <<" element removed";
            break;

        case 3:
            x = obj->top();
            std::cout <<"\n " << x <<" element is at TOP of stack";
            break;

        case 4:
            if(obj->isEmpty())
                std::cout << "\nStack is empty";
            else
                std::cout<< "\nStack is Non-empty";
            break;

        default:
            flag = 0;
            break;
        }
    }

}



                                                // PUSH costly

void MyStack::push(int x)
{
    int frontt;
    while(!q1.empty())
    {
        frontt = q1.front();
        q1.pop();

        q2.push(frontt);
    }

    q1.push(x);

    while(!q2.empty())
    {
        frontt = q2.front();
        q2.pop();

        q1.push(frontt);
    }
}


int MyStack::pop()
{
    int frontt;
    if(q1.empty())
    {
        std::cout <<"\n UNDERFLOW. Stack empty\n";
        return -1;
    }

    frontt = q1.front();
    q1.pop();

    return frontt;
}



int MyStack::top()
{
    if(q1.empty())
    {
        std::cout <<"\n UNDERFLOW. Stack empty\n";
        return -1;
    }

    return q1.front();
}



bool MyStack::isEmpty()
{
    if(q1.empty())
        return true;
    return false;
}



                                                // POP costly

void MyStack::push2(int x)
{
    q1.push(x);
}



int MyStack::pop2()
{
    int frontt;
    if(q1.empty())
    {
        std::cout <<"\nUNDERFLOW. Stack Empty\n";
        return -1;
    }

    while(q1.size() != 1)
    {
        frontt = q1.front();
        q1.pop();
        q2.push(frontt);
    }

    frontt = q1.front();
    q1.pop();

    q1 = q2;
    q2 = {};

    return frontt;
}



int MyStack::top2()
{
    if(q1.empty())
    {
        std::cout <<"\nUNDERFLOW. Stack Empty\n";
        return -1;
    }

    return q1.back();
}



bool MyStack::isEmpty2()
{
    if(q1.empty())
        return true;

    return false;
}
