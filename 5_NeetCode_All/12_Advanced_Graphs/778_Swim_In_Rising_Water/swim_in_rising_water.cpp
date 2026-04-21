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

#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 10.50% */
/* Space Beats: 10.63% */

/* Time  Complexity: O(N^2 * logN) */
/* Space Complexity: O(N^2) */
class Solution_Dijkstra {
public:
    int swimInWater(vector<vector<int>>& grid)
    {
        const int N = grid.size();

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;
        min_heap.push( {grid[0][0], 0, 0} );

        vector<vector<bool>> visited(N, vector<bool>(N, false));
        vector<pair<int,int>> directions = { {-1,0}, {1,0}, {0,-1}, {0,1} };

        /* Dijkstra-like */
        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            int min_height_so_far = top[0];
            int row               = top[1];
            int col               = top[2];

            if (visited[row][col])
                continue;

            if (row == N-1 && col == N-1)
                return min_height_so_far;

            visited[row][col] = true;

            for (const auto& dir: directions)
            {
                int new_row = row + dir.first;
                int new_col = col + dir.second;

                if (new_row < 0 || new_col < 0 || new_row >= N || new_col >= N)
                    continue;

                if (visited[new_row][new_col])
                    continue;

                int new_min_height = max(min_height_so_far, grid[new_row][new_col]);
                min_heap.push( {new_min_height, new_row, new_col} );
            }
        }

        return 0; // Unreachable
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Essentially what they are asking us to do is find a:

        MST - Minimum Spanning Tree

    There is an Algorithm for finding MST---Kruskal's Algorithm.

*/

/* Time  Beats: 79.52% */
/* Space Beats: 73.64% */

/* Time  Complexity: O(N^2 * logN) */
/* Space Complexity: O(N^2)        */
class DSU {
private:
    vector<int> rank;
    vector<int> parent;

public:
    DSU (int n)
    {
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
            return false; // We have NOT done a UNION

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        return true; // We have INDEED performed a UNION
    }

    bool connected(int node_1, int node_2)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        return root_1 == root_2;
    }
};

class Solution_Kruskal {
public:
    int swimInWater(vector<vector<int>>& grid)
    {
        const int N = grid.size();

        DSU dsu(N * N);

        vector<pair<int,int>> directions = { {-1,0}, {1,0}, {0,-1}, {0,1} };

        vector<tuple<int,int,int>> positions;
        positions.reserve(N*N);

        /* 1D flattening techniqeu */
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                positions.push_back( {grid[row][col], row, col} );
            }
        }

        /* Sort */
        sort(positions.begin(), positions.end()); // TC: O(N^2 * logN)

        /* Lambda */
        auto index = [&](int row, int col) -> int {
            return row * N + col;
        };

        int starting_position = index(0  , 0  );
        int ending_position   = index(N-1, N-1);

        /* Kruskal's Algorithm: Creation of Minimum-Spanning-Tree */
        for (const auto& [min_height_so_far, row, col] : positions)
        {
            for (const auto& dir : directions)
            {
                int new_row = row + dir.first;
                int new_col = col + dir.second;

                if (new_row < 0 || new_col < 0 || new_row >= N || new_col >= N)
                    continue;

                if (grid[new_row][new_col] > min_height_so_far)
                    continue;

                dsu.union_components(index(row    , col    ),
                                     index(new_row, new_col));
            }

            if (dsu.connected(starting_position, ending_position))
                return min_height_so_far;
        }

        return 0; // Unreachable
    }
};
