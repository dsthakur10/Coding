#include <iostream>
using namespace std;

class Employee{

private:
    string name;
    string company;
    int age;

public:

    Employee(){

    }

    Employee(string name, string company, int age)
    {
        this->name = name;
        this->company = company;
        this->age = age;
    }

    void setName(string name){
        this->name = name;
    }

    string getName(){
        return name;
    }

    void setCompany(string company){
        this->company = company;
    }

    string getCompany(){
        return company;
    }

    void setAge(int age){

        if(age >= 18)
            this->age = age;
    }

    int getAge(){
        return age;
    }

    void introduceYourself(){
        cout << "\nName = " << name << " Company = " << company << " Age = " << age;
    }
};

int main()
{
    Employee emp1("Devendra", "FreeCodeCamp", 24);
    Employee emp2;

    //emp1.age; --> gives error

    emp2.setName("Kamya");
    emp2.setCompany("Amazon");
    emp2.setAge(18);

    emp1.introduceYourself();
    emp2.introduceYourself();

    emp1.setAge(17);
    cout << "\nAge of " << emp1.getName() << " = " << emp1.getAge();

    emp1.setAge(27);
    cout << "\nAge of " << emp1.getName() << " = " << emp1.getAge();

    return 0;
}

