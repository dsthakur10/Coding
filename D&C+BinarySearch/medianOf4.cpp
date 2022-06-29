#include <iostream>
using namespace std;


float medianOfFour(int a,int b,int c,int d)
{
    float k;

    if(a<b)                                     // Level-1
    {
        if(b<c)                                     // Level-2
        {
            if(c<d)                                     // Level-3
                k = (b+c)/2.0;

            else                                        // Level-3
                k = (b + (a>d?a:d))/2.0;
        }

        else                                        // Level-2
        {
            if(c<d)                                     // Level-3
            {
                if(d<b)                                     // Level-4
                    k = (d + (a>c?a:c))/2.0;

                else                                        // Level-4
                    k = (b + (a>c?a:c))/2.0;
            }

            else                                        // Level-3
                k = (c + (a>d?a:d))/2.0;
        }
    }

    else                                        // Level-1
    {
        if(b<c)                                     // Level-2
        {
            if(c<d)                                     // Level-3
                k = (c + (a>d?d:a))/2.0;

            else                                        // Level-3
            {
                if(d<b)                                     // Level-4
                    k = (b + (a>c?c:a))/2.0;

                else                                        // Level-4
                    k = (d + (a>c?c:a))/2.0;
            }
        }

        else                                        // Level-2
        {
            if(c<d)                                     // Level-3
                k = (b + (a>d?d:a))/2.0;

            else                                        // Level-3
                k = (b+c)/2.0;
        }
    }

    return k;
}



int main()
{
    int a,b,c,d;

    cout<<"Enter 4 numbers in any order: "<<endl;

    cin>>a;
    cin>>b;
    cin>>c;
    cin>>d;

    float median = medianOfFour(a,b,c,d);

    cout<<endl<<"MEDIAN = "<<median;
    return 0;
}
