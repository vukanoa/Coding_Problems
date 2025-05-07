/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    3341) Find Minimum Time to Reach Last Room I
    ============================================

    ============
    Description:
    ============

    There is a dungeon with n x m rooms arranged as a grid.

    You are given a 2D array moveTime of size n x m, where moveTime[i][j]
    represents the minimum time in seconds when you can start moving to that
    room. You start from the room (0, 0) at time t = 0 and can move to an
    adjacent room. Moving between adjacent rooms takes exactly one second.

    Return the minimum time to reach the room (n - 1, m - 1).

    Two rooms are adjacent if they share a common wall, either horizontally or
    vertically.

    ============================================================
    FUNCTION: int minTimeToReach(vector<vector<int>>& moveTime);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: moveTime = [[0,4],[4,4]]
    Output: 6
    Explanation:
    The minimum time required is 6 seconds.
        At time t == 4, move from room (0, 0) to room (1, 0) in one second.
        At time t == 5, move from room (1, 0) to room (1, 1) in one second.


    --- Example 2 ---
    Input: moveTime = [[0,0,0],[0,0,0]]
    Output: 3
    Explanation:
    The minimum time required is 3 seconds.
        At time t == 0, move from room (0, 0) to room (1, 0) in one second.
        At time t == 1, move from room (1, 0) to room (1, 1) in one second.
        At time t == 2, move from room (1, 1) to room (1, 2) in one second.


    --- Example 3 ---
    Input: moveTime = [[0,1],[1,2]]
    Output: 3


    *** Constraints ***
    2 <= n == moveTime.length <= 50
    2 <= m == moveTime[i].length <= 50
    0 <= moveTime[i][j] <= 10^9

*/

#include <vector>
#include <queue>
#include <climits>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Dijkstra on a 2D grip)

*/

/* Time  Beats: 22.47% */
/* Space Beats: 18.40% */

/* Time  Complexity: O(ROWS * COLS * log(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COLS)                    */
class Solution {
public:
    int minTimeToReach(vector<vector<int>>& moveTime)
    {
        const int ROWS = moveTime.size();
        const int COLS = moveTime[0].size();

        vector<vector<int>> used(ROWS, vector<int>(COLS, false));
        used[0][0] = true;

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;
        min_heap.push( {0, 0, 0} );

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            int curr_time = top[0];
            int row       = top[1];
            int col       = top[2];

            if (row == ROWS-1 && col == COLS-1) // If we're on the goal-cell
                return curr_time;


            for (const auto& dir : directions)
            {
                int new_row = row + dir.first;
                int new_col = col + dir.second;

                if (new_row < 0 || new_col < 0 || new_row == ROWS || new_col == COLS)
                    continue;

                if (used[new_row][new_col])
                    continue;

                int new_curr_time = curr_time >= moveTime[new_row][new_col] ? curr_time + 1 : moveTime[new_row][new_col] + 1;

                min_heap.push( { new_curr_time, new_row, new_col} );
                used[new_row][new_col] = true;
            }
        }

        return 0; // Unreachable code
    }
};
