
// Print N-bit binary numbers having #1's >= #0's

/*

Given a positive integer N, the task is to find all the N bit binary numbers having #1's >= #0's for any prefix of the number.

Example 1:
Input:  N = 2
Output: 11 10

Example 2:
Input:  N = 3
Output: 111 110 101

*/


bool checkOnesGzeros(string str)
{
    int ones = 0, zeros = 0;

    for(int i=0; i<str.size(); i++)
    {
        if(str[i] == '1')
            ones++;
        else
            zeros++;
    }

    return ones>zeros;
}


void onesGEzeros(string output, int N, vector<string>& result)
{
    if(N == output.size())
    {
        result.push_back(output);
        return;
    }

    onesGEzeros(output+'1', N, result);

    if(checkOnesGzeros(output))
        onesGEzeros(output+'0', N, result);
}


vector<string> NBitBinary(int N)
{
    vector<string> result;
    string output = "1";

    onesGEzeros(output, N, result);

    return result;
}


// Method-2 --> Optimizing 1st solution by using an extra variable "diff" {#1's - #0's}. No need to calculate

void onesGEzeros(string output, int diff, int N, vector<string>& result)
{
    if(N == output.size())
    {
        result.push_back(output);
        return;
    }

    onesGEzeros(output+'1', diff+1, N, result);

    if(diff > 0)
        onesGEzeros(output+'0', diff-1, N, result);
}


vector<string> NBitBinary(int N)
{
    vector<string> result;
    string output = "1";

    onesGEzeros(output, 1, N, result);

    return result;
}


// Method-3 --> Using 2 variables(ones & zeros) instead of diff

void onesGEzeros(string output, int ones, int zeros, int N, vector<string>& result)
{
    if(N == 0)
    {
        result.push_back(output);
        return;
    }

    onesGEzeros(output+'1', ones+1, zeros, N-1, result);

    if(ones > zeros)
        onesGEzeros(output+'0', ones, zeros+1, N-1, result);
}


vector<string> NBitBinary(int N)
{
    vector<string> result;
    string output = "1";

    onesGEzeros(output, 1, 0, N-1, result);

    return result;
}
