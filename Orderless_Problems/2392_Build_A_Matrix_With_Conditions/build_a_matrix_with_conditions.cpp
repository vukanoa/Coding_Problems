#include <iostream>
#include <vector>
#include <queue>

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

    ========================================================================
    FUNCTION: vector<int> topo_sort(int k, vector<vector<int>>& conditions);  
    ========================================================================

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

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 93.52% */
/* Space Beats: 77.18% */

/* Time  Complexity: O(k^2 + rowConditions + colConditions) */
/* Space Complexity: O(k) */
class Solution {
public:
    // Topological sort using BFS (Kahn's algorithm)
    vector<int> topo_sort(int k, vector<vector<int>>& conditions)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        vector<int> degree(k+1, 0);
        vector<vector<int>> adj_list(k+1);

        for (auto& edge: conditions)
        {
            int v = edge[0];
            int w = edge[1];

            adj_list[v].push_back(w);
            degree[w]++;
        }

        queue<int> queue;
        for (int i = 1; i <= k; i++)
        {
            if (degree[i] == 0) 
                queue.push(i);
        }

        int count = 0;
        vector<int> result;
        result.reserve(k);

        while( ! queue.empty())
        {
            int j = queue.front();
            queue.pop();

            result.push_back(j);
            count++;

            for(int k : adj_list[j])
            {
                degree[k]--;
                if (degree[k] == 0)
                    queue.push(k);
            }
        }

        if (count != k)
            return {}; // Has cycle
        else
            return result;
    }

    vector<vector<int>> buildMatrix(int k, vector<vector<int>>& rowConditions, vector<vector<int>>& colConditions)
    {
        auto order_row = topo_sort(k, rowConditions);
        auto order_col = topo_sort(k, colConditions);

        if (order_row.empty()|| order_col.empty())
            return {}; // Some conflict

        vector<vector<int>> arr(k, vector<int>(k));

        // Find pos for x where 1 <= x <= k
        vector<int> pos_i(k+1, -1), pos_j(k+1, -1);

        for (int i = 0; i < k; i++)
        {
            pos_i[order_row[i]] = i;
            pos_j[order_col[i]] = i;
        }

        for (int x = 1; x <= k; x++)
            arr[pos_i[x]][pos_j[x]] = x;

        return arr;
    }
};
