/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    994) Rotting Oranges
    ===========================

    ============
    Description:
    ============

    You are given an m x n grid where each cell can have one of three values:
        # 0 representing an empty cell
        # 1 representing a fresh orange, or
        # 2 representing a rotten orange

    Every minutes, any fresh orange that is 4-directionally adjacent to a
    rotten orange becomes rotten.

    Return the minimum number of minutes that must elapse until no cell has a
    fresh orange. If this is impossible, return -1.

    =======================================================
    FUNCTION: int orangesRotting(vector<vector<int>>& grid);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

       Minute 0          Minute 1           Minute 2          Minute 3
    +---+---+---+     +---+---+---+      +---+---+---+     +---+---+---+
    | 2 | 1 | 1 |     | 2 | 2 | 1 |      | 2 | 2 | 2 |     | 2 | 2 | 2 |
    +---+---+---+     +---+---+---+      +---+---+---+     +---+---+---+
    | 1 | 1 | 0 |     | 2 | 1 | 0 |      | 2 | 2 | 0 |     | 2 | 2 | 0 |
    +---+---+---+     +---+---+---+      +---+---+---+     +---+---+---+
    | 0 | 1 | 1 |     | 0 | 1 | 1 |      | 0 | 1 | 1 |     | 0 | 2 | 1 |
    +---+---+---+     +---+---+---+      +---+---+---+     +---+---+---+


       Minute 4
    +---+---+---+
    | 2 | 2 | 2 |
    +---+---+---+
    | 2 | 2 | 0 |
    +---+---+---+
    | 0 | 2 | 2 |
    +---+---+---+



    --- Example 1 ---
    Input:  grid = [[2, 1, 1], [1, 1, 0], [0, 1, 1]]
    Output: 4

    --- Example 2 ---
    Input:  grid = [[2, 1, 1], [0, 1, 1], [1, 0, 1]]
    Output: -1
    Explanation: THe orange in the bottom left corner (row 2, column 0) is
    never rotten, because rotting only happens 4-directionally.

    --- Example 3 ---
    Input:  grid = [[0, 2]]
    Output: 0
    Explanation: Since there are already no fresh oranges at minut 0, the
    answer is just 0.

    *** Constraints ***
    m == grid.length
    n = grid[i].length
    1 <= m, n <= 10
    grid[i][j] is 0, 1, or 2.

*/

#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It's a basic BFS. The only "tricky" part are the first two things that
    are written in this Solution:
        1. Check if there aren't any fresh oranges left. If that is the case
           then return 0.

        2. Fill the queue with **ALL** the rotten oranges at Minute 0.

    The 2nd one is very important since that is the initial state of the queue
    upon entering the while loop of the BFS functionality.

    Each level in BFS is one "Minute", but we must take ALL of the INITIAL
    rotten oranges into account. Not one or only some of them.


    Because in order to push all of the INITIAL rotten oranges into our Queue
    we need to traverse the entire grid, we can use that to our advantage and
    also count the number of INITIALLY fresh oranges.

    Then we do level-by-level, i.e. minute-by-minute, and as soon as:

        1. The queue is NOT empty, and
        2. The TOTAL amount of FRESH oranges is GREATER than 0

    The 2nd condition is VERY important as it's an unusual thing to include in
    a BFS imiplementation.

    At the end simply check if the number of "fresh_oranges" is 0 or not and
    return accordingly.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  86.46% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_BFS {
public:
    int orangesRotting(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int fresh_oranges = 0;

        queue<pair<int,int>> queue;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 2)
                    queue.push( {row, col} );
                
                if (grid[row][col] == 1)
                    fresh_oranges++;
            }
        }

        vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        int minutes = 0;

        /* Multi-Source BFS */
        while (fresh_oranges > 0 && ! queue.empty())
        {

            int size = queue.size();
            while (size > 0)
            {
                auto [row, col] = queue.front();
                queue.pop();

                for (const auto& dir : directions)
                {
                    int new_row = row + dir.first;
                    int new_col = col + dir.second;

                    if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                        continue;

                    if (grid[new_row][new_col] != 1) // If it's NOT a fresh orange
                        continue;

                    grid[new_row][new_col] = 2; // Change Fresh to Rotten orange
                    fresh_oranges--;

                    queue.push( {new_row, new_col} );
                }

                // Decrement
                size--;
            }

            minutes++;
        }

        return fresh_oranges == 0 ? minutes : -1;
    }
};
