// Given an array of distinct integers candidates and a target, return a list of all unique combinations of candidates where the chosen numbers sum to target.
// You may return the combinations in any order.

// SAME NUMBER MAY BE CHOSEN FROM CANDIDATES AN UNLIMITED NUMBER OF TIMES.
// Two combinations are unique if the frequency of at least one of the chosen numbers is different.

// It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.


std::vector<std::vector<int>> findWays(std::vector<int> candidates, int startIndex, int target);

std::vector<std::vector<int>> solution1(std::vector<int> candidates, int target);

std::vector<std::vector<int>> solution2(std::vector<int> candidates, int target);


int main()
{
    int target;
    std::vector<int> myvec = {2,3,6,7};
    //std::vector<int> myvec = {};
    //std::vector<int> myvec = {};
    //std::vector<int> myvec = {};
    //std::vector<int> myvec = {};
    //std::vector<int> myvec = {};
    //std::vector<int> myvec = {};

    std::cout<<"Enter the target:";
    std::cin>>target;

    std::vector<std::vector<int>> cand = solution1(myvec,target);

    std:cout<<"\n\nCombination sum:\n";
    for(int i=0;i<cand.size();i++)
    {
        for(int j=0;j<cand[i].size();j++)
            std::cout<<cand[i][j]<<" ";
        std::cout<<"\n";
    }

}


std::vector<std::vector<int>> solution1(std::vector<int>& candidates, int target)
{
    std::sort(candidates.begin(),candidates.end());

    return findWays(candidates,0,target);

    int low = 0, high = candidates.size()-1, mid;

    while(low <= high)
    {
        mid = (low + high)/2;

        if(candidates[mid] == target)
            end = mid;

        else if(candidates[mid] < target )
    }
}


std::vector<std::vector<int>> findWays(std::vector<int> candidates, int startIndex, int target)
{
    if(target == 1)
    {
        if(candidates[0] == 1)
            return {{1}};

        else
            return {};
    }


    std::vector<std::vector<int>> cand;
    std::vector<std::vector<int>> temp;

    int mod,div;

    for(int i=startIndex; i<candidates.size(); i++)
    {
        mod = target%candidates[i];
        div = target/candidates[i];

        if(mod == 0)
        {
            std::vector<int> row;
            row.insert(row.begin(),div,candidates[i]);
            cand.push_back(row);
            row.clear();
        }


        for(int j=div;j>=1;j--)
        {
            int sub = target - candidates[i]*j;

            if(sub!=0)
            {
                temp = findWays(candidates,i+1,sub);

                for(int k = 0; k<temp.size();k++)
                {
                    temp[k].insert(temp[k].begin(),j,candidates[i]);
                    cand.push_back(temp[k]);
                }
            }
        }
    }

    return cand;

}

