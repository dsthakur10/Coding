// Accounts Merge

/*

Given a list of accounts where each element accounts[i] is a list of strings, where the first element accounts[i][0]
is a name, and the rest of the elements are emails representing emails of the account.

Now, we would like to merge these accounts. Two accounts definitely belong to the same person if there is
some common email to both accounts. Note that even if two accounts have the same name, they may belong to
different people as people could have the same name. A person can have any number of accounts initially,
but all of their accounts definitely have the same name.

After merging the accounts, return the accounts in the following format:
the first element of each account is the name, and the rest of the elements are emails in sorted order.
The accounts themselves can be returned in any order.


Example 1:
Input: accounts =
[["John","johnsmith@mail.com","john_newyork@mail.com"],
["John","johnsmith@mail.com","john00@mail.com"],
["Mary","mary@mail.com"],
["John","johnnybravo@mail.com"]]

Output: [["John","john00@mail.com","john_newyork@mail.com","johnsmith@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]

Explanation:
The first and second John's are the same person as they have the common email "johnsmith@mail.com".
The third John and Mary are different people as none of their email addresses are used by other accounts.
We could return these lists in any order, for example the answer [['Mary', 'mary@mail.com'], ['John', 'johnnybravo@mail.com'],
['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']] would still be accepted.

Example 2:
Input: accounts =
[["Gabe","Gabe0@m.co","Gabe3@m.co","Gabe1@m.co"],
["Kevin","Kevin3@m.co","Kevin5@m.co","Kevin0@m.co"],
["Ethan","Ethan5@m.co","Ethan4@m.co","Ethan0@m.co"],
["Hanzo","Hanzo3@m.co","Hanzo1@m.co","Hanzo0@m.co"],
["Fern","Fern5@m.co","Fern1@m.co","Fern0@m.co"]]

Output: [["Ethan","Ethan0@m.co","Ethan4@m.co","Ethan5@m.co"],["Gabe","Gabe0@m.co","Gabe1@m.co","Gabe3@m.co"],["Hanzo","Hanzo0@m.co","Hanzo1@m.co","Hanzo3@m.co"],["Kevin","Kevin0@m.co","Kevin3@m.co","Kevin5@m.co"],["Fern","Fern0@m.co","Fern1@m.co","Fern5@m.co"]]

*/




// Method-1 --> DFS

/*

Here, we will represent EMAILS as "nodes", and an edge will signify that two emails are connected and hence belong
to same person. This means that any two emails that are connected by a path of edges must also belong to the same
person. Initially, we are given N accounts, where each account's emails make up a connected component.

Our first step should be to ensure that for each account, all of its nodes are connected. Suppose an account has
K emails, and we want to connect these emails. Since all emails in an account are connected,
we can add an edge between every pair of emails. This will create a complete subgraph and require adding KC2 edges.

However, do we really need that many edges to keep track of which emails belong to the same account?
--> NO | As long as two emails are connected by a path of edges, we know they belong to the same account.
So instead of creating a complete subgraph for each account, we can create an acyclic graph using only K-1 edges.
Recall that K-1 is the minimum number of edges required to connect K nodes.
In this approach, we will connect emails in an account in STAR TOPOLOGY with the first email as the internal node
of the star and all other emails as the leaves.

WHY STAR TOPOLOGY ?
The beauty of connecting the emails in each account in this manner is that after connecting an email to a
second account, that email will have one edge going to an email in the first account and one edge going to an email
in the second account. Thereby automatically merging the two accounts.

After iterating over each account and connecting the emails as described above, we will have a one or more
connected components. Each connected component will represent one person, and the nodes in the connected component
are the person's emails. Now our task is to explore each connected component to find all the emails that belong to
each person. Since a depth-first search is guaranteed to explore every node in a connected component,
we will perform a DFS on each connected component (person) to find all of the connected emails.

*/

unordered_map<string, vector<string>> adj;
unordered_set<string> visited;

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts)
{
    // accounts[i][0] --> user name
    // accounts[i][1] --> 1st email of given user[i][0]

    // Building adjacency list using "unordered_map" since we do not have numbers here to represent nodes
    // Adding edge between first email to all other emails in the account --> STAR TOPOLOGY

    buildGraph(accounts);

    vector<vector<string>> mergedAccounts;          // contains result

    // Traverse over all the accounts to store components.
    for(int i=0; i<accounts.size(); i++)
    {
        string name = accounts[i][0];
        string firstEmail = accounts[i][1];

        // If email is already visited, then it's a part of different component.
        // (someone's first-email might be in STAR topology of some other account's first-email)
        // Hence perform DFS only if email is not visited yet.

        if(visited.find(firstEmail) == visited.end())
        {
            // Pushing required information as asked in problem.
            vector<string> newAccount;
            newAccount.push_back(name);
            DFS(newAccount, firstEmail);

            sort(newAccount.begin()+1, newAccount.end());       // sorting Email-Ids excluding name
            mergedAccounts.push_back(newAccount);         // pushing merged account in final list
        }
    }

    return mergedAccounts;
}



// DFS() will add emails in given mergedAccount as it traverses neighbors started from some first-Email

void DFS(vector<string>& mergedAccount, string email)
{
    visited.insert(email);
    mergedAccount.push_back(email);

    for(string neighbor : adj[email])
    {
        if(visited.find(neighbor) == visited.end())
            DFS(mergedAccount, neighbor);
    }
}


void buildGraph(vector<vector<string>>& accounts)
{
    int n = accounts.size();

    for(int i=0; i<n; i++)
    {
        string firstEmail = accounts[i][1];
        for(int j=2; j<accounts[i].size(); j++)
        {
            adj[firstEmail].push_back(accounts[i][j]);
            adj[accounts[i][j]].push_back(firstEmail);
        }
    }
}



// Method-2 --> Disjoint set

/*
Since most implementations of DSU use an array to record the root (representative) of each component,
we will use integers to represent each component for ease of operability. Therefore, we will give each account
a unique ID, and we will map all the emails in the account to the account's ID.

We chose the account index to be the identifier for all the emails of an account. We will assign the account index
as the group when we get the email for the first time and when we get an email that we have already traversed,
we will merge the current account and group that we have previously stored in emailGroup using union operation.

After traversing over all the accounts, we will find the representative of all the emails which will inform us
about their group. Emails with the same representative belong to the same person/group and hence will be stored
together. Also, we can retrieve the account name for our final answer using accountList as we have
GROUP WHICH IS THE INDEX IN THE ORIGINAL ACCOUNTS LIST

*/




vector<vector<string>> accountsMerge(vector<vector<string>>& accountList)
{
    int accountListSize = accountList.size();
    DSU dsu(accountListSize);

    // Maps email to their component index
    unordered_map<string, int> emailGroup;

    for (int i = 0; i < accountListSize; i++)
    {
        int accountSize = accountList[i].size();

        for (int j = 1; j < accountSize; j++)
        {
            string email = accountList[i][j];
            string accountName = accountList[i][0];

            // If this is the first time seeing this email then assign component group as the account index
            if (emailGroup.find(email) == emailGroup.end())
            {
                emailGroup[email] = i;
            }

            // If we have seen this email before then union this group with the previous group of the email
            else
            {
                dsu.unionBySize(i, emailGroup[email]);
            }
        }
    }

    // Store emails corresponding to the component's representative (root)

    unordered_map<int, vector<string>> components;
    for (auto emailIterator : emailGroup)
    {
        string email = emailIterator.first;         // email
        int group = emailIterator.second;           // ID for each email

        components[dsu.findRepresentative(group)].push_back(email);     // unique root of ID of each component
    }


    // Sort the components and add the account name

    vector<vector<string>> mergedAccounts;
    for (auto componentIterator : components)
    {
        int group = componentIterator.first;            // unique root of ID of each component

        vector<string> component = {accountList[group][0]};         // group ID was nothing but 'i' in traversing users

        component.insert(component.end(), componentIterator.second.begin(), componentIterator.second.end());
        sort(component.begin() + 1, component.end());
        mergedAccounts.push_back(component);
    }

    return mergedAccounts;
}
