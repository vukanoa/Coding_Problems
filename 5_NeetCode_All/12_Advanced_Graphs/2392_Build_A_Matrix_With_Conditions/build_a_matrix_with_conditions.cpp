/*
    ============
    === HARD ===
    ============

    ====================================
    2392) Build a Matrix with Conditions
    ====================================

    ============
    Description:
    ============

    You are given a positive integer k. You are also given:

        + a 2D integer array rowConditions of size n where rowConditions[i] =
          [abovei, belowi], and

        + a 2D integer array colConditions of size m where colConditions[i] =
          [lefti, righti].

    The two arrays contain integers from 1 to k.

    You have to build a k x k matrix that contains each of the numbers from 1
    to k exactly once. The remaining cells should have the value 0.

    The matrix should also satisfy the following conditions:

        + The number abovei should appear in a row that is strictly above the
          row at which the number belowi appears for all i from 0 to n - 1.

        + The number lefti should appear in a column that is strictly left of
          the column at which the number righti appears for all i from 0 to m -
          1.

    Return any matrix that satisfies the conditions. If no answer exists,
    return an empty matrix.

    =========================================================================================================================
    FUNCTION: vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions);
    =========================================================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: k = 3, rowConditions = [[1,2],[3,2]], colConditions = [[2,1],[3,2]]
    Output: [[3,0,0],[0,0,1],[0,2,0]]
    Explanation: The diagram above shows a valid example of a matrix that
    satisfies all the conditions.
    The row conditions are the following:

    - Number 1 is in row 1, and number 2 is in row 2, so 1 is above 2 in the
      matrix.

    - Number 3 is in row 0, and number 2 is in row 2, so 3 is above 2 in the
      matrix.

    The column conditions are the following:
    - Number 2 is in column 1, and number 1 is in column 2, so 2 is left of 1
      in the matrix.

    - Number 3 is in column 0, and number 2 is in column 1, so 3 is left of 2
      in the matrix.

    Note that there may be multiple correct answers.



    --- Example 2 ---
    Input: k = 3, rowConditions = [[1,2],[2,3],[3,1],[2,3]],
                  colConditions = [[2,1]]
    Output: []
    Explanation: From the first two conditions, 3 has to be below 1 but the
    third conditions needs 3 to be above 1 to be satisfied.  No matrix can
    satisfy all the conditions, so we return the empty matrix.




    *** Constraints ***
    2 <= k <= 400
    1 <= rowConditions.length, colConditions.length <= 10^4
    rowConditions[i].length == colConditions[i].length == 2
    1 <= abovei, belowi, lefti, righti <= k
    abovei != belowi
    lefti != righti

*/

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 96.75% */
/* Space Beats: 80.85% */

/* Time  Complexity: O(k^2 + N + M) */
/* Space Complexity: O(k^2 + N + M) */
class Solution_postorder_DFS {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions)
    {
        const int N = rowConditions.size();
        const int M = colConditions.size();

        // O(k^2)
        vector<vector<int>> result(k, vector<int>(k, 0));

        // O(k + N) + O(k + M) ---> O(k + (N + M)) ---> O(k + E)
        vector<int> row_topo_order = topological_order(rowConditions, k);
        vector<int> col_topo_order = topological_order(colConditions, k);

        /* Check if there are cycles in either of the given conditions */
        if (row_topo_order.empty()) return {};
        if (col_topo_order.empty()) return {};

        /* Convert orders to HashMaps */
        unordered_map<int,int> row_val__to__idx;
        unordered_map<int,int> col_val__to__idx;

        // Row
        // O(k) (entire block)
        for (int idx = 0; idx < k; idx++)
            row_val__to__idx[row_topo_order[idx]] = idx;

        // Col
        // O(k) (entire block)
        for (int idx = 0; idx < k; idx++)
            col_val__to__idx[col_topo_order[idx]] = idx;

        /* Populate the result */
        // O(k) (entire block)
        for (int val = 1; val < k+1; val++)
        {
            int row = row_val__to__idx[val];
            int col = col_val__to__idx[val];

            result[row][col] = val;
        }

        return result;
    }

private:
    // O(k + E) (entire block)
    vector<int> topological_order(vector<vector<int>> edges, int k)
    {
        vector<int> order;

        /* Create an Adjacency List */
        // O(E) (entire block)
        vector<vector<int>> adj_list(k+1);
        for (const auto& edge : edges)
        {
            const int& src = edge[0];
            const int& dst = edge[1];

            adj_list[src].push_back(dst);
        }
        
        // O(k)
        vector<bool> visited(k+1, false);
        vector<bool> path   (k+1, false);

        // O(k + E) (entire block)
        for (int node = 1; node < k+1; node++)
        {
            if (visited[node])
                continue;

            if ( ! postorder_DFS(node, visited, path, order, adj_list))
                return {}; // We have found a CYCLE
        }

        /* Reverse */
        // O(k)
        reverse(order.begin(), order.end());

        return order;
    }

    // O(k + E) (entire block)
    bool postorder_DFS(int node, vector<bool>& visited, vector<bool>& path, vector<int>& order, vector<vector<int>>& adj_list)
    {
        if (path[node])
            return false; // We've found a CYCLE

        if (visited[node])
            return true; // We have already processed from here onwards

        path[node] = true;
        for (const auto& neighbor : adj_list[node])
        {
            if ( ! postorder_DFS(neighbor, visited, path, order, adj_list))
                return false;
        }
        path[node] = false;

        // Mark as successfully processed
        visited[node] = true;
        order.push_back(node);

        return true;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 59.57% */
/* Space Beats: 96.86% */

/* Time  Complexity: O(k^2 + N + M) */
/* Space Complexity: O(k^2 + N + M) */
class Solution_Kahn_Algorithm__BFS {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions)
    {
        const int N = rowConditions.size();
        const int M = colConditions.size();

        // O(k^2)
        vector<vector<int>> result(k, vector<int>(k, 0));

        // O(k + N) + O(k + M) ---> O(k + (N + M)) ---> O(k + E)
        vector<int> row_topo_order = topological_order(rowConditions, k);
        vector<int> col_topo_order = topological_order(colConditions, k);

        /* Check if there are cycles in either of the given conditions */
        if (row_topo_order.size() != k) return {};
        if (col_topo_order.size() != k) return {};

        /* Convert orders to HashMaps */
        unordered_map<int,int> row_val__to__idx;
        unordered_map<int,int> col_val__to__idx;

        // Row
        // O(k) (entire block)
        for (int idx = 0; idx < k; idx++)
            row_val__to__idx[row_topo_order[idx]] = idx;

        // Col
        // O(k) (entire block)
        for (int idx = 0; idx < k; idx++)
            col_val__to__idx[col_topo_order[idx]] = idx;

        /* Populate the result */
        // O(k) (entire block)
        for (int val = 1; val < k+1; val++)
        {
            int row = row_val__to__idx[val];
            int col = col_val__to__idx[val];

            result[row][col] = val;
        }

        return result;
    }

private:
    // O(k + E) (entire block)
    vector<int> topological_order(vector<vector<int>> edges, int k)
    {
        vector<vector<int>> adj_list(k+1);
        vector<int> indegree(k+1, 0);

        /* Create an Adjacency List */
        // O(E) (entire block)
        for (const auto& edge : edges)
        {
            const int& src = edge[0];
            const int& dst = edge[1];

            adj_list[src].push_back(dst);
            indegree[dst]++;
        }

        // O(k) (entire block)
        queue<int> queue;
        for (int vertex = 1; vertex < k+1; vertex++)
        {
            if (indegree[vertex] == 0)
                queue.push(vertex);
        }

        vector<int> order;

        /* Topological Sort(Kahn's Algorithm) */
        // O(k + E)
        while ( ! queue.empty())
        {
            int node = queue.front();
            queue.pop();

            order.push_back(node);

            for (const int& neighbor : adj_list[node])
            {
                indegree[neighbor]--;

                if (indegree[neighbor] == 0)
                    queue.push(neighbor);
            }
        }

        // If there was a cycle, then the "order" would NOT end up having all
        // the N nodes in it. Therefore, if that's the case---We've found a
        // cycle.
        return order;
    }
};
