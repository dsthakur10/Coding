/*
Find k closest elements

    Given a SORTED INTEGER ARRAY arr, two integers k and x, return the k CLOSEST INTEGERS TO x IN THE ARRAY. The result should also be sorted in ascending order.

    An integer a is closer to x than an integer b if:

    |a - x| < |b - x|
            OR
    |a - x| == |b - x| AND a < b

*/



#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
#include<cmath>

std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x);
std::vector<int> findClosestElements2(std::vector<int>& arr, int k, int x);


int main()
{
    //std::vector<int> vec = {3,2,3,1,2,4,5,5,6};
    std::vector<int> vec;
    int n,k,x;

    std::cout<< "Enter size of array: ";
    std::cin >> n;

    std::cout << "\nEnter array elements:\n";
    for(int i=0;i<n;i++)
    {
        std::cin >> k;
        vec.push_back(k);
    }


    std::cout << "\nArray:\n";
    for(int i=0;i<n;i++)
        std::cout << vec[i] << " ";

    std::cout << "\nEnter K-value:";
    std::cin >> k;

    std::cout << "\nEnter X-value:";
    std::cin >> x;

    vec = findClosestElements2(vec,k,x);

    std::cout << "\n\n : " << k << " closest elements to number "<< x << ": ";
    for(int i=0;i<vec.size();i++)
        std::cout << vec[i] << " ";

    return 0;

}



// error in closest only... Correct it to get the final results.

/*
int closest(std::vector<int>& a, int x)
{
    int mid,l,m,r;
    int low=0, high = a.size()-1;

    while(low < high)
    {
        l = 0;
        r = 0;
        mid = (low + high)/2;

        if(mid != 0)
            l = abs(x - a[mid-1]);

        if(mid != a.size()-1)
            r = abs(x - a[mid+1]);

        m = abs(x - a[mid]);
                                            // Identifying the cases is very important

        if(m<=l && m<=r)
            return mid;

        else if(l<m && m<=r)
            high = mid-1;

        else
            low = mid+1;

    }

    return low;

}

*/


/*
int closest(int arr[],int low,int high,int target)
{
    int mid = (low+high)/2;

    if(arr[mid]==target)                                    // return mid if target = mid
        return mid;

    if(target<arr[mid] && target>=arr[mid-1])               //checking if mid & left(mid) are candidates for target
    {
        int d1 = abs(target - arr[mid]);
        int d2 = abs(target - arr[mid-1]);

        return (d1<d2)?mid:mid-1;
    }

    if(target<arr[mid+1] && target>=arr[mid])               //checking if mid & right(mid) are candidates for target
    {
        int d1 = abs(target - arr[mid+1]);
        int d2 = abs(target - arr[mid]);

        return (d1<d2)?mid+1:mid;
    }

    if(target<arr[mid])
        return closest(arr,low,mid-1,target);

    else
        return closest(arr,mid+1,high,target);
}



std::vector<int> findClosestElements(std::vector<int>& arr, int k, int x)
{
    std::vector<int> close;
    int index;

    if(x <= arr[0])
        index = 0;

    else if(x >= arr[arr.size()-1])
        index = arr.size()-1;

    else
        index = closest(arr,0,arr.size()-1,x);

    std::cout << "\nIndex = " << index << "\n";

    if(index == 0)
    {
        for(int i=0; i<k; i++)
            close.push_back(arr[i]);
    }


    else if(index == arr.size()-1)
    {
        for(int i=index; i>index-k ; i--)
            close.push_back(arr[i]);

        std::reverse(close.begin(),close.end());
    }


    else
    {
        int counter = k;
        int l = index-1, r = index+1;

        close.push_back(arr[index]);
        counter--;

        while(counter > 0)
        {
            if(l < 0)                       // left side of index exhausted
            {
                close.push_back(arr[r]);
                r++;
                counter--;
            }

            else if(r > arr.size()-1)
            {
                close.push_back(arr[l]);
                l--;
                counter--;
            }

            else
            {
                if((arr[index] - arr[l]) > (arr[r] - arr[index]))
                {
                    close.push_back(arr[r]);
                    r++;
                    counter--;
                }

                else if((arr[index] - arr[l]) < (arr[r] - arr[index]))
                {
                    close.push_back(arr[l]);
                    l--;
                    counter--;
                }

                else
                {
                    if(counter >= 2)
                    {
                        close.push_back(arr[l]);
                        close.push_back(arr[r]);
                        r++;
                        l--;
                        counter = counter-2;
                    }

                    else
                    {
                        close.push_back(arr[l]);
                        l--;
                        counter--;
                    }
                }

            }
        }               // end of while

        std::sort(close.begin(), close.end());

    }

    return close;
}


*/



// ----------------- Method-2 -------------------

/*
    Idea is to use heap. But how ?
    Taking reference from "k-largest numbers" problem, there we used min-heap of size k+1 & as soon as heap size became k+1, we popped of minimum/top element.
    In the end we just left with k-largest elements in the heap which is what we wanted.

    Here we cannot simply take any numbers in the beginning to start with. Need to modify the array to convert it to heap problem.

    Subtract all the array elements from X. Now we can consider applying heap to this modified array & can pick those elements which are close to X by just seeing their new value

    But we want to return original array. So what we can do is apply heap elements in pair (absolute value, value) & then return just their value using absolute value.


*/

std::vector<int> findClosestElements2(std::vector<int>& arr, int k, int x)
{
    std::priority_queue<std::pair<int,int>> pq;
    std::vector<int> absolute;

    for(int i=0; i<arr.size(); i++)
        absolute.push_back(abs(arr[i] - x));

    int i=0;

    while(i < arr.size())
    {
        pq.push(std::make_pair(absolute[i],arr[i]));

        if(pq.size() == k+1)
            pq.pop();

        i++;
    }

    absolute.clear();

    while(!pq.empty())
    {
        absolute.push_back(pq.top().second);
        pq.pop();
    }

    std::sort(absolute.begin(), absolute.end());
    return absolute;
}
