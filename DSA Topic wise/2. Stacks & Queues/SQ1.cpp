/*
Implement a first in first out (FIFO) QUEUE using only 2 STACKS. The implemented queue should support all the functions of a normal queue (push, peek, pop, and empty).

Implement the MyQueue class:

void push(int x) Pushes element x to the back of the queue.
int pop() Removes the element from the front of the queue and returns it.
int peek() Returns the element at the front of the queue.
boolean empty() Returns true if the queue is empty, false otherwise.

Notes:
You must use only standard operations of a stack, which means only push to top, peek/pop from top, size, and is empty operations are valid.
Depending on your language, the stack may not be supported natively. You may simulate a stack using a list or deque (double-ended queue)
as long as you use only a stack's standard operations.

*/

#include<iostream>
#include<stack>
#include<queue>

class MyQueue
{
    std::stack<int> s1, s2;

    public:
    void push(int x);
    int pop();
    int peek();
    bool isEmpty();

    void push2(int x);
    int pop2();
    int peek2();
    bool isEmpty2();
};


int main()
{
    int choice, x, flag = 1;
    MyQueue *obj = new MyQueue();

    obj->push2(1);
    obj->push2(2);
    obj->push2(3);
    obj->push2(4);

    while(flag)
    {
        std::cout << "\n1. EnQueue\t2. DeQueue\t3. First\t4. IsEmpty:\n";
        std::cout <<"Enter your choice:\n";
        std::cin >> choice;

        switch(choice)
        {
        case 1:
            std::cout << "\nEnter element to be inserted:\n";
            std::cin >> x;

            obj->push2(x);
            break;

        case 2:
            x = obj->pop2();
            std::cout <<"\n " << x <<" element removed";
            break;

        case 3:
            x = obj->peek2();
            std::cout <<"\n " << x <<" element is at FRONT of Queue";
            break;

        case 4:
            if(obj->isEmpty2())
                std::cout << "\nQueue is empty";
            else
                std::cout<< "\nQueue is Non-empty";
            break;

        default:
            flag = 0;
            break;
        }
    }

}


// ENQUEUE costly
void MyQueue::push(int x)
{
    int top;

    while(!s1.empty())
    {
        top = s1.top();

        s1.pop();
        s2.push(top);
    }

    s1.push(x);

    while(!s2.empty())
    {
        top = s2.top();

        s2.pop();
        s1.push(top);
    }
}


int MyQueue::pop()
{
    if(s1.empty())
    {
        std::cout<<"\nUNDERFLOW\n";
        return -1;
    }

    int top = s1.top();
    s1.pop();
    return top;
}


int MyQueue::peek()
{
    if(s1.empty())
    {
        std::cout<<"\nUNDERFLOW\n";
        return -1;
    }

    int top = s1.top();
    return top;
}


bool MyQueue::isEmpty()
{
    if(s1.empty())
        return true;

    return false;
}




// DEQUEUE costly
void MyQueue::push2(int x)
{
    s1.push(x);
}



int MyQueue::pop2()
{
    int top;

    if(s1.empty() && s2.empty())
    {
        std::cout<<"\nUNDERFLOW\n";
        return -1;
    }

    if(s2.empty())
    {
        while(!s1.empty())
        {
            top = s1.top();
            s1.pop();
            s2.push(top);
        }
    }

    top = s2.top();
    s2.pop();
    return top;
}


int MyQueue::peek2()
{
    if(s1.empty() && s2.empty())
    {
        std::cout<<"\nUNDERFLOW\n";
        return -1;
    }

    if(s2.empty())
    {
        while(!s1.empty())
        {
            int top = s1.top();
            s1.pop();
            s2.push(top);
        }
    }

    return s2.top();
}


bool MyQueue::isEmpty2()
{
    if(s1.empty() && s2.empty())
        return true;

    return false;
}
