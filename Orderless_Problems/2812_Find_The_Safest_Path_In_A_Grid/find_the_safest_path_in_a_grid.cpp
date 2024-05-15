#include <iostream>
#include <vector>
#include <queue>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    2812) Find the Safest Path in a Grid
    ====================================

    ============
    Description:
    ============

    You are given a 0-indexed 2D matrix grid of size n x n, where (r, c)
    represents:

        + A cell containing a thief if grid[r][c] = 1
        + An empty cell if grid[r][c] = 0

    You are initially positioned at cell (0, 0). In one move, you can move to
    any adjacent cell in the grid, including cells containing thieves.

    The safeness factor of a path on the grid is defined as the minimum
    manhattan distance from any cell in the path to any thief in the grid.

    Return the maximum safeness factor of all paths leading to cell (n - 1, n -
    1).

    An adjacent cell of cell (r, c), is one of the cells (r, c + 1), (r, c -
    1), (r + 1, c) and (r - 1, c) if it exists.

    The Manhattan distance between two cells (a, b) and (x, y) is equal to |a -
    x| + |b - y|, where |val| denotes the absolute value of val.

    ===============================================================
    FUNCTION: int maximumSafenessFactor(vector<vector<int>>& grid);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
                +-----+-----+-----+
                |  1  |  0  |  0  |
                +-----+-----+-----+
                |  0  |  0  |  0  |
                +-----+-----+-----+
                |  0  |  0  |  1  |
                +-----+-----+-----+
    Input: grid = [[1,0,0],[0,0,0],[0,0,1]]
    Output: 0
    Explanation: All paths from (0, 0) to (n - 1, n - 1) go through the thieves
                 in cells (0, 0) and (n - 1, n - 1).


    --- Example 2 ---
                +-----+-----+-----+
                |  0# |  0  |  1  |
                +-----+-----+-----+
                |  0# |  0  |  0  |      // #'s are a highlighted path
                +-----+-----+-----+
                |  0# |  0# |  0# |
                +-----+-----+-----+
    Input: grid = [[0,0,1],[0,0,0],[0,0,0]]
    Output: 2
    Explanation: The path depicted in the picture above has a safeness factor
                 of 2 since:
    - The closest cell of the path to the thief at cell (0, 2) is cell (0, 0).
      The distance between them is | 0 - 0 | + | 0 - 2 | = 2.  It can be shown
      that there are no other paths with a higher safeness factor.


    --- Example 3 ---
                +-----+-----+-----+-----+
                |  0# |  0# |  0  |  1  |
                +-----+-----+-----+-----+
                |  0  |  0# |  0# |  0  |      // #'s are a highlighted path
                +-----+-----+-----+-----+
                |  0  |  0  |  0# |  0  |
                +-----+-----+-----+-----+
                |  1  |  0  |  0# |  0# |
                +-----+-----+-----+-----+


    Input: grid = [[0,0,0,1],[0,0,0,0],[0,0,0,0],[1,0,0,0]]
    Output: 2
    Explanation: The path depicted in the picture above has a safeness factor
    of 2 since:
    - The closest cell of the path to the thief at cell (0, 3) is cell (1, 2).
      The distance between them is | 0 - 1 | + | 3 - 2 | = 2.
    - The closest cell of the path to the thief at cell (3, 0) is cell (3, 2).
      The distance between them is | 3 - 3 | + | 0 - 2 | = 2.
    It can be shown that there are no other paths with a higher safeness factor


    *** Constraints ***
    1 <= grid.length == n <= 400
    grid[i].length == n
    grid[i][j] is either 0 or 1.
    There is at least one thief in the grid.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Intuition

    1. Precompute distances to thieves using BFS, then
    2. Find the maximum safeness factor (minimum distance to any thief) along
       any path from (0, 0) to (n-1, n-1) using Dijkstra's algorithm.


    Approach: BFS + Dijkstra Algorithm
    Here's how the approach works:

        1. Precompute Distances: We perform a BFS from all cells containing
           thieves to compute the minimum distance from each cell to the
           nearest thief. Store these distances in safe_scores. (2D vector)

        2. Maximize "Minimum" Distance: Then, to find the maximum safeness
           factor (minimum distance to any thief) along a path from (0, 0) to
           (n-1, n-1), model it as a shortest path problem with the objective
           of maximizing the minimum distance along the path.

        3. Dijkstra's Algorithm: We then use Dijkstra's algorithm with a
           priority queue, where the priority is the safeness factor (minimum
           distance to any thief). We start from (0, 0) with its safeness
           factor safe_scores[0][0].

        4. Priority Queue Traversal: Then, at each step, we dequeue the cell
           with the maximum safeness factor. If it's (n-1, n-1), we return the
           safeness factor. Otherwise, we enqueue its unvisited neighbors with
           the minimum of the current safeness factor and the neighbor's
           safeness factor safe_scores[x][y].

        Pruning: We use a separate 2D boolean vector "visited" to mark visited
        cells and avoid revisiting them.

        Boundary Cases: If (0, 0) or (n-1, n-1) contains a thief, return 0 as
        the maximum safeness factor, because we have to start from (0, 0) and
        end at (n-1, n-1).

    The combination of BFS preprocessing, Dijkstra's algorithm with a priority
    queue, and proper handling of boundary cases and visited cells provides an
    efficient solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  92.01% */

/* Time  Complexity: O(n^2 * logn) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int maximumSafenessFactor(std::vector<std::vector<int>>& grid)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        const int N = grid.size();

        // Base case
        if (grid[0][0] == 1 || grid[N-1][N-1] == 1)
            return 0;

        std::vector<std::vector<int>> safe_scores(N, std::vector<int>(N, INT_MAX));
        /* BFS */
        bfs(grid, safe_scores);

        /* Dijkstra's Algorithm */
        std::priority_queue<std::pair<int, std::pair<int, int>>> max_heap;
        max_heap.push( {safe_scores[0][0], {0,0}} );

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        std::vector<std::vector<bool>> visited(N, std::vector<bool>(N, false));
        while (!max_heap.empty())
        {
            int safe   = max_heap.top().first;
            int curr_x = max_heap.top().second.first;
            int curr_y = max_heap.top().second.second;
            max_heap.pop();

            if (curr_x == N-1 && curr_y == N-1)
                return safe;

            for (const auto& dir : directions)
            {
                int x = curr_x + dir.first;
                int y = curr_y + dir.second;

                if (x < 0 || y < 0 || x == N || y == N || visited[x][y])
                    continue;

                int score = std::min(safe, safe_scores[x][y]);
                max_heap.push( {score, {x, y}} );
                visited[x][y] = true;
            }
        }

        return -1; // This will never be returned
    }

private:
    void bfs(std::vector<std::vector<int>>& grid, std::vector<std::vector<int>>& safe_scores)
    {
        const int N = grid.size();
        std::queue<std::pair<int, int>> queue;

        /* Initialize the queue with thieves */
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (grid[i][j] == 1) // Thief
                {
                    safe_scores[i][j] = 0;
                    queue.push( {i, j} );
                }
            }
        }

        /* Signing Cross */
        std::vector<std::pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

        /* BFS */
        while (!queue.empty())
        {
            std::pair<int, int> pair = queue.front();
            queue.pop();

            int curr_score = safe_scores[pair.first][pair.second];

            for (const auto& dir : directions)
            {
                int x = pair.first  + dir.first;
                int y = pair.second + dir.second;

                if (x < 0 || y < 0 || x == N || y == N || safe_scores[x][y] <= curr_score + 1)
                    continue;

                safe_scores[x][y] = curr_score + 1;
                queue.push( {x, y} );
            }
        }
    }
};
