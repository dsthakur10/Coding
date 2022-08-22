
string equilibrium(int *arr, int n) {

    vector<int> prefixSum(n, 0), suffixSum(n, 0);

    prefixSum[0] = arr[0];
    suffixSum[n-1] = arr[n-1];

    for(int i=1; i<n; i++)
        prefixSum[i] = prefixSum[i-1] + arr[i];

    for(int i=n-2; i>=0; i--)
        suffixSum[i] = suffixSum[i+1] + arr[i];


    // for(int i=0; i<n; i++)
    //     cout << prefixSum[i] << " ";

    // cout << "\n";

    // for(int i=0; i<n; i++)
    //     cout << suffixSum[i] << " ";


    for(int i=0; i<n; i++)
    {
        if(prefixSum[i] == suffixSum[i])
            return "YES";
    }

    return "NO";
}
