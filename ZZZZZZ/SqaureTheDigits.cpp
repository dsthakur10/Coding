
// Output should be the first number that repeats in the process

#include<bits/stdc++.h>

using namespace std;


int findRepeatedElement(int n, unordered_set<int>& unique)
{
    int sum = 0, rem;
    int number = n;
    while(number > 0)
    {
        rem = number % 10;
        number = number / 10;

        sum += rem*rem;
    }


    if(unique.find(sum) != unique.end())
        return sum;

    cout << "\nsum = " << sum;
    unique.insert(sum);
    return findRepeatedElement(sum, unique);
}

int sqaureTheDigits(int n)
{
    unordered_set<int> unique;
    return findRepeatedElement(n, unique);
}


int main()
{
    int number;

    cout << "Enter number:";
    cin >> number;

    cout << "\n\nSquare digit number = " << sqaureTheDigits(number);
}
