#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

/*
    ============
    === HARD ===
    ============

    ===========================
    778) Swim in Rising Water
    ===========================

    ============
    Description:
    ============

    You are given an n x n integer matrix grid where each value grid[i][j]
    represents the elevation at that point (i, j).

    The rain starts to fall. At time t, the depth of the water everywhere is t.
    You can swim from a square to another 4-directionally adjacent square if
    and only if the elevation of both squares individually are at most t. You
    can swim infinite distances in zero time. Of course, you must stay within
    the boundaries of the grid during your swim.

    Return the least time until you can reach the bottom right square (n - 1, n
    - 1) if you start at the top left square (0, 0).

    =====================================================
    FUNCTION: int swimInWater(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[0,2],[1,3]]
    Output: 3
    Explanation:
    At time 0, you are in grid location (0, 0).
    You cannot go anywhere else because 4-directionally adjacent neighbors have
    a higher elevation than t = 0.  You cannot reach point (1, 1) until time 3.
    When the depth of water is 3, we can swim anywhere inside the grid.


    --- Example 2 ---
    Input: grid = [[0,1,2,3,4],[24,23,22,21,5],[12,13,14,15,16],[11,17,18,19,20],[10,9,8,7,6]]
    Output: 16
    Explanation: The final route is shown.
    We need to wait until time 16 so that (0, 0) and (4, 4) are connected.


    *** Constraints ***
    n == grid.length
    n == grid[i].length
    1 <= n <= 50
    0 <= grid[i][j] < n^2
    Each value grid[i][j] is unique.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 12.40% */
/* Space Beats: 12.34% */

/* Time  Complexity: O(n^2 * logn) */
/* Space Complexity: O(n^2)        */
class Solution {
public:
    int swimInWater(vector<vector<int>>& grid)
    {
        int N = grid.size();

        set<pair<int, int>> visit;

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;  // (time/max-height, r, c)
        vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        visit.insert({0, 0});
        min_heap.push({grid[0][0], 0, 0});

        while ( ! min_heap.empty())
        {
            vector<int> cur = min_heap.top();
            min_heap.pop();

            int time = cur[0];
            int row  = cur[1];
            int col  = cur[2];

            if (row == N-1 && col == N-1)
                return time;

            for (auto& dir : directions)
            {
                int neighbor_row = row + dir[0], neighbor_col = col + dir[1];

                if (neighbor_row < 0 || neighbor_col < 0 || neighbor_row >= N || neighbor_col >= N || visit.count({neighbor_row, neighbor_col}))
                    continue;

                visit.insert({neighbor_row, neighbor_col});
                min_heap.push({max(time, grid[neighbor_row][neighbor_col]), neighbor_row, neighbor_col});
            }
        }

        return -1;  // This should never be reached if the input grid is valid
    }
};
