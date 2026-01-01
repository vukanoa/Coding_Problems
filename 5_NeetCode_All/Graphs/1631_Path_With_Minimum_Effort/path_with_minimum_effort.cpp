#include <iostream>
#include <vector>
#include <queue>
#include <climits>

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

/*
    ------------
    --- IDEA ---
    ------------

    BST with Priorities ==> A variation of Dijkstra.

*/

/* Time  Beats: 10.36% */
/* Space Beats: 15.84% */

/* Time  Complexity: O((M * N)^2 * log(M * N)) */
/* Space Complexity: O((M * N))                */
class Solution {
public:
    int minimumEffortPath(std::vector<std::vector<int>>& heights)
    {
        const int ROWS = heights.size();
        const int COLS = heights[0].size();

        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> min_heap;
        min_heap.push({0, 0, 0}); // [diff, row, col]

        std::vector<std::vector<bool>> visited(ROWS, std::vector<bool>(COLS, false));

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            int diff = top[0];
            int row  = top[1];
            int col  = top[2];

            if (visited[row][col])
                continue;

            visited[row][col] = true;

            if (row == ROWS-1 && col == COLS-1)
                return diff;

            for (auto& dir : directions)
            {
                int neighbor_row = row + dir.first;
                int neighbor_col = col + dir.second;

                if (neighbor_row < 0 || neighbor_row == ROWS ||
                    neighbor_col < 0 || neighbor_col == COLS ||
                    visited[neighbor_row][neighbor_col])
                {
                    continue;
                }

                int abs_diff = std::abs(heights[row][col] - heights[neighbor_row][neighbor_col]);
                int new_diff = std::max(diff, abs_diff);

                min_heap.push({new_diff, neighbor_row, neighbor_col});
            }
        }

        return 0;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    I have no idea why, but it turns out that using pair of pairs is faster
    than using a vector inside a priority queue.

    It makes a huge difference. If you don't believe, feel free to exchange
    this:

        std::priority_queue<std::pair<int, std::pair<int, int>>,
                            std::vector<std::pair<int, std::pair<int, int>>>,
                            std::greater<pair<int, pair<int, int>>>> min_heap;

    with this:
        std::priority_queue<std::vector<int>,
                            std::vector<std::vector<int>>,
                            std::greater<std::vector<int>>> min_heap;

    And of course, these:
        Line 224: min_heap.push({0, {0, 0}});
        Line 257: min_heap.push({new_diff, {neighbor_row, neighbor_col}});

    with these:
        Line 224: min_heap.push({0, 0, 0}); // [diff, row, col]
        Line 257: min_heap.push({new_diff, neighbor_row, neighbor_col});

*/

/* Time  Beats: 93.28% */
/* Space Beats: 65.53% */

/* Time  Complexity: O((M * N)^2 * log(M * N)) */
/* Space Complexity: O((M * N))                */
class Solution_Efficient_Implementation {
public:
    int minimumEffortPath(vector<vector<int>>& heights)
    {
        std::priority_queue<std::pair<int, std::pair<int, int>>,
                            std::vector<std::pair<int, std::pair<int, int>>>,
                            std::greater<pair<int, pair<int, int>>>> min_heap;

        int ROWS = heights.size();
        int COLS = heights[0].size();

        std::vector<std::vector<int>> distance(ROWS, std::vector<int>(COLS, INT_MAX));

        distance[0][0] = 0;
        min_heap.push({0, {0, 0}});

        std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        while (!min_heap.empty())
        {
            auto top = min_heap.top();
            min_heap.pop();

            int diff = top.first;
            int row  = top.second.first;
            int col  = top.second.second;

            if (row == ROWS-1 && col == COLS-1)
                return diff;

            for (auto& dir : directions)
            {
                int neighbor_row = row + dir.first;
                int neighbor_col = col + dir.second;

                if (neighbor_row < 0 || neighbor_row == ROWS ||
                    neighbor_col < 0 || neighbor_col == COLS)
                {
                    continue;
                }

                int abs_diff = std::abs(heights[row][col] - heights[neighbor_row][neighbor_col]);
                int new_diff = std::max(diff, abs_diff);

                if (new_diff < distance[neighbor_row][neighbor_col])
                {
                    distance[neighbor_row][neighbor_col] = new_diff;
                    min_heap.push({new_diff, {neighbor_row, neighbor_col}});
                }
            }
        }

        return 0;
    }
};
