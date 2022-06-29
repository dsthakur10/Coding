// FIRST NEGATIVE INTEGER IN EVERY WINDOW of size k

// Given an array A[] of size N and a positive integer K, find the first negative integer for each and every window(contiguous subarray) of size K.
// If window does not contain negative number, return 0


#include<climits>
#include<iostream>
#include<vector>
#include<algorithm>
#include<cmath>
#include<queue>


std::vector<int> printFirstNegativeInteger(std::vector<int> nums, int k);
std::vector<int> printFirstNegativeInteger2(std::vector<int> nums, int k);


int main()
{
    int n,k;
    std::vector<int> nums;

    std::cout << "Enter size of vector: ";
    std::cin >> n;

    std::cout << "Enter the array elements:\n";
    for(int i=0; i<n; i++)
    {
        std::cin >> k;
        nums.push_back(k);
    }

    std::cout << "\nEnter the size of subarray: ";
    std::cin >> k;

    std::vector<int> negatives = printFirstNegativeInteger2(nums,k);

    std::cout << "\n1st negative for every subarray of size "<< k << ":\n";
    for(int i=0; i<negatives.size(); i++)
        std::cout << negatives[i] << " ";

    return 0;
}


std::vector<int> printFirstNegativeInteger(std::vector<int> nums, int k)
{
    std::vector<int> negatives, indices;
    int n = nums.size();

    if(k > n)
    {
        std::cout << "\n\nINVALID";
        return {INT_MIN};
    }

    for(int i=0; i<k; i++)                          // first window
    {
        if(nums[i] < 0)
            indices.push_back(i);
    }

    if(!indices.empty())
        negatives.push_back(nums[indices[0]]);

    else
        negatives.push_back(0);

    for(int i=0; i<n-k; i++)
    {
        if(nums[k+i] < 0)
            indices.push_back(k+i);

        if(!indices.empty() && indices[0] == i)
            indices.erase(indices.begin());


        if(!indices.empty())
            negatives.push_back(nums[indices[0]]);

        else
            negatives.push_back(0);
    }

    return negatives;
}



std::vector<int> printFirstNegativeInteger2(std::vector<int> nums, int k)
{
    std::vector<int> negatives, indices;
    int i,j, n = nums.size();

    if(k > n)
    {
        std::cout << "\n\nINVALID";
        return {INT_MIN};
    }

    i=0;
    j=0;

    while(j < n)
    {
        if(nums[j] < 0)
            indices.push_back(j);

        if(j-i+1 < k)
            j++;

        else
        {
            if(!indices.empty())
                negatives.push_back(nums[indices[0]]);

            else
                negatives.push_back(0);

            if(!indices.empty() && indices[0] == i)
                indices.erase(indices.begin());

            i++;
            j++;
        }
    }

    return negatives;
}
