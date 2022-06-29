// Implement next permutation, which rearranges numbers into the lexicographically NEXT GREATER PERMUTATION of numbers.

// If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).

// NOTE : The replacement must be in place and use only constant extra memory.


#include<iostream>
#include<vector>
#include<algorithm>
#include<climits>

void solution1(std::vector<int>& nums);


int main()
{
    std::vector<int> myvec = {1,2,4,3,1};
    //std::vector<int> myvec = {1,2,3,4,1};
    //std::vector<int> myvec = {1,1,5};
    //std::vector<int> myvec = {1,4,1,1,1};
    //std::vector<int> myvec = {5,4,3,1,2,1};
    //std::vector<int> myvec = {2,1};
    //std::vector<int> myvec = {2,3};


    std::cout<<"\nBEFORE: ";
    for(int i=0;i<myvec.size();i++)
        std::cout<<myvec[i] <<" ";

    solution1(myvec);

    std::cout<<"\n\nAFTER: ";
    for(int i=0;i<myvec.size();i++)
        std::cout<<myvec[i] <<" ";
}


void solution1(std::vector<int>& nums)
{
    if(nums.size() == 1)
        return;

    int index=-1,next;
    for(int i=nums.size()-1;i>0;i--)                    // find the first index from the end where left < right. Below this index,
    {                                                   // no element is to be arranged.
        if(nums[i-1]<nums[i])
        {
            index = i-1;
            break;
        }
    }

    if(index==-1)                                       // array is reverse sorted (descending). Return sorted array (ascending)
    {
        sort(nums.begin(),nums.end());
        return;
    }

    std::cout<<"\nIndex = "<<index;

    //int temp = INT_MAX;
    for(int i=index+1;i<nums.size();i++)                // find the array element which is just greater than nums[index] to swap it with
    {                                                   // nums[index]. Since array is descending from index+1, we need to locate last
        if(nums[i]>nums[index])                         // element with value > nums[index].
            next = i;
    }
    std::cout<<"\nNext = "<<next<<std::endl;

    std::swap(nums[next],nums[index]);

    for(int i=0;i<nums.size();i++)
        std::cout<<nums[i] <<" ";

    reverse(nums.begin()+index+1,nums.end());           // We need smallest permutation after swapping just larger number with nums[index]
                                                        // reverse the array from index+1 to end.

/*  WHY REVERSE & NOT SORT ?

    Because after swapping, elements gets arranged in descending order since nums[next] is just greater than nums[index] in the range.
    reverse() takes O(n) time compared to O(nlogn) by sort().

*/
}
