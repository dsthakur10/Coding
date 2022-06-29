
// Stack using priority queue

#include<iostream>
#include<stack>
#include<queue>
#include<vector>
#include<algorithm>
#include<climits>

using namespace std;
typedef pair<int, int> pi;


class Stack{

private:
    priority_queue<pi> pq;
    int index;
public:

    Stack(){
        index = -1;
    }


    void push(int val){
        index++;
        pq.push(make_pair(index, val));
    }


    void pop(){
        if(pq.empty())
        {
            cout << "\nWRONG operation... Stack Empty !!!";
            return;
        }

        pq.pop();
        index--;
    }


    int top(){
        if(pq.empty())
        {
            cout << "\nWRONG operation... Stack Empty !!!";
            return INT_MIN;
        }

        return pq.top().second;
    }


    void content(){
        if(pq.empty())
        {
            cout << "\nWRONG operation... Stack Empty !!!";
            return;
        }

        priority_queue<pi> copiedpq = pq;
        while(!copiedpq.empty())
        {
            cout << copiedpq.top().first << "-->" << copiedpq.top().second << "\n";
            copiedpq.pop();
        }
    }
};


int main()
{
    Stack obj;
    int ch;

    do{
        cout << "\nOperations allowed: ";
        cout << "\n 1. PUSH element \n 2. POP element \n 3. Retrieve TOP element \n 4. Stack contents \n 5. EXIT";
        cout << "\n Enter your choice: ";
        cin >> ch;

        switch(ch)
        {
        case 1:
            int x;
            cout << "\n\nEnter element to push onto stack: ";
            cin >> x;
            obj.push(x);
            cout << "\nElement pushed";
            break;

        case 2:
            obj.pop();
            cout << "\nElement removed";
            break;

        case 3:
            cout << "\nTop element = " << obj.top();
            break;

        case 4:
            cout << "\nStack contents:\n";
            obj.content();
            break;

        case 5:
            cout << "\n\nEXITING.....";
            break;
        }

    }while(ch != 5);
}
