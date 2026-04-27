/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    1391) Check if There is a Valid Path in a Grid
    ==============================================

    ============
    Description:
    ============


    You are given an m x n grid. Each cell of grid represents a street. The
    street of grid[i][j] can be:

        1 which means a street connecting the left  cell and the right cell.
        2 which means a street connecting the upper cell and the lower cell.
        3 which means a street connecting the left  cell and the lower cell.
        4 which means a street connecting the right cell and the lower cell.
        5 which means a street connecting the left  cell and the upper cell.
        6 which means a street connecting the right cell and the upper cell.

    You will initially start at the street of the upper-left cell (0, 0).

    A valid path in the grid is a path that starts from the upper left cell
    (0, 0) and ends at the bottom-right cell (m - 1, n - 1). The path should
    only follow the streets.

    Notice that you are not allowed to change any street.

    Return true if there is a valid path in the grid or false otherwise.

    =======================================================
    FUNCTION: bool hasValidPath(vector<vector<int>>& grid);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[2,4,3],[6,5,2]]
    Output: true
    Explanation: As shown you can start at cell (0, 0) and visit all the cells
                 of the grid to reach (m - 1, n - 1).

    --- Example 2 ---
    Input: grid = [[1,2,1],[1,2,1]]
    Output: false
    Explanation: As shown you the street at cell (0, 0) is not connected with
                 any street of any other cell and you will get stuck at cell
                 (0, 0)

    --- Example 3 ---
    Input: grid = [[1,1,2]]
    Output: false
    Explanation: You will get stuck at cell (0, 1) and you cannot reach cell
                 (0, 2).


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    1 <= grid[i][j] <= 6

*/

#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic DFS. It can be considered "Simulation DFS". Just follow the rules.

*/

/* Time  Beats: 66.94% */
/* Space Beats: 32.26% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_DFS_Unordered_Set {
public:
    bool hasValidPath(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        // Can't go OUT from cell (0,0) or can't go IN cell (ROWS-1, COLS-1)
        if (grid[0][0] == 5 || grid[ROWS-1][COLS-1] == 4)
            return false;

        vector<unordered_set<int>> allowed(4, unordered_set<int>());
        allowed[0] = {2,3,4}; // Up
        allowed[1] = {2,5,6}; // Down
        allowed[2] = {1,4,6}; // Left
        allowed[3] = {1,3,5}; // Right

        vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

        /* DFS */
        return dfs(ROWS-1, COLS-1, allowed, visited, grid);
    }

    bool dfs(int row, int col, vector<unordered_set<int>>& allowed, vector<vector<bool>>& visited, vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int UP    = 0;
        const int DOWN  = 1;
        const int LEFT  = 2;
        const int RIGHT = 3;

        if (visited[row][col])
            return false;

        if (row == 0 && col == 0)
            return true;

        visited[row][col] = true;

        switch (grid[row][col])
        {
            case 1:
                // LEFT
                if (col-1 >= 0 && allowed[LEFT].count(grid[row][col-1]))
                {
                    if (dfs(row, col-1, allowed, visited, grid))
                        return true;
                }

                // RIGHT
                if (col+1 < COLS && allowed[RIGHT].count(grid[row][col+1]))
                {
                    if (dfs(row, col+1, allowed, visited, grid))
                        return true;
                }
                break;

            case 2:
                // UP
                if (row-1 >= 0 && allowed[UP].count(grid[row-1][col]))
                {
                    if (dfs(row-1, col, allowed, visited, grid))
                        return true;
                }

                // DOWN
                if (row+1 < ROWS && allowed[DOWN].count(grid[row+1][col]))
                {
                    if (dfs(row+1, col, allowed, visited, grid))
                        return true;
                }
                break;

            case 3:
                // LEFT
                if (col-1 >= 0 && allowed[LEFT].count(grid[row][col-1]))
                {
                    if (dfs(row, col-1, allowed, visited, grid))
                        return true;
                }

                // DOWN
                if (row+1 < ROWS && allowed[DOWN].count(grid[row+1][col]))
                {
                    if (dfs(row+1, col, allowed, visited, grid))
                        return true;
                }
                break;

            case 4:
                // RIGHT
                if (col+1 < COLS && allowed[RIGHT].count(grid[row][col+1]))
                {
                    if (dfs(row, col+1, allowed, visited, grid))
                        return true;
                }

                // DOWN
                if (row+1 < ROWS && allowed[DOWN].count(grid[row+1][col]))
                {
                    if (dfs(row+1, col, allowed, visited, grid))
                        return true;
                }
                break;

            case 5:
                // LEFT
                if (col-1 >= 0 && allowed[LEFT].count(grid[row][col-1]))
                {
                    if (dfs(row, col-1, allowed, visited, grid))
                        return true;
                }

                // UP
                if (row-1 >= 0 && allowed[UP].count(grid[row-1][col]))
                {
                    if (dfs(row-1, col, allowed, visited, grid))
                        return true;
                }
                break;

            case 6:
                // RIGHT
                if (col+1 < COLS && allowed[RIGHT].count(grid[row][col+1]))
                {
                    if (dfs(row, col+1, allowed, visited, grid))
                        return true;
                }

                // UP
                if (row-1 >= 0 && allowed[UP].count(grid[row-1][col]))
                {
                    if (dfs(row-1, col, allowed, visited, grid))
                        return true;
                }
                break;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a Space optimization on "allowed". It's reallly beneficial to be
    able to see both and appreciate the optimization.

*/

/* Time  Beats: 79.03% */
/* Space Beats: 32.26% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_DFS_Bitmask {
public:
    bool hasValidPath(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        // Can't go OUT from cell (0,0) or can't go IN cell (ROWS-1, COLS-1)
        if (grid[0][0] == 5 || grid[ROWS-1][COLS-1] == 4)
            return false;

        int allowed[4] = {0};
        allowed[0] = (1 << 2) | (1 << 3) | (1 << 4); // Up
        allowed[1] = (1 << 2) | (1 << 5) | (1 << 6); // Down
        allowed[2] = (1 << 1) | (1 << 4) | (1 << 6); // Left
        allowed[3] = (1 << 1) | (1 << 3) | (1 << 5); // Right

        vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

        /* DFS */
        return dfs(ROWS-1, COLS-1, allowed, visited, grid);
    }

    bool dfs(int row, int col, int (& allowed)[4], vector<vector<bool>>& visited, vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int UP    = 0;
        const int DOWN  = 1;
        const int LEFT  = 2;
        const int RIGHT = 3;

        if (visited[row][col])
            return false;

        if (row == 0 && col == 0)
            return true;

        visited[row][col] = true;

        switch (grid[row][col])
        {
            case 1:
                // LEFT
                if (col-1 >= 0 && (allowed[LEFT] & (1 << grid[row][col-1])))
                {
                    if (dfs(row, col-1, allowed, visited, grid))
                        return true;
                }

                // RIGHT
                if (col+1 < COLS && (allowed[RIGHT] & (1 << grid[row][col+1])))
                {
                    if (dfs(row, col+1, allowed, visited, grid))
                        return true;
                }
                break;

            case 2:
                // UP
                if (row-1 >= 0 && (allowed[UP] & (1 << grid[row-1][col])))
                {
                    if (dfs(row-1, col, allowed, visited, grid))
                        return true;
                }

                // DOWN
                if (row+1 < ROWS && (allowed[DOWN] & (1 << grid[row+1][col])))
                {
                    if (dfs(row+1, col, allowed, visited, grid))
                        return true;
                }
                break;

            case 3:
                // LEFT
                if (col-1 >= 0 && (allowed[LEFT] & (1 << grid[row][col-1])))
                {
                    if (dfs(row, col-1, allowed, visited, grid))
                        return true;
                }

                // DOWN
                if (row+1 < ROWS && (allowed[DOWN] & (1 << grid[row+1][col])))
                {
                    if (dfs(row+1, col, allowed, visited, grid))
                        return true;
                }
                break;

            case 4:
                // RIGHT
                if (col+1 < COLS && (allowed[RIGHT] & (1 << grid[row][col+1])))
                {
                    if (dfs(row, col+1, allowed, visited, grid))
                        return true;
                }

                // DOWN
                if (row+1 < ROWS && (allowed[DOWN] & (1 << grid[row+1][col])))
                {
                    if (dfs(row+1, col, allowed, visited, grid))
                        return true;
                }
                break;

            case 5:
                // LEFT
                if (col-1 >= 0 && (allowed[LEFT] & (1 << grid[row][col-1])))
                {
                    if (dfs(row, col-1, allowed, visited, grid))
                        return true;
                }

                // UP
                if (row-1 >= 0 && (allowed[UP] & (1 << grid[row-1][col])))
                {
                    if (dfs(row-1, col, allowed, visited, grid))
                        return true;
                }
                break;

            case 6:
                // RIGHT
                if (col+1 < COLS && (allowed[RIGHT] & (1 << grid[row][col+1])))
                {
                    if (dfs(row, col+1, allowed, visited, grid))
                        return true;
                }

                // UP
                if (row-1 >= 0 && (allowed[UP] & (1 << grid[row-1][col])))
                {
                    if (dfs(row-1, col, allowed, visited, grid))
                        return true;
                }
                break;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Classic DSU(i.e. "Disjoint-Set Union") Solution.

    Wherenever we are asked to check the "connectedness" of two nodes/cells,
    we can most certainly use "DSU" to solve it.

    It's usually a much more elegant Solution than the alternatives, as you can
    see yourself.

*/

/* Time  Beats: 79.03% */
/* Space Beats: 49.60% */

/* Time  Complexity: O(ROWS * COLS * alpha(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COLS)                      */
class DSU {
private:
    vector<int> rank;
    vector<int> parent;
    int components;

public:
    DSU(int n)
    {
        rank.resize(n);
        parent.resize(n);

        components = n;

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

    bool connected_components(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        return root_1 == root_2;
    }
};

class Solution_dsu {
public:
    bool hasValidPath(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        // Can't go OUT from cell (0,0) or can't go IN cell (ROWS-1, COLS-1)
        if (grid[0][0] == 5 || grid[ROWS-1][COLS-1] == 4)
            return false;

        int up    = (1 << 2) | (1 << 3) | (1 << 4); // Up
        int down  = (1 << 2) | (1 << 5) | (1 << 6); // Down
        int left  = (1 << 1) | (1 << 4) | (1 << 6); // Left
        int right = (1 << 1) | (1 << 3) | (1 << 5); // Right

        DSU dsu(ROWS * COLS);

        auto index = [&](int row, int col) -> int {
            return row * COLS + col;
        };

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                // LEFT
                if (col-1 >= 0 && (left & (1 << grid[row][col-1])) && (right & (1 << grid[row][col])))
                {
                    dsu.union_components(index(row  , col-1),  // Left
                                         index(row  , col  )); // Current
                }

                // UP
                if (row-1 >= 0 && (up & (1 << grid[row-1][col])) && (down & (1 << grid[row][col])))
                {
                    dsu.union_components(index(row-1, col  ),  // Up
                                         index(row  , col  )); // Current

                }
            }
        }

        /* Check if Starting and Ending cells are connected */
        return dsu.connected_components(index(0     , 0     ), 
                                        index(ROWS-1, COLS-1));
    }

};
