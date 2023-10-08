#include <iostream>
#include <vector>
#include <queue>

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


/*
    ------------
    --- IDEA ---
    ------------

    It's a basic BFS. The only "tricky" part are the first three things that
    are written in this Solution:
        1. Check if there aren't any fresh oranges left. If that is the case
           then return 0.

        2. Check if there aren't any rotten oranges at the beginning, if that
           is the case, then return -1.

        3. Fill the queue with **all** the rotten oranges at Minute 0.

    3rd one is very important since that is the initial state of the queue upon
    entering the while loop of the BFS functionality.

    Each level in BFS is one "Minute".

    At the end just check if there are any fresh oranges left(ones that aren't
    able to be reached). If there are, return -1, else return number of elapsed
    minutes.

*/

/* Time  Beats:   100% */
/* Space Beats: 76.48% */

/* Time  Complexity: O(n * m) */
/* Space Complexity: O(num of (fresh + rotten) oranges) */
class Solution{
public:
    int orangesRotting(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        /* If there aren't any fresh oranges left, return 0 */
        if (leftover_fresh(grid) == false)
            return 0;

        /* If there aren't any rotten oranges at the beginning, return -1 */
        if (no_rotten_ones(grid))
            return -1;

        /* Fill the queue with all rotten oranges found on minute 0 */
        std::queue<std::pair<int, int>> queue;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 2)
                    queue.push({i, j});
            }
        }

        /* Directions */
        std::vector<std::pair<int, int>> directions = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

        int minutes = -1;

        /* BFS */
        while (!queue.empty())
        {
            int tmp = queue.size() - 1;

            while (tmp-- >= 0)
            {
                auto curr = queue.front();
                queue.pop();

                for (auto& dir : directions)
                {
                    int row = curr.first  + dir.first;
                    int col = curr.second + dir.second;

                    if (row >= 0 && row < m && col >= 0 && col < n && grid[row][col] == 1)
                    {
                        queue.push({row, col});
                        grid[row][col] = 2;
                    }
                }
            }

            minutes++;
        }

        /* If there aren't any fresh oranges left, return -1, else minutes */
        return leftover_fresh(grid) ? -1 : minutes;
    }

private:
    /* Checks if there are any fresh oranges left in entire grid */
    bool leftover_fresh(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                    return true;
            }
        }

        return false;
    }

    /* Check if there aren't any rotten oranges. If there aren't return true */
    bool no_rotten_ones(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 2)
                    return false;
            }
        }

        return true;
    }
};


int
main()
{
    Solution sol;

    /* Example 1 */
    // std::vector<std::vector<int>> grid = {{2, 1, 1}, {1, 1, 0}, {0, 1, 1}};

    /* Example 2 */
    // std::vector<std::vector<int>> grid = {{2, 1, 1}, {0, 1, 1}, {1, 0, 1}};

    /* Example 3 */
    // std::vector<std::vector<int>> grid = {{0, 2}};

    /* Example 4 */
    // std::vector<std::vector<int>> grid =
    // {
    //  {2,0,1,1,1},
    //  {1,0,1,0,1},
    //  {1,0,1,0,1},
    //  {1,0,0,0,1},
    //  {1,1,1,1,1}
    // };

    /* Example 5 */
    std::vector<std::vector<int>> grid =
    {
     {2,0,1,1,1,1,1,1,1,1},
     {1,0,1,0,0,0,0,0,0,1},
     {1,0,1,0,1,1,1,1,0,1},
     {1,0,1,0,1,0,0,1,0,1},
     {1,0,1,0,1,0,0,1,0,1},
     {1,0,1,0,1,1,0,1,0,1},
     {1,0,1,0,0,0,0,1,0,1},
     {1,0,1,1,1,1,1,1,0,1},
     {1,0,0,0,0,0,0,0,0,1},
     {1,1,1,1,1,1,1,1,1,1}
    };

    /* Example 6 */
    // std::vector<std::vector<int>> grid = {{2,2,2,1,1}};


    std::cout << "\n\t=======================";
    std::cout << "\n\t=== ROTTING ORANGES ===";
    std::cout << "\n\t=======================\n\n";


    /* Write Output */
    bool first = true;
    std::cout << "\n\tGrid:\n\t\t";
    for (auto x: grid)
    {
        for (const auto& xx : x)
        {
            printf("%2d ", xx);
        }
        std::cout << "\n\t\t";
    }
    std::cout << "\n";


    /* Solution */
    int output = sol.orangesRotting(grid);


    /* Write Output */
    std::cout << "\n\tOutput: " << output << "\n\n";


    return 0;
}
