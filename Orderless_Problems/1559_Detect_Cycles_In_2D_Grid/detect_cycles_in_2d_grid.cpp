/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    1559) Detect Cycles in 2D Grid
    ==============================

    ============
    Description:
    ============

    Given a 2D array of characters grid of size m x n, you need to find if
    there exists any cycle consisting of the same value in grid.

    A cycle is a path of length 4 or more in the grid that starts and ends at
    the same cell. From a given cell, you can move to one of the cells adjacent
    to it - in one of the four directions (up, down, left, or right), if it has
    the same value of the current cell.

    Also, you cannot move to the cell that you visited in your last move. For
    example, the cycle (1, 1) -> (1, 2) -> (1, 1) is invalid because from (1,
    2) we visited (1, 1) which was the last visited cell.

    Return true if any cycle of the same value exists in grid, otherwise,
    return false.

    =========================================================
    FUNCTION: bool containsCycle(vector<vector<char>>& grid);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [["a","a","a","a"],["a","b","b","a"],["a","b","b","a"],["a","a","a","a"]]
    Output: true

    --- Example 2 ---
    Input: grid = [["c","c","c","a"],["c","d","c","c"],["c","c","e","c"],["f","c","c","c"]]
    Output: true

    --- Example 3 ---
    Input: grid = [["a","b","b"],["b","z","b"],["b","b","a"]]
    Output: false


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 500
    grid consists only of lowercase English letters.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Cycle makes it "more difficult" than some other 2D-matching problems.

    We needed to utilized both "path" and "failed" matrices in order to
    accomplish what we're asked.

    We could've done with only one additional matrix, however the code would
    be much more difficult to read and grasp.

*/

/* Time  Beats: 51.18% */
/* Space Beats: 65.61% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_DFS_Cycle_Detection {
public:
    bool containsCycle(vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<bool>> path(ROWS, vector<bool>(COLS, false));
        vector<vector<bool>> failed(ROWS, vector<bool>(COLS, false));

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (failed[row][col])
                    continue;

                char chr = grid[row][col];

                if (dfs(row, col, chr, -1, -1, path, failed, grid))
                    return true;
            }
        }

        return false;
    }

    bool dfs(int row, int col, char chr, int prev_row, int prev_col, vector<vector<bool>>& path, vector<vector<bool>>& failed, vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        /* Out-of-Bounds */
        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return false;

        /* Wrong character OR already failed path */
        if (grid[row][col] != chr || failed[row][col])
            return false;

        /* Already visited on this path---Cycle! */
        if (path[row][col])
            return true;

        path[row][col] = true;

        /* Signing Cross */
        if ( ! (row-1== prev_row && col  == prev_col) && dfs(row-1, col  , chr, row, col, path, failed, grid)) return true; // Up
        if ( ! (row+1== prev_row && col  == prev_col) && dfs(row+1, col  , chr, row, col, path, failed, grid)) return true; // Down
        if ( ! (row  == prev_row && col-1== prev_col) && dfs(row  , col-1, chr, row, col, path, failed, grid)) return true; // Left
        if ( ! (row  == prev_row && col+1== prev_col) && dfs(row  , col+1, chr, row, col, path, failed, grid)) return true; // Right

        path[row][col] = false;
        failed[row][col] = true;

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a fundamental DSU problem for cycle-detection.

    First, you must understand DSU by heart, then come here to read this.
    It's a really fundamental technique with DSU, however it requires that you
    already have a solid understanding of DSU.

*/

/* Time  Beats: 97.00% */
/* Space Beats: 96.61% */

/* Time  Complexity: O(ROWS * COLS * alpha(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COLS)                      */
class DSU {
private:
    vector<int> rank;
    vector<int> parent;
    int components;

public:
    DSU (int n)
    {
        components = n;

        rank.resize(n);
        parent.resize(n);

        for (int i = 0; i < n; i++)
        {
            rank[i]   = 1;
            parent[i] = i;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Inverse Ackerman function */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        if (root_1 == root_2)
            return false;

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        components--;

        return true;
    }

    int number_of_components()
    {
        return components;
    }

    bool are_connected(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        return root_1 == root_2;
    }
};

class Solution_DSU_Cycle_Detection {
public:
    bool containsCycle(vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        DSU dsu(ROWS * COLS);

        auto node_1D_idx = [&] (int row, int col) -> int{
            return row * COLS + col;
        };

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                /********/
                /** UP **/
                /********/
                // If UP is NOT Out-of_Bounds AND current chr == the above chr
                if (row-1 >= 0 && grid[row][col] == grid[row-1][col])
                {
                    // If these 2 components are NOT Unioned(i.e. merged) here,
                    // that means they're ALREADY connected---There is a CYCLE!
                    if ( ! dsu.union_components(node_1D_idx(row,   col  ),
                                                node_1D_idx(row-1, col  )))
                    {
                        return true;
                    }
                }

                /**********/
                /** LEFT **/
                /**********/
                // If UP is NOT Out-of_Bounds AND current chr == the above chr
                if (col-1 >= 0 && grid[row][col] == grid[row][col-1])
                {
                    // If these 2 components are NOT Unioned(i.e. merged) here,
                    // that means they're ALREADY connected---There is a CYCLE!
                    if ( ! dsu.union_components(node_1D_idx(row,   col  ),
                                                node_1D_idx(row  , col-1)))
                    {
                        return true;
                    }
                }
            }
        }

        return false;
    }
};
