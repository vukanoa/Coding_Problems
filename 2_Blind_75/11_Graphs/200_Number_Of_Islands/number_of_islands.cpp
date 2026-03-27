/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    200) Number of Islands
    ===========================

    ============
    Description:
    ============

    Given an m x n 2D binary grid "grid" which represents a map of '1's(land)
    and '0's(water), return the number of islands.

    An island is surrounded by water and is formed by connecting adjacent lands
    horizontally or vertically. You may assume all four edges of the grid are
    all surrounded by water.

    =====================================================
    FUNCTION: int numIslands(vector<vector<char>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  grid = [
        ["1", "1", "1", "1", "0"],
        ["1", "1", "0", "1", "0"],
        ["1", "1", "0", "0", "0"],
        ["0", "0", "0", "0", "0"],
        ]
    Output: 1

    --- Example 2 ---
    Input:  grid = [
        ["1", "1", "0", "0", "0"],
        ["1", "1", "0", "0", "0"],
        ["0", "0", "1", "0", "0"],
        ["0", "0", "0", "1", "1"],
        ]
    Output: 3

    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 300
    grid[i][j] is '0' or '1'

*/

#include <vector>
#include <queue>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    A simple self-explanatory DFS.

*/

/* Time  Beats: 98.84% */
/* Space Beats: 85.21% */

/* Time  Complexity:
    O(n) or O(row * columns) or O(V) 'V' for Vertices in Graph
*/
/* Space Complexity: O(n)
    Recursion can go up to N levels deep since we can have all 1's in "grid".
*/
class Solution_DFS {
public:
    int numIslands(vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int islands = 0;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == '1')
                {
                    dfs(row, col, grid);
                    islands++;
                }
            }
        }

        /* Restore original Grid */
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == '#')
                    grid[row][col] = '1';
            }
        }

        return islands;
    }

private:
    void dfs(int row, int col, vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return;

        if (grid[row][col] != '1')
            return;

        grid[row][col] = '#';

        /* Signing Cross */
        dfs(row-1, col  , grid); // Up
        dfs(row+1, col  , grid); // Down
        dfs(row  , col-1, grid); // Left
        dfs(row  , col+1, grid); // Right
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 41.82% */
/* Space Beats: 29.37% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_BFS {
public:
    int numIslands(vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int islands = 0;

        /* Signing Cross */
        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == '1')
                {
                    islands++;

                    grid[row][col] = '#'; // Visited

                    queue<pair<int, int>> queue;
                    queue.push( {row, col} );

                    /* BFS */
                    while ( ! queue.empty())
                    {
                        /* We don't care about level-by-level, just do flood */
                        auto [curr_row, curr_col] = queue.front();
                        queue.pop();

                        for (const auto& dir : directions)
                        {
                            int new_row = curr_row + dir.first;
                            int new_col = curr_col + dir.second;

                            if (new_row < 0      || 
                                new_col < 0      ||
                                new_row >= ROWS  ||
                                new_col >= COLS)
                            {
                                continue;
                            }

                            if (grid[new_row][new_col] != '1')
                                continue;

                            grid[new_row][new_col] = '#'; // Mark as visited
                            queue.push( {new_row, new_col} );
                        }

                    }
                }
            }
        }

        /* Restore original Grid */
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == '#')
                    grid[row][col] = '1';
            }
        }

        return islands;
    }
};





/*
    ------------
    --- IDEA ---
    ------------

    This one uses 2D vectors for both "rank" and "parent'.

    I wanted to include this Implementation as well so that you can compare it
    and see why we're doing the "1D flattening technique" in the 2nd DSU
    Solution.

*/

/* Time  Beats: 97.99% */
/* Space Beats: 35.19% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
struct DSU_non_optimal {
    vector<vector<int>> rank;
    vector<vector<pair<int,int>>> parent;

    DSU_non_optimal (const int& ROWS, const int& COLS)
    {
        rank.resize(ROWS, vector<int>(COLS, 1));

        parent.resize(ROWS, vector<pair<int,int>>(COLS, pair<int,int>()));
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
                parent[row][col] = {row, col};
        }
    }

    pair<int,int> find_root_node(pair<int,int> node)
    {
        while (node != parent[node.first][node.second])
        {
            int row = node.first;
            int col = node.second;

            /* Reverse Ackerman function */
            parent[row][col] = parent[parent[row][col].first]
                                     [parent[row][col].second];

            node = parent[row][col];
        }

        return node;
    }

    bool union_components(pair<int,int> node_1, pair<int,int> node_2)
    {
        pair<int,int> a = find_root_node(node_1);
        pair<int,int> b = find_root_node(node_2);

        if (a == b)
            return false;

        if (rank[a.first][a.second] < rank[b.first][b.second])
            swap(a, b);

        // Make sure that to merge TOWARDS the smaller node, i.e. root "a"
        parent[b.first][b.second] = a;
        rank[a.first][a.second]  += rank[b.first][b.second];

        return true;
    }
};

class Solution_DSU_non_optimal {
public:
    int numIslands(vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int islands = 0;

        DSU_non_optimal dsu(ROWS, COLS);

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == '1')
                {
                    islands++;

                    if (row+1 < ROWS && grid[row+1][col] == '1')
                    {
                        pair<int,int> node_1 = make_pair(row  , col  );
                        pair<int,int> node_2 = make_pair(row+1, col  );

                        if (dsu.union_components(node_1, node_2)) // If Merged
                            islands--;
                    }

                    if (col+1 < COLS && grid[row][col+1] == '1')
                    {
                        pair<int,int> node_1 = make_pair(row  , col  );
                        pair<int,int> node_2 = make_pair(row  , col+1);

                        if (dsu.union_components(node_1, node_2)) // If Merged
                            islands--;
                    }
                }
            }
        }

        return islands;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    An optimal way of writing DSU for a 2D vector.

*/

/* Time  Beats: 83.73% */
/* Space Beats: 35.74% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
struct DSU {
    vector<int> rank;
    vector<int> parent;

    DSU (const int& ROWS, const int& COLS)
    {
        rank.resize(ROWS * COLS, 1);

        parent.resize(ROWS * COLS);
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
                parent[row * COLS + col] = row * COLS + col;
        }
    }

    int find_root_node(int node)
    {
        while (node != parent[node])
        {
            /* Reverse Ackerman function */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2)
    {
        int root_1 = find_root_node(node_1);
        int root_2 = find_root_node(node_2);

        if (root_1 == root_2)
            return false;

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        // Make sure that to merge TOWARDS the smaller node, i.e. root "a"
        parent[root_2] = root_1;       // Merge Roots

        rank[root_1]  += rank[root_2]; // Increase the component size of root_1

        return true;
    }
};

class Solution_DSU {
public:
    int numIslands(vector<vector<char>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();
        int islands = 0;

        DSU dsu(ROWS, COLS);

        /* Lambda */
        auto index = [COLS](int row, int col) { return row * COLS + col; };

        /* Union Components */
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (grid[row][col] == '1')
                {
                    islands++;

                    if (row+1 < ROWS && grid[row+1][col] == '1')
                    {
                        int node_1 = index(row  , col  );
                        int node_2 = index(row+1, col  );

                        if (dsu.union_components(node_1, node_2)) // If Merged
                            islands--;
                    }

                    if (col+1 < COLS && grid[row][col+1] == '1')
                    {
                        int node_1 = index(row  , col  );
                        int node_2 = index(row  , col+1);

                        if (dsu.union_components(node_1, node_2)) // If Merged
                            islands--;
                    }
                }
            }
        }

        return islands;
    }
};
