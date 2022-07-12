/*

Given a boolean expression with following symbols.

Symbols
    'T'     ---> true
    'F'     ---> false

And following operators filled between symbols

Operators
    &       ---> boolean AND
    |       ---> boolean OR
    ^       ---> boolean XOR

Count the NUMBER OF WAYS WE CAN PARENTHESIZE THE EXPRESSION SO THAT THE VALUE OF EXPRESSION EVALUATES TO TRUE.
Let the input be in form of two arrays one contains the symbols (T and F) in order and the other contains operators (&, | and ^}

Examples:

Input: symbol[]    = {T, F, T}
       operator[]  = {^, &}

Output: 2
The given expression is "T ^ F & T", it evaluates true in 2 ways "((T ^ F) & T)" and "(T ^ (F & T))"


Input: symbol[]    = {T, F, F}
       operator[]  = {^, |}

Output: 2
The given expression is "T ^ F | F", it evaluates true in 2 ways "( (T ^ F) | F )" and "( T ^ (F | F) )".


Input: symbol[]    = {T, T, F, T}
       operator[]  = {|, &, ^}

Output: 4
The given expression is "T | T & F ^ T", it evaluates true in 4 ways ((T|T)&(F^T)), (T|(T&(F^T))), (((T|T)&F)^T) and (T|((T&F)^T)).

*/



#include<iostream>
#include<vector>
#include<string>
#include<cstring>
#include<climits>
#include<unordered_map>

static int dp[101][101][2];
static std::unordered_map<std::string, int> mp;

int booleanParenthesization(std::string expr, int i, int j, int isTrue);                                                // Top_Down memoization (3D matrix)
int booleanParenthesization2(std::string expr, int i, int j, int isTrue);                                               // Top_Down memoization (map)
int booleanParenthesization3(std::vector<char> symbols, std::vector<char> operators, int n);                            // Bottom-Up


int main()
{
    memset(dp, -1, sizeof(dp));
    //mp.clear();

    std::vector<char> symbols, operators;
    int n;
    char x;

    std::cout << "\nEnter #symbols: ";
    std::cin >> n;

    std::cout << "\nEnter symbols (T or F): ";
    for(int i=0; i<n; i++)
    {
        std::cin >> x;
        symbols.push_back(x);
    }


    std::cout << "\nEnter operators (& or | or ^): ";
    for(int i=0; i<n-1; i++)
    {
        std::cin >> x;
        operators.push_back(x);
    }


    std::string expr;

    int i;
    for(i=0; i<n-1; i++)
    {
        expr.push_back(symbols[i]);
        expr.push_back(operators[i]);
    }

    expr.push_back(symbols[i]);

    //std::cout << "EXPR = "<< expr;

    int ways = booleanParenthesization(expr, 0, expr.size()-1, 1);
    std::cout << "\n\nTOP-DOWN: Total #ways (3D matrix) = " << ways << "\n";

    ways = booleanParenthesization2(expr, 0, expr.size()-1, 1);
    std::cout << "\n\nTOP-DOWN: Total #ways (Map) = " << ways << "\n";

    ways = booleanParenthesization3(symbols, operators, n);
    std::cout << "\n\nBOTTOM-UP: Total #ways = " << ways << "\n";

    std::cout << "\n";

    for(auto it = mp.begin(); it != mp.end(); it++)
        std::cout << it->first << " --> " << it->second << std::endl;

    std::cout << "Map size = " << mp.size();

    return 0;

}




int booleanParenthesization(std::string expr, int i, int j, int isTrue)
{
    if(i > j)
        return 0;

    if(i == j)
    {
        if(isTrue == 1)
            return (expr[i] == 'T');

        else
            return (expr[i] == 'F');
    }

    if(dp[i][j][isTrue] != -1)
        return dp[i][j][isTrue];

    int ans = 0;
    for(int k = i+1; k < j; k = k+2)
    {
        int lt, lf, rt, rf;

        lt = (dp[i][k-1][1] == -1) ? booleanParenthesization(expr, i, k-1, 1) : dp[i][k-1][1];

        lf = (dp[i][k-1][0] == -1) ? booleanParenthesization(expr, i, k-1, 0) : dp[i][k-1][0];

        rt = (dp[k+1][j][1] == -1) ? booleanParenthesization(expr, k+1, j, 1) : dp[k+1][j][1];

        rf = (dp[k+1][j][0] == -1) ? booleanParenthesization(expr, k+1, j, 0) : dp[k+1][j][0];


        if(expr[k] == '&')
        {
            if(isTrue == 1)
                ans += lt * rt;

            else
                ans += lt * rf + lf * rt + lf * rf;
        }


        else if(expr[k] == '|')
        {
            if(isTrue == 1)
                ans += lt * rt + lt * rf + lf * rt;

            else
                ans += lf * rf;
        }


        else if(expr[k] == '^')
        {
            if(isTrue == 1)
                ans += lt * rf + lf * rt;

            else
                ans += lt * rt + lf * rf;
        }
    }

    dp[i][j][isTrue] = ans;

    return ans;
}




int booleanParenthesization2(std::string expr, int i, int j, int isTrue)
{
    std::string str = std::to_string(i) + "_" + std::to_string(j) + "_" + std::to_string(isTrue);

    if(mp.find(str) != mp.end())       // this check is redundant & useless since we have already checked the existence of str in left & right partitions of some other problem
    {
        std::cout << "Hey...\n";
        return mp[str];
    }


    if(i > j)
        return 0;

    if(i == j)
    {
        if(isTrue == 1)
        {
            mp[str] = (expr[i] == 'T');
            return mp[str];
        }

        else
        {
            mp[str] = (expr[i] == 'F');
            return mp[str];
        }
    }


    int ans = 0;
    for(int k = i+1; k < j; k = k+2)
    {
        int lt, lf, rt, rf;
        std::string leftT, rightT, leftF, rightF;

        leftT = std::to_string(i) + "_" + std::to_string(k-1) + "_" + std::to_string(1);
        leftF = std::to_string(i) + "_" + std::to_string(k-1) + "_" + std::to_string(0);
        rightT = std::to_string(k+1) + "_" + std::to_string(j) + "_" + std::to_string(1);
        rightF = std::to_string(k+1) + "_" + std::to_string(j) + "_" + std::to_string(0);

/*
        lt = ((mp.find(leftT) != mp.end()) ? mp[leftT] : booleanParenthesization2(expr, i, k-1, 1));

        lf = ((mp.find(leftF) != mp.end()) ? mp[leftF] : booleanParenthesization2(expr, i, k-1, 0));

        rt = ((mp.find(rightT) != mp.end()) ? mp[rightT] : booleanParenthesization2(expr, k+1, j, 1));

        rf = ((mp.find(rightF) != mp.end()) ? mp[rightF] : booleanParenthesization2(expr, k+1, j, 0));
*/

        //if(mp.count(leftT) > 0)

        if(mp.find(leftT) != mp.end())                              // checks are made here (stored results are reused here)
        {
            lt = mp[leftT];
            std::cout << leftT << "\n" ;
        }

        else
            lt = booleanParenthesization2(expr, i, k-1, 1);

        if(mp.find(leftF) != mp.end())
        {
            lf = mp[leftF];
            std::cout << leftF << "\n";
        }

        else
            lf = booleanParenthesization2(expr, i, k-1, 0);

        if(mp.find(rightT) != mp.end())
        {
            rt = mp[rightT];
            std::cout << rightT << "\n";
        }

        else
            rt = booleanParenthesization2(expr, k+1, j, 1);

        if(mp.find(rightF) != mp.end())
        {
            rf = mp[rightF];
            std::cout << rightF << "\n";
        }

        else
            rf = booleanParenthesization2(expr, k+1, j, 0);

        // OR

/*
            int lt = solve(S, i, k-1, 1);
            int lf = solve(S, i, k-1, 0);
            int rt = solve(S, k+1, j, 1);
            int rf = solve(S, k+1, j, 0);
*/

        if(expr[k] == '&')
        {
            if(isTrue == 1)
                ans += lt * rt;

            else
                ans += lt * rf + lf * rt + lf * rf;
        }


        else if(expr[k] == '|')
        {
            if(isTrue == 1)
                ans += lt * rt + lt * rf + lf * rt;

            else
                ans += lf * rf;
        }


        else if(expr[k] == '^')
        {
            if(isTrue == 1)
                ans += lt * rf + lf * rt;

            else
                ans += lt * rt + lf * rf;
        }
    }

    mp[str] = ans;
    return mp[str];

}




int booleanParenthesization3(std::vector<char> symbols, std::vector<char> operators, int n)
{
    int total[n+1][n+1];
    int TRUE[n+1][n+1];
    int FALSE[n+1][n+1];

    for(int i=1; i<n+1; i++)
    {
        TRUE[i][i] = (symbols[i-1] == 'T') ? 1 : 0;
        FALSE[i][i] = (symbols[i-1] == 'F') ? 1 : 0;
        total[i][i] = 1;
    }

    for(int l=2; l<=n ; l++)
    {
        for(int i=1; i<=n-l+1; i++)
        {
            int j = i+l-1;

            TRUE[i][j] = 0;
            FALSE[i][j] = 0;

            for(int k=i; k<j; k++)
            {
                total[i][k] = TRUE[i][k] + FALSE[i][k];
                total[k+1][j] = TRUE[k+1][j] + FALSE[k+1][j];

                if(operators[k-1] == '&')
                {
                    TRUE[i][j] += TRUE[i][k] * TRUE[k+1][j];
                    FALSE[i][j] += (total[i][k] * total[k+1][j]) - (TRUE[i][k] * TRUE[k+1][j]);
                }

                else if(operators[k-1] == '|')
                {
                    TRUE[i][j] += (total[i][k] * total[k+1][j]) - FALSE[i][k] * FALSE[k+1][j];
                    FALSE[i][j] += FALSE[i][k] * FALSE[k+1][j];
                }

                else if(operators[k-1] == '^')
                {
                    TRUE[i][j] += (TRUE[i][k] * FALSE[k+1][j]) + (FALSE[i][k] * TRUE[k+1][j]);
                    FALSE[i][j] += (TRUE[i][k] * TRUE[k+1][j]) + (FALSE[i][k] * FALSE[k+1][j]);
                }

                total[i][j] = TRUE[i][j] + FALSE[i][j];

            }

        }
    }

/*
    for(int i=0; i<n+1; i++)
    {
        std::cout << "\n";
        for(int j=0; j<n+1; j++)
            std::cout << TRUE[i][j] << " ";

    }

    std::cout << "\n\nTotal = " << total[1][n] << "  TRUE = " << TRUE[1][n] << "  FALSE = " << FALSE[1][n];
*/
    return TRUE[1][n];


}
