#include <iostream>
#include <vector>
#include <queue>

/*
    ============
    === HARD ===
    ============

    =============================================
    1857) Largest Color Value in a Directed Graph
    =============================================

    ============
    Description:
    ============

    There is a directed graph of n colored nodes and m edges. The nodes are
    numbered from 0 to n - 1.

    You are given a string colors where colors[i] is a lowercase English letter
    representing the color of the ith node in this graph (0-indexed). You are
    also given a 2D array edges where edges[j] = [aj, bj] indicates that there
    is a directed edge from node aj to node bj.

    A valid path in the graph is a sequence of nodes x1 -> x2 -> x3 -> ... ->
    xk such that there is a directed edge from xi to xi+1 for every 1 <= i < k.
    The color value of the path is the number of nodes that are colored the
    most frequently occurring color along that path.

    Return the largest color value of any valid path in the given graph, or -1
    if the graph contains a cycle.

    ==========================================================================
    FUNCTION: int largestPathValue(string colors, vector<vector<int>>& edges);
    ==========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: colors = "abaca", edges = [[0,1],[0,2],[2,3],[3,4]]
    Output: 3
    Explanation: The path 0 -> 2 -> 3 -> 4 contains 3 nodes that are colored
                 "a" (red in the above image).


    --- Example 2 ---
    Input: colors = "a", edges = [[0,0]]
    Output: -1
    Explanation: There is a cycle from 0 to 0.


    *** Constraints ***
    n == colors.length
    m == edges.length
    1 <= n <= 10^5
    0 <= m <= 10^5
    colors consists of lowercase English letters.
    0 <= aj, bj < n

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 39.13% */
/* Space Beats: 53.35% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution {
public:
    int largestPathValue(string s, vector<vector<int>>& e)
    {
        const int n = s.size();

        vector<int> ad[n];
        vector<int> ind(n,0);

        for (auto i : e)
        {
            ad[i[0]].push_back(i[1]);
            ind[i[1]]++;
        }

        vector<int> col(n);

        for (int i = 0; i < s.size(); i++)
            col[i] = s[i]-'a';

        queue<int> queue;

        int result = 0;
        int mx = 1;

        vector<vector<int>> dp(n, vector<int>(26, 0));
        vector<bool> visited(n, 0);

        for (int i = 0; i < n; i++)
        {
            if (ind[i] == 0)
            {
                visited[i] = true;
                queue.push(i);

                dp[i][col[i]]++;
            }
        }

        while ( ! queue.empty())
        {
            int x = queue.front();

            queue.pop();
            result++;

            for (auto i : ad[x])
            {
                if ( ! visited[i])
                {
                    for (int j = 0; j < 26; j++)
                    {
                        dp[i][j] = max(dp[i][j],dp[x][j] + (j == col[i]));
                        mx = max(mx,dp[i][j]);
                    }
                }

                ind[i]--;

                if (ind[i] == 0)
                    queue.push(i);
            }
        }

        if (result != n)
            return -1;

        return mx;
    }
};
