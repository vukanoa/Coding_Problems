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

#include <string>
#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 80.90% */
/* Space Beats: 86.66% */

/* Time  Complexity: O(V + E) */
/* Space Complexity: O(V + E) */
class Solution {
public:
    int largestPathValue(string colors, vector<vector<int>>& edges)
    {
        const int N = colors.size();

        vector<int> adj_list[N];
        vector<int> indegree(N, 0);

        for (const auto& entry : edges)
        {
            adj_list[entry[0]].push_back(entry[1]);
            indegree[entry[1]]++;
        }

        vector<int> color_of_vertex(N);

        for (int vertex = 0; vertex < N; vertex++)
            color_of_vertex[vertex] = colors[vertex] - 'a';

        queue<int> queue;

        int visited_count  = 0;
        int max_color_freq = 1;

        vector<vector<int>> dp(N, vector<int>(26, 0)); // ROW=vertex, COL=color
        vector<bool> visited(N, false);

        for (int vertex = 0; vertex < N; vertex++)
        {
            if (indegree[vertex] == 0)
            {
                visited[vertex] = true;
                queue.push(vertex);

                dp[vertex][color_of_vertex[vertex]]++;
            }
        }

        /* BFS */
        while ( ! queue.empty())
        {
            int curr_vertex = queue.front();
            queue.pop();

            visited_count++;

            for (const auto& neighbor : adj_list[curr_vertex])
            {
                if ( ! visited[neighbor])
                {
                    for (int color = 0; color < 26; color++)
                    {
                        dp[neighbor][color] = max(dp[neighbor][color], dp[curr_vertex][color] + (color == color_of_vertex[neighbor]));
                        max_color_freq = max(max_color_freq, dp[neighbor][color]);
                    }
                }

                indegree[neighbor]--;

                if (indegree[neighbor] == 0)
                    queue.push(neighbor);
            }
        }

        if (visited_count != N)
            return -1;

        return max_color_freq;
    }
};
