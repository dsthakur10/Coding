
// Method-1 --> 2 loops

string getSmallestString(int n, int k) {

    string result;
    vector<int> store(n, 1);

    int sum, mod, count;

    sum = k - n;
    int index = n-1;

    while(sum > 0)
    {
        if(sum >= 25)
        {
            store[index] += 25;
            sum -= 25;
            index--;
        }

        else
        {
            store[index] += sum;
            sum = 0;
            index--;
        }
    }

    for(int i=0; i<n; i++)
    {
        char ch = 'a' + store[i] - 1;
        result.push_back(ch);
    }

    return result;
}



// Method-2 --> 1 loop

string getSmallestString2(int n, int k) {

    string result(n, 'a');
    vector<int> store(n, 1);

    int sum;

    sum = k - n;
    int index = n-1;

    while(sum > 0)
    {
        if(sum >= 25)
        {
            store[index] += 25;
            sum -= 25;
        }

        else
        {
            store[index] += sum;
            sum = 0;
        }

        result[index] = 'a' + store[index] - 1;
        index--;
    }

    return result;
}


// Method-3 --> 1 vector removed

string getSmallestString3(int n, int k) {

    string result(n, 'a');
    int sum;

    sum = k - n;
    int index = n-1;

    while(sum > 0)
    {
        if(sum >= 25)
        {
            result[index] = 'z';
            sum -= 25;
        }

        else
        {
            result[index] = 'a' + sum ;         // 1 is already deducted before while doing sum = k-n
            sum = 0;
        }

        index--;
    }

    return result;
}
