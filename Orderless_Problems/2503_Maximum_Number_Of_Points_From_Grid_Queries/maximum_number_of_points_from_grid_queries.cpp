/*
    ============
    === HARD ===
    ============

    ================================================
    2503) Maximum Number of Points From Grid Queries
    ================================================

    ============
    Description:
    ============

    You are given an m x n integer matrix grid and an array queries of size k.

    Find an array answer of size k such that for each integer queries[i] you
    start in the top left cell of the matrix and repeat the following process:

        + If queries[i] is strictly greater than the value of the current cell
          that you are in, then you get one point if it is your first time
          visiting this cell, and you can move to any adjacent cell in all 4
          directions: up, down, left, and right.

        + Otherwise, you do not get any points, and you end this process.

    After the process, answer[i] is the maximum number of points you can get.

    Note that for each query you are allowed to visit the same cell multiple
    times.

    Return the resulting array answer.

    =================================================================================
    FUNCTION: vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries);
    =================================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
    Output: [5,8,1]
    Explanation: The diagrams above show which cells we visit to get points for
                 each query.

    --- Example 2 ---
    Input: grid = [[5,2,1],[1,1,2]], queries = [3]
    Output: [0]
    Explanation: We can not get any points because the value of the top left
                 cell is already greater than or equal to 3.


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    2 <= m, n <= 1000
    4 <= m * n <= 10^5
    k == queries.length
    1 <= k <= 10^4
    1 <= grid[i][j], queries[i] <= 10^6

*/

#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    By-the-book Dijkstra applied on a "Grid traversal" problem.

*/

/* Time  Beats: 72.46% */
/* Space Beats: 81.16% */

/* Time  Complexity: O(K * logK + (ROWS * COLS) * log(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COLS + K)                             */
class Solution_Dijkstra_Grid_Traversal {
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        const int K = queries.size();
        vector<int> answer(K, 0);

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        vector<pair<int, int>> sorted_queries;
        for (int i = 0; i < queries.size(); i++)
            sorted_queries.push_back( {queries[i], i} );

        /* Sort */
        sort(sorted_queries.begin(), sorted_queries.end());

        priority_queue<pair<int, pair<int, int>>,
                       vector<pair<int, pair<int, int>>>,
                       greater<>> min_heap;

        vector<vector<bool>> visited(ROWS, vector<bool>(COLS, false));

        // Start from the top-left cell
        min_heap.push({grid[0][0], {0, 0}});
        visited[0][0] = true;

        int total_points = 0;

        for (const auto& [query_val, query_idx] : sorted_queries)
        {
            // Expand the cells that are smaller than the current query value
            while ( ! min_heap.empty() && min_heap.top().first < query_val)
            {
                auto [cell_value, position] = min_heap.top();
                min_heap.pop();

                int curr_row = position.first;
                int curr_col = position.second;

                total_points++;

                // Explore all four possible directions
                for (const auto& dir : directions)
                {
                    int new_row = curr_row + dir.first;
                    int new_col = curr_col + dir.second;

                    if (new_row < 0 || new_col < 0 || new_row == ROWS || new_col == COLS)
                        continue;

                    if (visited[new_row][new_col])
                        continue;

                    min_heap.push( {grid[new_row][new_col], {new_row, new_col}} );
                    visited[new_row][new_col] = true;
                }
            }

            answer[query_idx] = total_points;
        }

        return answer;
    }
};
