/*
    ============
    === HARD ===
    ============

    ==============================================
    2872) Maximum Number of K-Divisible Components
    ==============================================

    ============
    Description:
    ============

    There is an undirected tree with n nodes labeled from 0 to n - 1. You are
    given the integer n and a 2D integer array edges of length n - 1, where
    edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi
    in the tree.

    You are also given a 0-indexed integer array values of length n, where
    values[i] is the value associated with the ith node, and an integer k.

    A valid split of the tree is obtained by removing any set of edges,
    possibly empty, from the tree such that the resulting components all have
    values that are divisible by k, where the value of a connected component is
    the sum of the values of its nodes.

    Return the maximum number of components in any valid split.

    =====================================================================================================
    FUNCTION: int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k);
    =====================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 5, edges = [[0,2],[1,2],[1,3],[2,4]], values = [1,8,1,4,4], k = 6
    Output: 2
    Explanation: We remove the edge connecting node 1 with 2. The resulting split is valid because:
    - The value of the component containing nodes 1 and 3 is values[1] + values[3] = 12.
    - The value of the component containing nodes 0, 2, and 4 is values[0] + values[2] + values[4] = 6.
    It can be shown that no other valid split has more than 2 connected components.

    --- Example 2 ---
    Input: n = 7, edges = [[0,1],[0,2],[1,3],[1,4],[2,5],[2,6]], values = [3,0,6,1,5,2,1], k = 3
    Output: 3
    Explanation: We remove the edge connecting node 0 with 2, and the edge connecting node 0 with 1. The resulting split is valid because:
    - The value of the component containing node 0 is values[0] = 3.
    - The value of the component containing nodes 2, 5, and 6 is values[2] + values[5] + values[6] = 9.
    - The value of the component containing nodes 1, 3, and 4 is values[1] + values[3] + values[4] = 6.
    It can be shown that no other valid split has more than 3 connected components.


    *** Constraints ***
    1 <= n <= 3 * 10^4
    edges.length == n - 1
    edges[i].length == 2
    0 <= ai, bi < n
    values.length == n
    0 <= values[i] <= 10^9
    1 <= k <= 10^9
    Sum of values is divisible by k.
    The input is generated such that edges represents a valid tree.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 36.71% */
/* Space Beats: 43.04% */

/* Time  Complexity: O(n + m) */
/* Space Complexity: O(n + m) */
class Solution_DFS {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>> &edges, vector<int> &values, int k)
    {
        vector<int> adj_list[n];

        for (auto edge : edges)
        {
            adj_list[edge[0]].push_back(edge[1]);
            adj_list[edge[1]].push_back(edge[0]);
        }

        int component_count = 0;

        dfs(adj_list, values, k, component_count, 0, -1);

        return component_count;
    }

private:
    int dfs(vector<int> adj_list[], vector<int> &values, int k, int &component_count, int curr_node, int parent_node)
    {
        int sum = 0;

        for (auto neighbor_node : adj_list[curr_node])
        {
            if (neighbor_node != parent_node)
            {
                sum += dfs(adj_list, values, k, component_count, neighbor_node, curr_node);
                sum %= k;
            }
        }

        sum += values[curr_node];

        sum %= k;
        if (sum == 0)
            component_count++;

        return sum;
    }
};




#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 10.76% */
/* Space Beats:  7.60% */

/* Time  Complexity: O(n + m) */
/* Space Complexity: O(n + m) */
class Solution_BFS {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k)
    {
        if (n < 2)
            return 1;

        int component_count = 0;
        unordered_map<int, unordered_set<int>> graph;

        for (const auto& edge : edges)
        {
            graph[edge[0]].insert(edge[1]);
            graph[edge[1]].insert(edge[0]);
        }

        vector<long long> long_values(values.begin(), values.end());

        queue<int> queue;
        for (const auto& [node, neighbors] : graph)
        {
            if (neighbors.size() == 1)
                queue.push(node);
        }

        while ( ! queue.empty())
        {
            int curr_node = queue.front();
            queue.pop();

            int neighbor_node = -1;
            if ( ! graph[curr_node].empty())
                neighbor_node = *graph[curr_node].begin();

            if (neighbor_node >= 0)
            {
                graph[neighbor_node].erase(curr_node);
                graph[curr_node].erase(neighbor_node);
            }

            if (long_values[curr_node] % k == 0)
            {
                component_count++;
            }
            else if (neighbor_node >= 0)
            {
                long_values[neighbor_node] += long_values[curr_node];
            }

            if (neighbor_node >= 0 && graph[neighbor_node].size() == 1)
                queue.push(neighbor_node);
        }

        return component_count;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 75.95% */
/* Space Beats: 67.09% */

/* Time  Complexity: O(n + m) */
/* Space Complexity: O(n + m) */
class Solution_Topological_or_Onion_Sort {
public:
    int maxKDivisibleComponents(int n, vector<vector<int>>& edges, vector<int>& values, int k)
    {
        if (n < 2)
            return 1;

        int component_count = 0;
        vector<vector<int>> adj_list(n);
        vector<int> in_degree(n, 0);

        // Build the graph and calculate in-degrees
        for (const auto& edge : edges)
        {
            adj_list[edge[0]].push_back(edge[1]);
            adj_list[edge[1]].push_back(edge[0]);

            in_degree[edge[0]]++;
            in_degree[edge[1]]++;
        }

        // Convert values to long long to prevent overflow
        vector<long long> long_values(values.begin(), values.end());

        // Initialize the queue with nodes having in-degree of 1 (leaf nodes)
        queue<int> queue;
        for (int node = 0; node < n; node++)
        {
            if (in_degree[node] == 1)
                queue.push(node);
        }

        while ( ! queue.empty())
        {
            int curr_node = queue.front();
            queue.pop();
            in_degree[curr_node]--;

            long long add_value = 0;

            if (long_values[curr_node] % k == 0)
                component_count++;
            else
                add_value = long_values[curr_node];

            // Propagate the value to the neighbor nodes
            for (int neighborNode : adj_list[curr_node])
            {
                if (in_degree[neighborNode] == 0)
                    continue;

                in_degree[neighborNode]--;
                long_values[neighborNode] += add_value;

                // If the neighbor node's in-degree becomes 1, add it to queue
                if (in_degree[neighborNode] == 1)
                    queue.push(neighborNode);
            }
        }

        return component_count;
    }
};
