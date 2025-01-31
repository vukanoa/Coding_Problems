/*
    ============
    === HARD ===
    ============

    ===========================
    827) Making A Large Island
    ===========================

    ============
    Description:
    ============

    You are given an n x n binary matrix grid. You are allowed to change at most
    one 0 to be 1.

    Return the size of the largest island in grid after applying this operation

    An island is a 4-directionally connected group of 1s.

    =======================================================
    FUNCTION: int largestIsland(vector<vector<int>>& grid);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,0],[0,1]]
    Output: 3
    Explanation: Change one 0 to 1 and connect two 1s, then we get an island
                 with area = 3.

    --- Example 2 ---
    Input: grid = [[1,1],[1,0]]
    Output: 4
    Explanation: Change the 0 to 1 and make the island bigger, only one island
                 with area = 4.

    --- Example 3 ---
    Input: grid = [[1,1],[1,1]]
    Output: 4
    Explanation: Can't change any 0 to 1, only one island with area = 4.


    *** Constraints ***
    n == grid.length
    n == grid[i].length
    1 <= n <= 500
    grid[i][j] is either 0 or 1.

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This one is not very difficult, but it is consisted of quite a few parts.

    First, Constraints can be misleading. Even though 500 is not a big number
    we still cannot do a Brute-Brufe-Force which would be an
    O((ROWS * COLS)^2) Time Complexity.


    So, what would a Brute-Force even look like?

    Since we are allowed to change ONLY ONE zero to one, then we should start
    at every zero, as if it's a 1 and count the size of the connected island,
    i.e. how many cells are in this one, now connected, island.

    For example:

           0     1     2     3
        +-----+-----+-----+-----+
     0  |  0  |  1  |  0  |  0  |
        +-----+-----+-----+-----+
     1  |  1  |  1  |  0  |  1  |
        +-----+-----+-----+-----+
     2  |  1  |  0  |  0  |  1  |
        +-----+-----+-----+-----+

    We'd do a DFS starting at every 0-cell and count current 0-cell as 1.

    If we were to start at cell grid[0][0], we would have an island of size 5.
    If we were to start at cell grid[0][2], we would have an island of size 5.
    If we were to start at cell grid[0][3], we would have an island of size 3.
    If we were to start at cell grid[1][2], we would have an island of size 7.
    If we were to start at cell grid[2][1], we would have an island of size 5.
    If we were to start at cell grid[2][2], we would have an island of size 3.

    We can see that the biggest island would be create had we started from
    grid[1][2], that way we'd connect the left island of size 4 and the right
    island of size 2, and we'd add 1 to it since the current cell should be
    treated as a 1, since we can change at most one 0-cell to 1.


    But this would take O(ROWS * COLS) for each cell in the grid. That means
    the total Time Complexity would be O((ROWS * COLS)^2), which is, even for
    these Constraints, unacceptable.


    So, what should we do?

    It would be awesome if we could have a size of the entire connected island
    in each cell of that island.

    This sounds confusing, let's look at the picture:

               0     1     2     3
            +-----+-----+-----+-----+
         0  |  0  |  1  |  0  |  0  |
            +-----+-----+-----+-----+
         1  |  1  |  1  |  0  |  1  |
            +-----+-----+-----+-----+
         2  |  1  |  0  |  0  |  1  |
            +-----+-----+-----+-----+

    If we had an above example, it would be awesome if we could have this:


               0     1     2     3
            +-----+-----+-----+-----+
         0  |  0  |  4  |  0  |  0  |
            +-----+-----+-----+-----+
         1  |  4  |  4  |  0  |  2  |
            +-----+-----+-----+-----+
         2  |  4  |  0  |  0  |  2  |
            +-----+-----+-----+-----+

    Now each non-zero cell, instead of 1, has a total size of the island that
    it is a part of.

    For example cell grid[0][1] = 4.
    Why?

    Because grid[0][1] is a part of the island:
        grid[0][1]
        grid[1][1]
        grid[1][0]
        grid[2][0]

    This whole connected island is of size 4. Therefore, we want each cell to
    boldly proclaim "I'm a cell which is a part of the island of size 4".

    But, why do we need that? What is the point?

    We need that because then we can start at any 0-cell and check all of the
    4-adjacent cells and check if those adjacent cells are a part of some
    islands and immediately know the size of their sizes.

    In our above example:

               0     1     2     3
            +-----+-----+-----+-----+
         0  |  0  |  4  |  0  |  0  |
            +-----+-----+-----+-----+
         1  |  4  |  4  |  0  |  2  |
            +-----+-----+-----+-----+
         2  |  4  |  0  |  0  |  2  |
            +-----+-----+-----+-----+

    Once we get at 0-cell at grid[1][2] == 0, we can check:

        1) What is the size of the island ABOVE the current cell?    It's 0.
        2) What is the size of the island BELOW the current cell?    It's 0.
        3) What is the size of the island LEFT  of the current cell? It's 4.
        4) What is the size of the island RIGHT of the current cell? It's 2.

    So 2 + 4 = 6. Howwever, don't forget that we've changed this current 0-cell
    to 1 and thus have to include that one as well.

    Therefore, the final answer would be 7, which we know is the correct answer


    However, there's one problem with this. What if we had some example like
    this:

               0     1
            +-----+-----+
         0  |  0  |  1  |
            +-----+-----+
         1  |  1  |  1  |
            +-----+-----+
         2  |  1  |  0  |
            +-----+-----+

    Had we performed our "trick" and have put size of the entire island in each
    cell that the current island is a part of, we'd have this:

               0     1
            +-----+-----+
         0  |  0  |  4  |
            +-----+-----+
         1  |  4  |  4  |
            +-----+-----+
         2  |  4  |  0  |
            +-----+-----+

    So, what is the problem?
    The problem is that if we start at 0-cell and check:
        1) up
        2) down
        3) left
        4) right

    We'd get this:
        1) What is the size of the island ABOVE the current cell?    It's 0.
        2) What is the size of the island BELOW the current cell?    It's 4.
        3) What is the size of the island LEFT  of the current cell? It's 0.
        4) What is the size of the island RIGHT of the current cell? It's 4.

    It would seem as if the correct result is: 4 + 4 + 1 = 9, which would be
    INOCRRECT.

    Why?

    Because we've counted THE SAME ISLAND twice. We've included the same island
    by going down and to the right.

    Think about it, had we changed this grid[0][0] to 1, we would now have an
    island of size 9 right?
    We'd have an island of size 5.

    So, how do we get around this problem?

    It's actually much more simple than you probably think. We'll have an
    additional grid, called "which_island", where we're going to mark each cell
    of one island with one number, strating at 1. Then the next island that is
    separated from the previous island is going to have all number 2s in it,
    etc.

    How does this help us?

    It helps us because once we trie to "bridge" our 4-adjacent islands, we
    can check if any of them are part of the same island. If that is the case
    then we want to include it ONLY ONCE.

    Let's show it on our example:
    This part will remain the same.

               0     1
            +-----+-----+
         0  |  0  |  4  |
            +-----+-----+
         1  |  4  |  4  |
            +-----+-----+
         2  |  4  |  0  |
            +-----+-----+

    But now, we have another grid of same size, where we'll put the number of
    island that the current cell is a part of. Since there is only a single
    island in this one, all' non-zero cells will have a number of 1.

               0     1
            +-----+-----+
         0  |  0  |  1  |
            +-----+-----+
         1  |  1  |  1  |
            +-----+-----+
         2  |  1  |  0  |
            +-----+-----+

    This may seem as if we've gone back to the beginning so - WHy do it in the
    first place.

    Let's look at a better example:


               0     1     2     3     4     5
            +-----+-----+-----+-----+-----+-----+
         0  |  1  |  1  |  0  |  1  |  1  |  1  |
            +-----+-----+-----+-----+-----+-----+
         1  |  1  |  1  |  0  |  0  |  1  |  1  |
            +-----+-----+-----+-----+-----+-----+
         2  |  0  |  0  |  0  |  0  |  0  |  0  |
            +-----+-----+-----+-----+-----+-----+
         3  |  1  |  1  |  0  |  1  |  1  |  1  |
            +-----+-----+-----+-----+-----+-----+

    Out initial "trick" remains the same:

               0     1     2     3     4     5
            +-----+-----+-----+-----+-----+-----+
         0  |  4  |  4  |  0  |  5  |  5  |  5  |
            +-----+-----+-----+-----+-----+-----+
         1  |  4  |  4  |  0  |  0  |  5  |  5  |
            +-----+-----+-----+-----+-----+-----+
         2  |  0  |  0  |  0  |  0  |  0  |  0  |
            +-----+-----+-----+-----+-----+-----+
         3  |  2  |  2  |  0  |  3  |  3  |  3  |
            +-----+-----+-----+-----+-----+-----+


    However, now we have "which_islands", that will look like this:

               0     1     2     3     4     5
            +-----+-----+-----+-----+-----+-----+
         0  |  1  |  1  |  0  |  2  |  2  |  2  |
            +-----+-----+-----+-----+-----+-----+
         1  |  1  |  1  |  0  |  0  |  2  |  2  |
            +-----+-----+-----+-----+-----+-----+
         2  |  0  |  0  |  0  |  0  |  0  |  0  |
            +-----+-----+-----+-----+-----+-----+
         2  |  3  |  3  |  0  |  4  |  4  |  4  |
            +-----+-----+-----+-----+-----+-----+

    The picture seems confusing at first, but what it represents is the
    consecutive ID of an island in the grid, going left-to-right and then
    top-to-bottom.

    That's why the:
    island of size 4 is the 1st island.
    Island of size 5 is the 2nd island
    Island of size 2 is the 3rd island
    Island of size 4 is the 4th island

    In this specific example we didn't actually need to do this "which_islands"
    part, however it would be necessary in examples like this:

               0     1     2
            +-----+-----+-----+-----+
         0  |  1  |  1  |  0  |  0  |
            +-----+-----+-----+-----+
         1  |  1  |  0  |  1  |  1  |
            +-----+-----+-----+-----+
         2  |  1  |  0  |  1  |  0  |
            +-----+-----+-----+-----+

    Our initial "trick":

               0     1     2     3
            +-----+-----+-----+-----+
         0  |  4  |  4  |  0  |  0  |
            +-----+-----+-----+-----+
         1  |  4  |  0  |  3  |  3  |
            +-----+-----+-----+-----+
         2  |  4  |  0  |  3  |  0  |
            +-----+-----+-----+-----+


    "which_islands":

               0     1     2     3
            +-----+-----+-----+-----+
         0  |  1  |  1  |  0  |  0  |
            +-----+-----+-----+-----+
         1  |  1  |  0  |  2  |  2  |
            +-----+-----+-----+-----+
         2  |  1  |  0  |  2  |  0  |
            +-----+-----+-----+-----+

    Now once we get to grid[1][1] == 0, we are going to innclude island of 4
    ONLY ONCE, even though it is both above and left of the current cell.

    Island of size 3 will be included once anyway because it appears to be only
    to the right of the current grid[1][1] cell.

    This way our total result would be: 4 + 3 + 1 = 8
    And that is a correct answer.

    Had we not have this "which_islands", we'd have: 4 + 4 + 3 + 1 = 12, which
    would NOT be correct.


    Once you get this high-idea, the code is self-explanatory, even if it is a
    bit lengthy.

*/

/* Time  Beats: 17.25% */
/* Space Beats:  8.14% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    int largestIsland(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int result = 0;

        vector<vector<int>> which_island(ROWS, vector<int>(COLS, 0));

        vector<vector<bool>> visited_1 = vector(ROWS, vector<bool>(COLS, false));
        vector<vector<bool>> visited_2 = vector(ROWS, vector<bool>(COLS, false));

        int island = 1;
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 1 && !visited_1[row][col])
                {
                    int size_of_island = dfs(grid, row, col, visited_1);
                    dfs_fill_islands(grid, row, col, visited_2, size_of_island, which_island, island);
                    island++;
                }
            }
        }

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == 0)
                {
                    int size = 1;
                    unordered_set<int> uset;

                    if (row-1 >= 0)
                    {
                        size += grid[row-1][col];
                        uset.insert(which_island[row-1][col]);
                    }

                    if (row+1 < ROWS && !uset.count(which_island[row+1][col]))
                    {
                        size += grid[row+1][col];
                        uset.insert(which_island[row+1][col]);
                    }

                    if (col-1 >= 0 && !uset.count(which_island[row][col-1]))
                    {
                        size += grid[row][col-1];
                        uset.insert(which_island[row][col-1]);
                    }

                    if (col+1 < COLS && !uset.count(which_island[row][col+1]))
                    {
                        size += grid[row][col+1];
                        uset.insert(which_island[row][col+1]);
                    }

                    result = max(result, size);
                }
            }
        }

        return result == 0 ? ROWS * COLS : result;
    }

private:
    int dfs(vector<vector<int>>& grid, int row, int col, vector<vector<bool>>& visited)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row == ROWS || col == COLS)
            return 0;

        if (visited[row][col] || grid[row][col] == 0)
            return 0;

        visited[row][col] = true;

        int up    = dfs(grid, row-1, col  , visited);
        int down  = dfs(grid, row+1, col  , visited);
        int left  = dfs(grid, row  , col-1, visited);
        int right = dfs(grid, row  , col+1, visited);

        return 1 + up + down + left + right;
    }

    void dfs_fill_islands(vector<vector<int>>& grid, int row, int col, vector<vector<bool>>& visited, int size_of_island, vector<vector<int>>& which_island, int island)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row == ROWS || col == COLS)
            return;

        if (visited[row][col] || grid[row][col] == 0)
            return;

        visited[row][col] = true;
        which_island[row][col] = island;
        grid[row][col] = size_of_island;

        dfs_fill_islands(grid, row-1, col  , visited, size_of_island, which_island, island);
        dfs_fill_islands(grid, row+1, col  , visited, size_of_island, which_island, island);
        dfs_fill_islands(grid, row  , col-1, visited, size_of_island, which_island, island);
        dfs_fill_islands(grid, row  , col+1, visited, size_of_island, which_island, island);
    }
};
