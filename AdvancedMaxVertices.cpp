// This code simulates the algorithm for deterministically finding a hyperedge using r rounds in the
// Advanced Max Vertices Query Model.

#include <iostream>
#include <vector>

using namespace std;

int Rounds;
int Hyperedge_size;

void populate2rounds(vector<vector<double> >& dp, int k)
{
    // since query complexity will be atmost O(n^k)
    double minimum = k;
    for(int i=1;i<k;i++)
    {
        double term1 = static_cast<double>((Hyperedge_size*i))/static_cast<double>(Hyperedge_size+i);
        double term2 = k - i;
        minimum = min(minimum, max(term1,term2));
    }
    dp[2][k] = minimum;
}

void populateRrounds(vector<vector<double> >& dp, int r, int k)
{
    // since query complexity will be atmost O(n^k)
    double minimum = k;
    for (int i=1; i < k; i++)
    {
        double x = i;
        double term1 = dp[r-1][Hyperedge_size]*x / (dp[r-1][Hyperedge_size] + x);
        double term2 = dp[r-1][k-i];
        minimum = min(minimum, max(term1,term2));
    }
    dp[r][k] = minimum;
}

int main()
{
    cout << "Enter the adaptivity (number of rounds of querying) of the algorithm" << endl;
    cin >> Rounds;
    cout << "Enter the size of the hyperedges in the graph" << endl;
    cin >> Hyperedge_size;
    vector<vector<double> > dp(Rounds+1, vector<double> (Hyperedge_size+1));

    for (int i=0; i<=Rounds; i++)
    {
        for (int j=0; j<=Hyperedge_size; j++)
        {
            dp[i][j] = INT_MAX;
        }
    }

    // Initialising the Query complexity of single round hyperedge finding
    for (int j=1; j<=Hyperedge_size; j++)
    {
        dp[1][j] = j;
    }

    dp[2][1] = 1;

    // Calculating the Query complexity for a general r' <= r and k' <= k from here onwards
    for (int j=2; j<=Hyperedge_size; j++)
    {
        populate2rounds(dp, j);
    }

    for (int i=3; i<=Rounds; i++)
    {
        // Initialising the Query complexity of finding the final vertex in r rounds
        dp[i][1] = min(static_cast<double>(1), dp[i-1][Hyperedge_size]);

        for (int j=2; j<=Hyperedge_size; j++)
        {
            populateRrounds(dp,i,j);
        }
    }
    double IndependentSetQueryComplexity = static_cast<double>(Hyperedge_size) / static_cast<double>(Rounds);
    cout << "The query complexity of the Independent Set algorithm is O(n^x), x = " << IndependentSetQueryComplexity << endl;
    cout << "The query complexity of this algorithm is O(n^x), x = ";
    cout << min(dp[Rounds][Hyperedge_size], IndependentSetQueryComplexity) << endl;
}