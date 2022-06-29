/*

    Matrix chain multiplication

Given a sequence of matrices, find the most efficient way to multiply these matrices together. The problem is not actually to perform the multiplications,
but merely to decide in which order to perform the multiplications.

We have many options to multiply a chain of matrices because matrix multiplication is associative.
In other words, no matter how we parenthesize the product, the result will be the same. For example, if we had four matrices A, B, C, and D, we would have:

((AB)C)D = ((A)(BC))D = A((BC)D) = A(B(CD)) = (AB)(CD)

EXAMPLES:

Input: arr[] = {40, 20, 30, 10, 30}
Output: 26000

There are 4 matrices of dimensions 40x20, 20x30, 30x10 and 10x30.
Let the input 4 matrices be A, B, C and D.  The minimum number of mmultiplications are obtained by putting parenthesis in following way

(A(BC))D --> 20*30*10 + 40*20*10 + 40*10*30


Input: arr[] = {10, 20, 30, 40, 30}
Output: 30000
There are 4 matrices of dimensions 10x20, 20x30, 30x40 and 40x30.
Let the input 4 matrices be A, B, C and D.  The minimum number of multiplications are obtained by putting parenthesis in following way

((AB)C)D --> 10*20*30 + 10*30*40 + 10*40*30


*/



#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<climits>

static int dp[101][101];

int MCM(std::vector<int> arr, int i, int j);                   // Top_Down memoization
int MCM2(std::vector<int> arr, int n);                  // Bottom-Up


int main()
{
    memset(dp, -1, sizeof(dp));
    int n;
    std::vector<int> arr;

    std::cout << "\nEnter number of matrices + 1: ";
    std::cin >> n;

    int x;
    std::cout << "\nEnter dimensions of matrices: ";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        arr.push_back(x);
    }

    int cost = MCM(arr, 1, n-1);
    std::cout << "\n\nTOP-DOWN: Minimum #multiplications = " << cost << "\n";

    cost = MCM2(arr, n);
    std::cout << "\n\nBOTTOM-UP: Minimum #multiplications = " << cost;

    return 0;
}


int MCM(std::vector<int> arr, int i, int j)
{
    if(i >= j)
        return 0;

    if(dp[i][j] != -1)
        return dp[i][j];

    int minimum = INT_MAX;

    int temp;
    for(int k=i; k<j; k++)
    {
        temp = MCM(arr,i,k) + MCM(arr,k+1,j) + arr[i-1]*arr[k]*arr[j];

        minimum = std::min(minimum, temp);
    }

    dp[i][j] = minimum;

    return dp[i][j];
}


// For simplicity of the program, one extra row and one extra column are allocated in dp[][]. 0TH ROW AND 0TH COLUMN OF dp[][] ARE NOT USED

// dp[i, j] = Minimum number of scalar multiplications needed to compute the matrix A[i]A[i+1]...A[j] = A[i..j] where dimension of A[i] is p[i-1] x p[i]


int MCM2(std::vector<int> arr, int n)
{
    int dp[n][n], minimum;

    for(int i=1; i<n ; i++)
        dp[i][i] = 0;

    for(int l=2; l<n; l++)
    {
        for(int i=1; i<n-l+1 ; i++)
        {
            int j = i+l-1;

            minimum = INT_MAX;
            for(int k=i; k<j; k++)
            {
                int temp = dp[i][k] + dp[k+1][j] + arr[i-1]*arr[k]*arr[j];

                minimum = std::min(minimum, temp);
            }

            dp[i][j] = minimum;
            //std::cout << dp[i][j] << " ";
        }

        //std::cout << "\n";
    }

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
            std::cout << dp[i][j] <<" ";
        std::cout << "\n";
    }

    return dp[1][n-1];
}
