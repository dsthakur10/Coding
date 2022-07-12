
/*

Given a set of N jobs where each jobi has a deadline and profit associated with it.

Each job takes 1 unit of time to complete and only one job can be scheduled at a time.
We earn the profit associated with job if and only if the job is completed by its deadline.

Find the number of jobs done and the maximum profit.

NOTE: Jobs will be given in the form (Jobid, Deadline, Profit) associated with that Job.

*/


// Method-1 --> Greedy method

struct Job
{
    int id;	 // Job Id
    int dead; // Deadline of job
    int profit; // Profit if job is over before or on deadline
};


static bool customCompare(const Job &x, const Job &y)
{
    return (x.profit > y.profit);
}


//Function to find the maximum profit and the number of jobs done.
vector<int> JobScheduling(Job arr[], int n)
{
    // sort according to max Profit
    sort(arr, arr+n, customCompare);
    vector<int> store(100, 0);

    int maxProfit = 0, numberOfJobs = 0;
    for(int i=0; i<n; i++)
    {
        int pos = arr[i].dead - 1;
        while(pos >= 0 && store[pos] != 0)
            pos--;

        if(pos >= 0)
        {
            store[pos] = arr[i].id;
            maxProfit += arr[i].profit;
            numberOfJobs++;
        }
    }

    return {numberOfJobs, maxProfit};
}



// Method-2 --> DP

