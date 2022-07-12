
/*
Given n cuboids where the dimensions of the ith cuboid is cuboids[i] = [widthi, lengthi, heighti] (0-indexed).
Choose a subset of cuboids and place them on each other.

You can place cuboid i on cuboid j if widthi <= widthj and lengthi <= lengthj and heighti <= heightj.
You can REARRANGE any cuboid's dimensions by rotating it to put it on another cuboid.

Return the maximum height of the stacked cuboids.

Example 1:
Input: cuboids = [[50,45,20],[95,37,53],[45,23,12]]
Output: 190
Explanation:
Cuboid 1 is placed on the bottom with the 53x37 side facing down with height 95.
Cuboid 0 is placed next with the 45x20 side facing down with height 50.
Cuboid 2 is placed next with the 23x12 side facing down with height 45.
The total height is 95 + 50 + 45 = 190.

Example 2:
Input: cuboids = [[38,25,45],[76,35,3]]
Output: 76
Explanation:
You can't place any of the cuboids on the other.
We choose cuboid 1 and rotate it so that the 35x3 side is facing down and its height is 76.

Example 3:
Input: cuboids = [[7,11,17],[7,17,11],[11,7,17],[11,17,7],[17,7,11],[17,11,7]]
Output: 102
Explanation:
After rearranging the cuboids, you can see that all cuboids have the same dimension.
You can place the 11x7 side down on all cuboids so their heights are 17.
The maximum height of stacked cuboids is 6 * 17 = 102.

*/



// LOGIC --> Greedy + DP

/*
We are asked to make a stack of all the boxes such that a box has to have lower dimensions than its base box,
and the twist is that we can rotate the cuboidal box as per our need.

    "width[i] <= width[j] and length[i] <= length[j] and height[i] <= height[j]"

1. SET THE MAXIMUM OF ALL 3 DIMENSIONS OF BOX AS ITS HEIGHT.

    We need maximum height of each box --> We can also rotate box dimensions
    --> We have to select the maximum of all the 3 dimensions --> Sort every box to get maximum height as box[2]

    After sorting we will have --> [low, mid, high] :
        --> low is lowest dimension of box
        --> mid is middle dimension of box
        --> high is biggest dimension of box

    --> cuboidal[i][2] is the highest dimension for every box & now we can treat it as height of the box-i


2. SORT THE BOXES

     To have a stack with max height, lets sort the cuboids first. We sort them all based on our static comparator
     function which ensures that a box with lower dimesions is put before the one having higher dimesions.

     --> This sorting is done to find the longest increasing subsequence, which will eventually consist of all
         the boxes that will be piled up.


*/



// There's no need for comparator functio   n as sort() in C++ by default sorts the vector by column-1 & tiebreaker

static bool comp(const vector<int>& a, const vector<int>& b)
{
    if(a[0] < b[0])
        return true;

    else if(a[0] == b[0])
    {
        if(a[1] < b[1])
            return true;

        else if(a[1] == b[1])
        {
            if(a[2] < b[2])
                return true;
            else
                return false;
        }

        else
            return false;
    }

    return false;
}


int maxHeight(vector<vector<int>>& cuboids) {

    int n = cuboids.size();

    for(int i=0; i<n; i++)
        sort(cuboids[i].begin(), cuboids[i].end());         // sort the 3 dimensions for every box

    //sort(cuboids.begin(), cuboids.end(), comp);             // sort all the boxes
    sort(cuboids.begin(), cuboids.end());

    return LIS(cuboids, n);
}

int LIS(vector<vector<int>>& cuboids, int n)
{
    int maxHeight = 0;
    int dp[n];

    for(int i=0; i<n; i++)
    {
        dp[i] = cuboids[i][2];  // height
        for(int j=0; j<i; j++)
        {
            if(cuboids[j][0] <= cuboids[i][0] && cuboids[j][1] <= cuboids[i][1] && cuboids[j][2] <= cuboids[i][2])
                dp[i] = max(dp[i], cuboids[i][2] + dp[j]);
        }

        maxHeight = max(maxHeight, dp[i]);
    }

    return maxHeight;
}
