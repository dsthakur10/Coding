/*

Design a stack that supports push, pop, top, and RETRIEVING THE MINIMUM ELEMENT IN CONSTANT TIME.

Implement the MinStack class:

MinStack() initializes the stack object.

void push(int val) - pushes the element val onto the stack.
void pop() - removes the element on the top of the stack.
int top() - gets the top element of the stack.
int getMin() - retrieves the minimum element in the stack.


*/


#include<iostream>
#include<stack>


class MyStack
{
    std::stack<int> st;
    std::stack<int> temp;
    int minn;

    public:
    void push(int val);
    void pop();
    int top();
    int getMin();

    public:
    void push2(int val);
    void pop2();
    int top2();
    int getMin2();

};

int main()
{
    int choice, x, flag = 1;
    MyStack *obj = new MyStack();

    obj->push2(5);
    obj->push2(3);
    obj->push2(4);
    obj->push2(1);
    obj->push2(2);


    while(flag)
    {
        std::cout << "\n1. Push\t2. Pop\t3. Top\t4. Minimum:\n";
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
            obj->pop2();
            std::cout <<"\nElement removed\n";
            break;

        case 3:
            x = obj->top2();
            std::cout <<"\n" << x <<" element is at TOP of stack\n";
            break;

        case 4:
            x = obj->getMin2();
            std::cout <<"\nMinimum element in stack = "<< x << "\n";
            break;

        default:
            flag = 0;
            break;
        }
    }

}



                                        // Method-1
void MyStack::push(int val)
{
    if(st.empty())
        minn = val;

     else
        minn = std::min(minn,val);

    st.push(val);
}


void MyStack::pop()
{
    int top;

    if(minn != st.top())
        st.pop();

    else
    {
        st.pop();
        int flag = 1;

        while(!st.empty())
        {
            top = st.top();
            st.pop();
            temp.push(top);

            if(flag == 1)
            {
                minn = top;
                flag = 0;
            }

            else
                minn = std::min(minn,top);

        }

        while(!temp.empty())
        {
            st.push(temp.top());
            temp.pop();
        }
    }
}


int MyStack::top()
{
    return st.top();
}


int MyStack::getMin()
{
    return minn;
}




                                // Method-2
// We are using 2 stacks here. 1st for storing elements. 2nd for storing those elements that are minimum for a particular time being until some other better option is available

void MyStack::push2(int val)
{
    if(st.empty() || val <= getMin2())                  // Initial value in stack
        temp.push(val);

    st.push(val);
}



void MyStack::pop2()
{
    if(st.top() == getMin2())
        temp.pop();

    st.pop();
}



int MyStack::top2()
{
    return st.top();
}



int MyStack::getMin2()
{
    return temp.top();
}
