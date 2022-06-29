/*

Design a stack that supports push, pop, top, and retrieving the minimum element in CONSTANT TIME.

Implement the MinStack class:

MinStack()          -->     initializes the stack object.
void push(int val)  -->     pushes the element val onto the stack.
void pop()          -->     removes the element on the top of the stack.
int top()           -->     gets the top element of the stack.
int getMin()        -->     retrieves the minimum element in the stack.

*/

#include<iostream>
#include<stack>
#include<algorithm>
#include<utility>

using namespace std;

typedef pair<int, int> pi;      // <element, minimum until this element>


// Method-1 --> O(n) space --> Using 2 stacks  (temp stack to keep track of & update minimum element)

class MinStack {

private:
    stack<int> st, temp;

public:

    MinStack() {

    }

    void push(int val) {
        st.push(val);

        if(temp.empty() || val <= temp.top())
            temp.push(val);
    }

    void pop() {
        if(st.top() == temp.top())
            temp.pop();

        st.pop();
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return temp.top();
    }

};



// Method-2 --> O(n) space with 1 stack (We store pairs rather than element alone.) <element, minimum element until now>

class MinStack2{

private:
    stack<pi> st;
    int minimum;

public:

    MinStack() {
        minimum = -1;
    }


    void push(int val)
    {
        if(st.empty())
        {
            minimum = val;
            st.push(make_pair(val,val));
        }

        else if(st.top().second >= val)
        {
            minimum = val;
            st.push(make_pair(val,val));
        }

        else
        {
            st.push(make_pair(val, minimum));
        }
    }


    void pop()
    {
        if(st.top().first == st.top().second)
        {
            st.pop();
            minimum = st.empty() ? -1 : st.top().second;
        }

        else
            st.pop();
    }


    int top()
    {
        return st.top().first;
    }


    int getMin()
    {
        return minimum;
    }

    void printStack()
    {
        stack<pi> mystack = st;

        while(!mystack.empty())
        {
            cout << mystack.top().first << "->" << mystack.top().second << "\n";
            mystack.pop();
        }
    }

};



// Method-3  -->  O(1) space --> Using flag value.

/*

We push flag value onto the stack rather than original value in case current value < minimum.
flag = 2*current - minimum

While popping, check if top < minimum element. If yes, update minimum before popping.
minimum = 2*minimum - top

While retrieving top element, return top only if top > minimum.
Else return minimum

*/

class MinStack3 {

public:
    stack<long> st;
    long minimum;

    MinStack() {
        minimum = -1;
    }


    void push(int val) {
        if(st.empty())
        {
            minimum = val;
            st.push(val);
        }

        else if(val >= minimum)
        {
            st.push(val);
        }

        else if(val < minimum)
        {
            long temp = 2*(long)val - minimum;
            st.push(temp);
            minimum = val;
        }
    }


    void pop() {
        if(st.top() >= minimum)
            st.pop();

        else if(st.top() < minimum)
        {
            long temp = 2*(long)minimum - st.top();
            st.pop();
            minimum = temp;
        }
    }


    int top() {
        if(st.top() >= minimum)
            return st.top();

        else
            return minimum;
    }


    int getMin() {
        return minimum;
    }
};




int main()
{
    MinStack2 obj;

    obj.push(18);
    obj.push(19);
    obj.push(29);
    obj.push(15);
    obj.push(16);
    obj.push(7);
    obj.push(12);
    obj.push(1);

    cout << "\nStack contents:\n";
    obj.printStack();

    cout << "\nMinimum = " << obj.getMin();
    obj.pop();
    cout << "\nMinimum = " << obj.getMin();
    obj.pop();
    cout << "\nMinimum = " << obj.getMin();
    obj.pop();
    cout << "\nMinimum = " << obj.getMin();

    return 0;
}

