#include <iostream>
using namespace std;

class Employee{

public:
    string name;
    string company;
    int age;

    Employee(string name, string company, int age)
    {
        this->name = name;
        this->company = company;
        this->age = age;
    }

    void introduceYourself(){
        cout << "\nName = " << name << " Company = " << company << " Age = " << age;
    }
};

int main()
{
    Employee emp1("Devendra", "FreeCodeCamp", 24);
    Employee emp2("Dev", "Amazon", 18);

    emp1.introduceYourself();
    emp2.introduceYourself();

    return 0;
}
