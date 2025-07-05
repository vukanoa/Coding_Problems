/*
    ==============
    === MEDIUM ===
    ==============

    ======================================================
    3603) Minimum Cost Path with Alternating Directions II
    ======================================================

    ============
    Description:
    ============
    You are given two integers m and n representing the number of rows and
    columns of a grid, respectively.

    The cost to enter cell (i, j) is defined as (i + 1) * (j + 1).

    You are also given a 2D integer array waitCost where waitCost[i][j] defines
    the cost to wait on that cell.

    You start at cell (0, 0) at second 1.

    At each step, you follow an alternating pattern:

        On odd-numbered seconds, you must move right or down to an adjacent
        cell, paying its entry cost. On even-numbered seconds, you must wait in
        place, paying waitCost[i][j].

    Return the minimum total cost required to reach (m - 1, n - 1).

    =========================================================================
    FUNCTION: long long minCost(int m, int n, vector<vector<int>>& waitCost);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: m = 1, n = 2, waitCost = [[1,2]]
    Output: 3
    Explanation:
    The optimal path is:
        Start at cell (0, 0) at second 1 with entry cost (0 + 1) * (0 + 1) = 1.
        Second 1: Move right to cell (0, 1) with entry cost (0 + 1) * (1 + 1) = 2.
    Thus, the total cost is 1 + 2 = 3.

    --- Example 2 ---
    Input: m = 2, n = 2, waitCost = [[3,5],[2,4]]
    Output: 9
    Explanation:
    The optimal path is:
        Start at cell (0, 0) at second 1 with entry cost (0 + 1) * (0 + 1) = 1.
        Second 1: Move down to cell (1, 0) with entry cost (1 + 1) * (0 + 1) = 2.
        Second 2: Wait at cell (1, 0), paying waitCost[1][0] = 2.
        Second 3: Move right to cell (1, 1) with entry cost (1 + 1) * (1 + 1) = 4.
    Thus, the total cost is 1 + 2 + 2 + 4 = 9.

    --- Example 3 ---
    Input: m = 2, n = 3, waitCost = [[6,1,4],[3,2,5]]
    Output: 16
    Explanation:
    The optimal path is:
        Start at cell (0, 0) at second 1 with entry cost (0 + 1) * (0 + 1) = 1.
        Second 1: Move right to cell (0, 1) with entry cost (0 + 1) * (1 + 1) = 2.
        Second 2: Wait at cell (0, 1), paying waitCost[0][1] = 1.
        Second 3: Move down to cell (1, 1) with entry cost (1 + 1) * (1 + 1) = 4.
        Second 4: Wait at cell (1, 1), paying waitCost[1][1] = 2.
        Second 5: Move right to cell (1, 2) with entry cost (1 + 1) * (2 + 1) = 6.
    Thus, the total cost is 1 + 2 + 1 + 4 + 2 + 6 = 16.


    *** Constraints ***
    1 <= m, n <= 10^5
    2 <= m * n <= 10^5
    waitCost.length == m
    waitCost[0].length == n
    0 <= waitCost[i][j] <= 10^5

*/

#include <climits>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple Dijkstra.

*/

/* Time  Beats: 36.84% */
/* Space Beats: 63.16% */

/* Time  Complexity: O(M * N * log(M * N)) */
/* Space Complexity: O(M * N)              */
class Solution {
public:
    long long minCost(int m, int n, vector<vector<int>>& waitCost)
    {
        const int ROWS = waitCost.size();
        const int COLS = waitCost[0].size();

        priority_queue<vector<long long>, vector<vector<long long>>, greater<vector<long long>>> min_heap;
        min_heap.push( {1LL, 0LL, 0LL} );

        vector<vector<long long>> help(ROWS, vector<long long>(COLS, LLONG_MAX));
        help[0][0] = 1LL;

        while ( ! min_heap.empty())
        {
            long long cost = min_heap.top()[0];
            long long row  = min_heap.top()[1];
            long long col  = min_heap.top()[2];
            min_heap.pop();

            if (help[row][col] != cost)
                continue;

            if (row == m-1 && col == n-1)
                return static_cast<long long>(cost - waitCost[m-1][n-1]);

            if (row+1 < m)
            {
                long long c = cost + (row+1 + 1) * (col + 1) + waitCost[row+1][col];

                if (c < help[row+1][col])
                {
                    min_heap.push( {c, row+1, col} );
                    help[row+1][col] = c;
                }
            }

            if (col+1 < n)
            {
                long long c = cost + (row + 1) * (col+1 + 1) + waitCost[row][col+1];

                if (c < help[row][col+1])
                {
                    min_heap.push( {c, row, col+1} );
                    help[row][col+1] = c;
                }
            }
        }

        return 0;
    }
};
