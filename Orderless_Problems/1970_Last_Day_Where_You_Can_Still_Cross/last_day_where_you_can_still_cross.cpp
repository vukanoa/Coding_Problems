/*
    ============
    === HARD ===
    ============

    ========================================
    1970) Last Day Where You Can Still Cross
    ========================================

    ============
    Description:
    ============

    There is a 1-based binary matrix where 0 represents land and 1 represents
    water. You are given integers row and col representing the number of rows
    and columns in the matrix, respectively.

    Initially on day 0, the entire matrix is land. However, each day a new cell
    becomes flooded with water. You are given a 1-based 2D array cells, where
    cells[i] = [ri, ci] represents that on the ith day, the cell on the rith
    row and cith column (1-based coordinates) will be covered with water (i.e.,
    changed to 1).

    You want to find the last day that it is possible to walk from the top to
    the bottom by only walking on land cells. You can start from any cell in
    the top row and end at any cell in the bottom row. You can only travel in
    the four cardinal directions (left, right, up, and down).

    Return the last day where it is possible to walk from the top to the bottom
    by only walking on land cells.

    =============================================================================
    FUNCTION: int latestDayToCross(int row, int col, vector<vector<int>>& cells);
    =============================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: row = 2, col = 2, cells = [[1,1],[2,1],[1,2],[2,2]]
    Output: 2
    Explanation: The above image depicts how the matrix changes each day starting from day 0.
    The last day where it is possible to cross from top to bottom is on day 2.

    --- Example 2 ---
    Input: row = 2, col = 2, cells = [[1,1],[1,2],[2,1],[2,2]]
    Output: 1
    Explanation: The above image depicts how the matrix changes each day starting from day 0.
    The last day where it is possible to cross from top to bottom is on day 1.

    --- Example 3 ---
    Input: row = 3, col = 3, cells = [[1,2],[2,1],[3,3],[2,2],[1,1],[1,3],[2,3],[3,2],[3,1]]
    Output: 3
    Explanation: The above image depicts how the matrix changes each day starting from day 0.
    The last day where it is possible to cross from top to bottom is on day 3.


    *** Constraints ***
    2 <= row, col <= 2 * 10^4
    4 <= row * col <= 2 * 10^4
    cells.length == row * col
    1 <= ri <= row
    1 <= ci <= col
    All the values of cells are unique.

*/

#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 97.38% */
/* Space Beats: 95.29% */

/* Time  Complexity: O(row * col) */
/* Space Complexity: O(row * col) */
class DSU {
public:
    vector<int> rank;
    vector<int> parent;

    DSU(int n)
    {
        rank.assign(n, 1);

        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        // iota(parent.begin(), parent.end(), 1);
    }

    int find_root_node(int node)
    {
        // Get root parent
        while (node != parent[node])
        {
            // Huge Optimization (From O(n) to Amortized O(1) Time Complexity)
            // If there is no grandparent, nothing will happen
            parent[node] = parent[parent[node]];

            node = parent[node];
        }

        return node;
    }

    bool union_components(int node1, int node2)
    {
        int root1 = find_root_node(node1);
        int root2 = find_root_node(node2);

        if (root1 == root2)
            return false;

        if (rank[root1] < rank[root2])
            swap(root1, root2);

        // Make sure that to merge TOWARDS the smaller node, i.e. root1
        parent[root2] = root1;
        rank[root1] += rank[root2];

        return true;
    }
};

class Solution {
public:
    int latestDayToCross(int row, int col, vector<vector<int>>& cells)
    {
        DSU dsu(row * col + 2);

        vector<vector<int>> grid(row, vector<int>(col, 0));

        int directions[8][2] =
        {
            {  0,  1}, {  0, -1},
            {  1,  0}, { -1,  0},
            {  1,  1}, {  1, -1},
            { -1,  1}, { -1, -1}
        };

        int left_virtual_node  = 0;
        int right_virtual_node = row * col + 1;

        for (int day = 0; day < row * col; day++)
        {
            int curr_row = cells[day][0] - 1;
            int curr_col = cells[day][1] - 1;

            grid[curr_row][curr_col] = 1;

            int curr_cell_id = curr_row * col + curr_col + 1;

            for (auto& dir : directions)
            {
                int new_row = curr_row + dir[0];
                int new_col = curr_col + dir[1];

                if (new_row >= 0 && new_row < row &&
                    new_col >= 0 && new_col < col &&
                    grid[new_row][new_col] == 1)
                {
                    int neighbor_cell_id = new_row * col + new_col + 1;

                    dsu.union_components(curr_cell_id, neighbor_cell_id);
                }
            }

            if (curr_col == 0)
                dsu.union_components(left_virtual_node, curr_cell_id);

            if (curr_col == col - 1)
                dsu.union_components(right_virtual_node, curr_cell_id);

            if (dsu.find_root_node(left_virtual_node) == dsu.find_root_node(right_virtual_node))
                return day;
        }

        return -1;
    }
};
