/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    1631) Path With Minimum Effort
    ==============================

    ============
    Description:
    ============

    You are a hiker preparing for an upcoming hike. You are given heights, a 2D
    array of size rows x columns, where heights[row][col] represents the height
    of cell (row, col). You are situated in the top-left cell, (0, 0), and you
    hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e.,
    0-indexed). You can move up, down, left, or right, and you wish to find a
    route that requires the minimum effort.

    A route's effort is the maximum absolute difference in heights between two
    consecutive cells of the route.

    Return the minimum effort required to travel from the top-left cell to the
    bottom-right cell.

    ==============================================================
    FUNCTION: int minimumEffortPath(vector<vector<int>>& heights);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---

        +-----+-----+-----+
        |  1  |  2  |  2  |
        +-----+-----+-----+
        |  3  |  8  |  2  |
        +-----+-----+-----+
        |  5  |  3  |  5  |
        +-----+-----+-----+

    Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
    Output: 2
    Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of
    2 in consecutive cells.  This is better than the route of [1,2,2,2,5],
    where the maximum absolute difference is 3.



    --- Example 2 ---

        +-----+-----+-----+
        |  1  |  2  |  3  |
        +-----+-----+-----+
        |  3  |  8  |  4  |
        +-----+-----+-----+
        |  5  |  3  |  5  |
        +-----+-----+-----+

    Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
    Output: 1
    Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of
    1 in consecutive cells, which is better than route [1,3,5,3,5].


    --- Example 3 ---

        +-----+-----+-----+-----+-----+
        |  1  |  2  |  1  |  1  |  1  |
        +-----+-----+-----+-----+-----+
        |  1  |  2  |  1  |  2  |  1  |
        +-----+-----+-----+-----+-----+
        |  1  |  2  |  1  |  2  |  1  |
        +-----+-----+-----+-----+-----+
        |  1  |  2  |  1  |  2  |  1  |
        +-----+-----+-----+-----+-----+
        |  1  |  1  |  1  |  3  |  1  |
        +-----+-----+-----+-----+-----+

    Input: heights =
    [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
    Output: 0
    Explanation: This route does not require any effort.




    *** Constraints ***
    rows == heights.length
    columns == heights[i].length
    1 <= rows, columns <= 100
    1 <= heights[i][j] <= 10^6

*/

#include <vector>
#include <queue>
#include <bits/stdc++.h>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (DIjkstra on a 2D Grid)

*/

/* Time  Beats:  8.52% */
/* Space Beats: 11.42% */

/* Time  Complexity: O((ROWS * COLS) * log(ROWS * COLS)) */
/* Space Complexity: O((ROWS * COLS)                   ) */
class Solution_Dijkstra {
public:
    int minimumEffortPath(vector<vector<int>>& heights)
    {
        const int ROWS = heights.size();
        const int COLS = heights[0].size();

        // min-Heap: {abs_diff, row, col}
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;
        min_heap.push( {0, 0, 0} );

        // 1D flattening technique
        bool visited[10001] = {false};

        /* Signing Cross */
        vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        /* Dijkstra's Algorithm */
        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            int min_effort_to_here = top[0];
            int row                = top[1];
            int col                = top[2];

            if (visited[row * COLS + col])
                continue; // We've already been here with some SMALLER effort

            visited[row * COLS + col] = true;

            // If we've reached the bottom-right cell
            if (row == ROWS-1 && col == COLS-1)
                return min_effort_to_here;

            /* Signign Cross directions: Up, Down, Left, Right */
            for (const auto& dir : directions)
            {
                int new_row = row + dir.first;
                int new_col = col + dir.second;

                /* Out-of-Bounds */
                if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                    continue;

                /* Already processed */
                if (visited[new_row * COLS + new_col])
                    continue;

                int next_abs_diff  = abs(heights[row][col] - heights[new_row][new_col]);
                int new_min_effort = max(min_effort_to_here, next_abs_diff);

                min_heap.push( {new_min_effort, new_row, new_col} );
            }
        }

        return 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 5.00% */
/* Space Beats: 5.05% */

/* Time  Complexity: O(ROWS * COLS * log(MAX_HEIGHT)) */
/* Space Complexity: O(ROWS * COLS)                   */
class Solution_Binary_Search_and_DFS {
public:
    int minimumEffortPath(vector<vector<int>>& heights)
    {
        const int ROWS = heights.size();
        const int COLS = heights[0].size();
        const int MAX_HEIGHT = 1e6;

        bool visited[10001] = {false};

        int low  = 0;
        int high = MAX_HEIGHT;

        while (low < high)
        {
            int mid = low + (high - low) / 2; // Left-leaning mid

            memset(visited, false, sizeof(visited));

            if ( ! dfs_reached_last_cell(0, 0, mid, visited, heights))
                low = mid + 1;
            else
                high = mid;
        }

        return low;
    }

private:
    bool dfs_reached_last_cell(int row, int col, int limit, bool (& visited)[10001], vector<vector<int>>& heights)
    {
        const int ROWS = heights.size();
        const int COLS = heights[0].size();

        if (row == ROWS-1 && col == COLS-1)
            return true;

        visited[row * COLS + col] = true;

        vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};
        for (const auto& dir : directions)
        {
            int new_row = row + dir.first;
            int new_col = col + dir.second;

            if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                continue;

            if (visited[new_row * COLS + new_col])
                continue;

            int next_abs_diff = abs(heights[new_row][new_col] - heights[row][col]);
            if (next_abs_diff > limit)
                continue;

            if (dfs_reached_last_cell(new_row, new_col, limit, visited, heights))
                return true;
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 7.18% */
/* Space Beats: 5.03% */

/* Time  Complexity: O(E * logE) */ // Where E is the total amount of EDGES
/* Space Complexity: O(E + V)    */ // Where V is the total amount of VERTICES
class DSU {
private:
    vector<int> rank;
    vector<int> parent;
    vector<int> max_weight;

public:
    DSU (int N)
    {
        rank.resize(N);
        parent.resize(N);

        max_weight.resize(N);

        for (int i = 0; i < N; i++)
        {
            rank[i]   = 1;
            parent[i] = i;

            max_weight[i] = 0;
        }
    }

    int find_root(int node)
    {
        while (node != parent[node])
        {
            /* Reverse Ackerman function */
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node_1, int node_2, int diff)
    {
        int root_1 = find_root(node_1);
        int root_2 = find_root(node_2);

        if (root_1 == root_2)
            return false; // Already the same component

        if (rank[root_1] < rank[root_2])
            swap(root_1, root_2);

        parent[root_2] = root_1;
        rank[root_1]  += rank[root_2];

        max_weight[root_1] = max( {max_weight[root_1], max_weight[root_2], diff} );

        return true;
    }

    int get_max_weight(int node_1)
    {
        int root_1 = find_root(node_1);

        return max_weight[root_1];
    }
};

class Solution_Kruskal_Algorithm {
public:
    int minimumEffortPath(vector<vector<int>>& heights)
    {
        const int ROWS = heights.size();
        const int COLS = heights[0].size();

        DSU dsu(ROWS * COLS);

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> min_heap;

        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (col+1 < COLS) // Right
                {
                    int right = abs(heights[row  ][col+1] - heights[row][col]);
                    min_heap.push( {right, row, col, row,   col+1} );
                }

                if (row+1 < ROWS) // Down
                {
                    int down  = abs(heights[row+1][col  ] - heights[row][col]);
                    min_heap.push( {down , row, col, row+1, col  } );
                }
            }
        }

        /* Kruskal's Algorithm */
        while ( ! min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            int diff  = top[0];

            int u_row = top[1];
            int u_col = top[2];

            int v_row = top[3];
            int v_col = top[4];

            /* 1D Flatteninc technique */
            int node_1 = u_row * COLS + u_col;
            int node_2 = v_row * COLS + v_col;

            /* Potential Union */
            dsu.union_components(node_1, node_2, diff);


            /* Check if the Starting and Goal node are connected now */
            int start_node = 0        * COLS + 0;
            int goal_node  = (ROWS-1) * COLS + (COLS-1);

            int start_root = dsu.find_root(start_node);
            int goal_root = dsu.find_root(goal_node);

            if (start_root == goal_root)
                return dsu.get_max_weight(start_root);
        }

        return 0; // Unreachable
    }
};
