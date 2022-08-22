#include <iostream>
using namespace std;


// Whoever decides to extend abstract class, needs to provide the implementation of
// virtual method (pure virtual function)

class AbstractEmployee{

    // pure virtual function / abstract function
    virtual void AskForPromotion() = 0;
};

class Employee : AbstractEmployee {

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

    void AskForPromotion()
    {
        if(age > 30)
            cout << "\n" << name << ", got promoted";

        else
            cout << "\n" << name << ", Wait for " << 30 - age << " years";
    }

};





int main()
{
    Employee emp1("Devendra", "FreeCodeCamp", 24);
    Employee emp2("Kamya", "Amazon", 18);

    emp1.setAge(27);
    cout << "\nAge of " << emp1.getName() << " = " << emp1.getAge();
    emp1.AskForPromotion();

    emp1.setAge(35);
    cout << "\nAge of " << emp1.getName() << " = " << emp1.getAge();
    emp1.AskForPromotion();

    return 0;
}



