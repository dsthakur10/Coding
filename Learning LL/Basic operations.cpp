#include<iostream>

class Node
{
public:
    int data;
    Node *next;

    Node()
    {
        data = 0;
        next = NULL;
    }

    Node(int key)
    {
        data = key;
        next = NULL;
    }
};


class SLL
{
public:
    Node *head;

    SLL()
    {
        head = NULL;
    }

    SLL(Node *n)
    {
        head = n;
    }

    Node* nodeExists(int key);
    void appendNode(Node *n);
    void prependNode(Node *n);
    void insertAfter(Node *n, int key);
    void deleteNode(int key);
    void updateNode(int key,int newkey);
    void deleteAll(int key);
    void updateAll(int key,int newkey);
    void displayList();
};


Node* SLL::nodeExists(int key)
{
    Node *temp=head;

    while(temp)
    {
        if(temp->data == key)
            return temp;
        temp = temp->next;
    }

    return NULL;
}


void SLL::appendNode(Node *n)
{
    if(!head)
    {
        head = n;
        std::cout<<"\n\nNode appended";
        return;
    }

    Node *temp = head;
    while(temp->next)
        temp = temp->next;

    temp->next = n;

    std::cout<<"\n\nNode appended";
}


void SLL::prependNode(Node *n)
{
    if(!head)
    {
        head = n;
        std::cout<<"\n\nNode prepended";
        return;
    }

    n->next = head;
    head = n;

    std::cout<<"\n\nNode prepended";
}


void SLL::insertAfter(Node *n, int key)
{
    Node *temp = nodeExists(key);

    if(temp)
    {
        n->next = temp->next;
        temp->next = n;
        std::cout<<"\n\nNode added after node having key = "<<key;
    }

    else
        std::cout<<"\n\nNode with key value = "<<key<<"does not exists";
}


void SLL::deleteNode(int key)
{
    Node *cur,*prev;

    if(head->data == key)
    {
        cur = head;
        head = head->next;
        delete cur;
        std::cout<<"\n\nNode deleted with key = "<<key;
        return;
    }

    cur = head->next;
    prev = head;

    while(cur)
    {
        if(cur->data == key)
        {
            prev->next = cur->next;
            delete cur;
            std::cout<<"\n\nNode deleted with key = "<<key;
            return;
        }

        cur = cur->next;
        prev = prev->next;
    }

    if(!cur)
        std::cout<<"\n\nNode DOES NOT EXIST";
}


void SLL::updateNode(int key,int newkey)
{
    Node* temp = head;

    while(temp)
    {
        if(temp->data == key)
        {
            temp->data = newkey;
            std::cout<<"\n\n Key value updated";
            return;
        }

        temp = temp->next;
    }

    if(!temp)
        std::cout<<"\n\nNode DOES NOT EXIST";
}


void SLL::deleteAll(int key)
{
    int flag = 0;
    Node *cur,*prev;
    cur = head;
    prev = NULL;

    while(cur)
    {
        if(cur->data == key)
        {
            flag = 1;
            if(cur == head)
            {
                head = head->next;
                delete cur;
                cur = head;
            }
            else
            {
               prev->next = cur->next;
               delete cur;
               cur = prev->next;
            }
        }

        else
        {
            prev = cur;
            cur = cur->next;
        }

    }

    if(flag)
        std::cout<<"\n\nALL nodes with key = "<<key<<" deleted";

    else
        std::cout<<"\n\nNode DOES NOT EXIST";
}


void SLL::updateAll(int key, int newkey)
{
    int flag = 0;
    Node* temp = head;

    while(temp)
    {
        if(temp->data == key)
        {
            flag = 1;
            temp->data = newkey;
        }

        temp = temp->next;
    }

    if(flag)
        std::cout<<"\n\n ALL nodes updated";

    else
        std::cout<<"\n\nNode DOES NOT EXIST";
}


void SLL::displayList()
{
    if(!head)
    {
        std::cout<<"Linked list EMPTY";
        return;
    }

    Node *temp = head->next;
    std::cout<<head->data;
    while(temp)
    {
        std::cout<<" -> "<<temp->data;
        temp = temp->next;
    }
}


int main()
{
    SLL s;
    int option,val,k;

    do
    {
        std::cout<<"\n\nFollowing options available. Press 0 to exit.";
        std::cout<<"\n1. Append Node";
        std::cout<<"\n2. Prepend Node";
        std::cout<<"\n3. Insert Node after some required Node";
        std::cout<<"\n4. Delete certain Node";
        std::cout<<"\n5. Delete ALL";
        std::cout<<"\n6. Update certain Node";
        std::cout<<"\n7. Update ALL";
        std::cout<<"\n8. Print Linked List\n";

        std::cin>>option;

        Node *ptr = new Node();

        switch(option)
        {
        case 1:
            std::cout<<"\n\nEnter data:";
            std::cin>>val;
            ptr->data = val;

            s.appendNode(ptr);
            break;

        case 2:
            std::cout<<"\n\nEnter data:";
            std::cin>>val;
            ptr->data = val;

            s.prependNode(ptr);
            break;

        case 3:
            std::cout<<"\n\nEnter data:";
            std::cin>>val;
            ptr->data = val;
            std::cout<<"\nEnter key of existing node after which you want to add new node:";
            std::cin>>k;

            s.insertAfter(ptr,k);
            break;

        case 4:
            std::cout<<"\n\nEnter key value of node to be deleted:";
            std::cin>>val;

            s.deleteNode(val);
            break;

        case 5:
            std::cout<<"\n\nEnter key value of all liking nodes to be deleted:";
            std::cin>>val;

            s.deleteAll(val);
            break;

        case 6:
            std::cout<<"\n\nEnter key value of node to be updated";
            std::cin>>val;
            std::cout<<"\nEnter new value:";
            std::cin>>k;

            s.updateNode(val,k);
            break;

        case 7:
            std::cout<<"\n\nEnter key value of all the liking nodes to be updated";
            std::cin>>val;
            std::cout<<"\nEnter new value:";
            std::cin>>k;

            s.updateAll(val,k);
            break;

        case 8:
            std::cout<<"\n\n---------Linked list--------\n";
            s.displayList();
            break;

        default:
            std::cout<<"\n\nEnter proper option";
            break;
        }

    }while(option);

    return 0;
}
