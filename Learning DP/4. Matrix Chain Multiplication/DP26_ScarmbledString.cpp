/*

Given two strings S1 and S2 of equal length, the task is to determine if S2 is a scrambled form of S1.

Scrambled string:
Given string str, we can represent it as a binary tree by partitioning it into two non-empty substrings recursively.

Note: Scrambled string is not same as an Anagram

Below is one possible representation of str = “coder”:


    coder
   /    \
  co    der
 / \    /  \
c   o  d   er
           / \
          e   r

To scramble the string, we may choose any non-leaf node and swap its two children.
Suppose, we choose the node “co” and swap its two children, it produces a scrambled string “ocder”.


    ocder
   /    \
  oc    der
 / \    /  \
o   c  d   er
           / \
          e   r

Thus, “ocder” is a scrambled string of “coder”.

Similarly, if we continue to swap the children of nodes “der” and “er”, it produces a scrambled string “ocred”.


    ocred
   /    \
  oc    red
 / \    /  \
o   c  re  d
       / \
      r   e

Thus, “ocred” is a scrambled string of “coder”.


Examples:

Input: S1=”coder”, S2=”ocder”
Output: Yes

Explanation:
“ocder” is a scrambled form of “coder”

Input: S1=”abcde”, S2=”caebd”
Output: No

Explanation:
“caebd” is not a scrambled form of “abcde”

*/



#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<climits>
#include<unordered_map>
#include<algorithm>

static int dp[101][101][101];
static std::unordered_map<std::string, bool> mp;


bool scrambledStringRecursive(std::string str1, std::string str2);
int scrambledString(std::string str1, std::string str2, int s1, int s2, int len);           // Top_Down memoization (matrix)
bool scrambledString2(std::string str1, std::string str2);                                  // Top_Down memoization (map)
bool scrambledString3(std::string str1, std::string str2);                                  // Bottom-Up


int main()
{
    memset(dp, -1, sizeof(dp));

    std::string str1, str2;
    std::cout << "\nEnter 2 strings: \n";
    std::cin >> str1 >> str2;

    if(str1.size() != str2.size())
    {
        std::cout << "\nError --- String length NOT same...";
        return 0;
    }

    bool flag = scrambledStringRecursive(str1, str2);
    std::cout << "\n\nRECURSIVE: = \"" << str1 << "\" is scrambled string of \"" << str2 << "\" = "<< std::boolalpha << flag << "\n";

    int counter = scrambledString(str1, str2, 0, 0, str1.size());
    std::cout << "\n\nTOP-DOWN ( 3D - Matrix ): = \"" << str1 << "\" is scrambled string of \"" << str2 << "\" = "<< counter << "\n";

    flag = scrambledString2(str1, str2);
    std::cout << "\n\nTOP-DOWN ( MAP ): = \"" << str1 << "\" is scrambled string of \"" << str2 << "\" = "<< std::boolalpha << flag << "\n";

/*
    for(auto it = mp.begin(); it != mp.end(); it++)
        std::cout << "\n" << it->first << " --> " << it->second ;
*/

    flag = scrambledString3(str1, str2);
    std::cout << "\n\nBOTTOM-UP: = \"" << str1 << "\" is scrambled string of \"" << str2 << "\" = "<< std::boolalpha << flag << "\n";


    return 0;
}



bool scrambledStringRecursive(std::string A, std::string B)
{
    if(A == B)                                              // if both substrings are equal --> simply return TRUE
        return true;

    if(A.size() <= 1)                                       // if length=1 & still character does not match, return false
        return false;

    int n = A.size();
    bool flag = false;

    std::string tempA = A;
    std::string tempB = B;

    sort(tempA.begin(), tempA.end());
    sort(tempB.begin(), tempB.end());

    if(tempA != tempB)
        return false;

    for(int k=1; k<n; k++)                           // partitions are made randomly such that minimum length of substring must be 1
    {

        bool c1 = scrambledStringRecursive(A.substr(0,k), B.substr(0,k)) && scrambledStringRecursive(A.substr(k, n-k), B.substr(k, n-k));                 // NO swap
        bool c2 = scrambledStringRecursive(A.substr(0,k), B.substr(n-k, k)) && scrambledStringRecursive(A.substr(k, n-k), B.substr(0, n-k));              // swap

        if(c1 || c2)
        {
            flag = true;
            break;
        }
    }

    return flag;
}



int scrambledString(std::string A, std::string B, int index1, int index2, int len)
{
    std::string subA = A.substr(index1,len);
    std::string subB = B.substr(index2,len);

    if(subA == subB)                                              // if both substrings are equal --> simply return TRUE
        return 1;

    if(subA.size() <= 1)                                       // if length=1 & still character does not match, return false
        return 0;

    if(dp[index1][index2][len] != -1)
        return dp[index1][index2][len];

    int n = subA.size();
    int flag = 0;

    std::string tempA = subA;
    std::string tempB = subB;

    sort(tempA.begin(), tempA.end());
    sort(tempB.begin(), tempB.end());

    if(tempA != tempB)
    {
        dp[index1][index2][len] = 0;
        return 0;
    }

    for(int k=1; k<len; k++)                           // partitions are made randomly such that minimum length of substring must be 1
    {
        int flag1, flag2, flag3, flag4;

        flag1 = (dp[index1][index2][k] != -1) ? dp[index1][index2][k] : scrambledString(A, B, index1, index2, k);
        flag2 = (dp[index1+k][index2+k][len-k] != -1) ? dp[index1+k][index2+k][len-k] : scrambledString(A, B, index1+k, index2+k, len-k);

        flag3 = (dp[index1][index2+len-k][k] != -1) ? dp[index1][index2+len-k][k] : scrambledString(A, B, index1, index2+len-k , k);
        flag4 = (dp[index1+k][index2][len-k] != -1) ? dp[index1+k][index2][len-k] : scrambledString(A, B, index1+k, index2, len-k);

        if((flag1 && flag2) || (flag3 && flag4))
        {
            flag = 1;
            break;
        }
    }

    dp[index1][index2][len] = flag;
    return flag;

}



bool scrambledString2(std::string A, std::string B)
{
    std::string str = A + "_" + B;

    if(A == B)                                              // if both substrings are equal --> simply return TRUE
        return true;

    if(A.size() <= 1)                                       // if length=1 & still character does not match, return false
        return false;

    if(mp.find(str) != mp.end())
        return mp[str];

    int n = A.size();
    bool flag = false;

    std::string tempA = A;
    std::string tempB = B;

    sort(tempA.begin(), tempA.end());
    sort(tempB.begin(), tempB.end());

    if(tempA != tempB)
    {
        mp[str] = false;
        return false;
    }

    for(int k=1; k<n; k++)                           // partitions are made randomly such that minimum length of substring must be 1
    {
        std::string S1 = A.substr(0,k) + "_" + B.substr(0,k);
        std::string S2 = A.substr(k,n-k) + "_" + B.substr(k, n-k);
        std::string S3 = A.substr(0,k) + "_" + B.substr(n-k, k);
        std::string S4 = A.substr(k, n-k) + "_" + B.substr(0, n-k);

        bool flag1, flag2, flag3, flag4;

        flag1 = (mp.find(S1) != mp.end()) ? mp[S1] : scrambledString2(A.substr(0,k), B.substr(0,k));
        flag2 = (mp.find(S2) != mp.end()) ? mp[S2] : scrambledString2(A.substr(k, n-k), B.substr(k, n-k));

        flag3 = (mp.find(S3) != mp.end()) ? mp[S3] : scrambledString2(A.substr(0,k), B.substr(n-k, k));
        flag4 = (mp.find(S4) != mp.end()) ? mp[S4] : scrambledString2(A.substr(k, n-k), B.substr(0, n-k));

        if((flag1 && flag2) || (flag3 && flag4))
        {
            flag = true;
            break;
        }
    }

    mp[str] = flag;
    return mp[str];

}



bool scrambledString3(std::string A, std::string B)
{
    int n = A.size();
    bool dp[n+1][n+1][n+1];

    for(int i=1; i<n+1; i++)
    {
        for(int j=1; j<n+1; j++)
        {
            if(A[i-1] == B[j-1])
                dp[i][j][1] = true;

            else
                dp[i][j][1] = false;
        }

    }

    for(int l=2; l<n+1; l++)
    {
        for(int i=1; i<=n-l+1; i++)
        {
            for(int j=1; j<=n-l+1; j++)
            {
                bool flag = false;
                for(int k=1; k<l ; k++)
                {
                    if((dp[i][j][k] && dp[i+k][j+k][l-k]) || (dp[i][j+l-k][k] && dp[i+k][j][l-k]))
                    {
                        flag = true;
                        break;
                    }
                }

                dp[i][j][l] = flag;
            }
        }
    }

    return dp[1][1][n];
}
