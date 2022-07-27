// Find the City With the Smallest Number of Neighbors at a Threshold Distance

/*

There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.

Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.

Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.



Example 1:
Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
Output: 3
Explanation:
The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2]
City 1 -> [City 0, City 2, City 3]
City 2 -> [City 0, City 1, City 3]
City 3 -> [City 1, City 2]
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has
the greatest number.

Example 2:
Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
Output: 0
Explanation:
The neighboring cities at a distanceThreshold = 2 for each city are:
City 0 -> [City 1]
City 1 -> [City 0, City 4]
City 2 -> [City 3, City 4]
City 3 -> [City 2, City 4]
City 4 -> [City 1, City 2, City 3]
The city 0 has 1 neighboring city at a distanceThreshold = 2.

*/



typedef pair<int, int> pi;

vector<vector<int>> buildGraph(vector<vector<int>>& edges, int n)
{
    vector<vector<int>> matrix(n, vector<int>(n, INT_MAX));

    for(int i=0; i<n; i++)
        matrix[i][i] = 0;

    for(int i=0; i<edges.size(); i++)
    {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];

        matrix[u][v] = w;
        matrix[v][u] = w;
    }

    return matrix;
}


int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold){

    vector<vector<int>> matrix = buildGraph(edges, n);
    //vector<vector<int>> temp;

    for(int k=0; k<n; k++)
    {
        //temp = matrix;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX)
                    matrix[i][j] = min(matrix[i][j],
                                      matrix[i][k] + matrix[k][j]);
            }
        }
    }

    vector<int> countCities(n, 0);
    int minCount = INT_MAX;
    int minIndex;

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(matrix[i][j] <= distanceThreshold)
                countCities[i]++;
        }

        if(countCities[i] <= minCount)
        {
            minCount = countCities[i];
            minIndex = i;
        }
    }

    return minIndex;
}


// Carry out calculations in the same loop
// No need for extra O(N) space for countCities[] to keep count of cities reachable within threshold distance.

int findTheCity(int n, vector<vector<int>>& edges, int distanceThreshold){

    vector<vector<int>> matrix = buildGraph(edges, n);
    vector<int> countCities(n, 0);
    int minCount = INT_MAX;
    int minIndex;

    for(int k=0; k<n; k++)
    {
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(matrix[i][k] != INT_MAX && matrix[k][j] != INT_MAX)
                    matrix[i][j] = min(matrix[i][j],
                                      matrix[i][k] + matrix[k][j]);
            }

          /*

            // check threshold in the last round
            if(k == n-1)
            {
                for(int j=0; j<n; j++)
                {
                    if(matrix[i][j] <= distanceThreshold)
                        countCities[i]++;
                }

                if(countCities[i] <= minCount)
                {
                    minCount = countCities[i];
                    minIndex = i;
                }
            }
        */
            if(k == n-1)
            {
                count = 0;
                for(int j=0; j<n; j++)
                {
                    if(matrix[i][j] <= distanceThreshold)
                        count++;
                }

                if(count <= minCount)
                {
                    minCount = count;
                    minIndex = i;
                }
            }
        }
    }

    return minIndex;
}
