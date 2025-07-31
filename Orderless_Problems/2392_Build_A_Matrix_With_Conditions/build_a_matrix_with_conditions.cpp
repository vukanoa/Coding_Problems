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
#include <vector>
using namespace std;



/* Time  Beats: 96.75% */
/* Space Beats: 80.85% */

/* Time  Complexity: O(max(k^2, N)) */
/* Space Complexity: O(max(k^2, N)) */
class Solution_DFS {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions)
    {
        vector<int> order_rows = topological_sort(rowConditions, k);
        vector<int> order_cols = topological_sort(colConditions, k);

        if (order_rows.empty() || order_cols.empty())
            return {};

        vector<vector<int>> matrix(k, vector<int>(k, 0));
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (order_rows[i] == order_cols[j])
                    matrix[i][j] = order_rows[i];
            }
        }

        return matrix;
    }

private:
    vector<int> topological_sort(vector<vector<int>>& edges, const int& k)
    {
        vector<vector<int>> adj_list(k + 1);
        vector<int> order;

        // Legend:
        // 0: not visited
        // 1: visiting
        // 2: visited
        vector<int> visited(k + 1, 0);
        bool has_cycle = false;

        // Build an adjacency list
        for (const auto& e : edges)
            adj_list[e[0]].push_back(e[1]);

        for (int i = 1; i <= k; i++)
        {
            if (visited[i] == 0)
            {
                dfs(i, adj_list, visited, order, has_cycle);

                if (has_cycle)
                    return {};
            }
        }

        // Reverse to get the correct order
        reverse(order.begin(), order.end());

        return order;
    }

    void dfs(int node, vector<vector<int>>& adj_list, vector<int>& visited, vector<int>& order, bool& has_cycle)
    {
        visited[node] = 1; // Visiting

        for (int neighbor : adj_list[node])
        {
            if (visited[neighbor] == 0)
            {
                dfs(neighbor, adj_list, visited, order, has_cycle);

                if (has_cycle)
                    return;
            }
            else if (visited[neighbor] == 1)
            {
                has_cycle = true;
                return;
            }
        }

        visited[node] = 2; // Visited
        order.push_back(node);
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

/* Time  Complexity: O(max(k^2, N)) */
/* Space Complexity: O(max(k^2, N)) */
class Solution {
public:
    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions)
    {
        vector<int> order_rows = topological_sort(rowConditions, k);
        vector<int> order_cols = topological_sort(colConditions, k);

        if (order_rows.empty() || order_cols.empty())
            return {};

        vector<vector<int>> matrix(k, vector<int>(k, 0));
        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                if (order_rows[i] == order_cols[j])
                    matrix[i][j] = order_rows[i];
            }
        }

        return matrix;
    }

private:
    // Find topological sequence using Kahn's algorithm
    vector<int> topological_sort(vector<vector<int>>& edges, int k)
    {
        vector<vector<int>> adj_list(k + 1);
        vector<int> degree(k + 1);
        vector<int> order;

        for (const auto& e : edges)
        {
            adj_list[e[0]].push_back(e[1]);
            degree[e[1]]++;
        }

        queue<int> queue;

        // Push all integers with in-degree 0 in the queue.
        for (int i = 1; i <= k; i++)
        {
            if (degree[i] == 0)
                queue.push(i);
        }

        while ( ! queue.empty())
        {
            int front = queue.front();
            queue.pop();

            order.push_back(front);
            k--;

            for (const auto& neighbor : adj_list[front])
            {
                if (--degree[neighbor] == 0)
                    queue.push(neighbor);
            }
        }

        // If we have NOT visited all integers, return empty array.
        if (k != 0)
            return {};

        return order;
    }
};
