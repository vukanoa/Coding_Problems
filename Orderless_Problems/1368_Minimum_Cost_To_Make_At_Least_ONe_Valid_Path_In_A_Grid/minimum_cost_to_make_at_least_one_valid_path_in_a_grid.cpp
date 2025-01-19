/*
    ============
    === HARD ===
    ============

    ============================================================
    1368) Minimum Cost to Make at Least One Valid Path in a Grid
    ============================================================

    ============
    Description:
    ============

    Given an m x n grid. Each cell of the grid has a sign pointing to the next
    cell you should visit if you are currently in this cell. The sign of
    grid[i][j] can be:

        1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
        2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
        3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
        4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])

    Notice that there could be some signs on the cells of the grid that point
    outside the grid.

    You will initially start at the upper left cell (0, 0). A valid path in the
    grid is a path that starts from the upper left cell (0, 0) and ends at the
    bottom-right cell (m - 1, n - 1) following the signs on the grid. The valid
    path does not have to be the shortest.

    You can modify the sign on a cell with cost = 1. You can modify the sign on
    a cell one time only.

    Return the minimum cost to make the grid have at least one valid path.

    =================================================
    FUNCTION: int minCost(vector<vector<int>>& grid);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
    Output: 3
    Explanation: You will start at point (0, 0).
    The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) change the arrow to down with cost = 1 --> (3, 3)
    The total cost = 3.


    --- Example 2 ---
    Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
    Output: 0
    Explanation: You can follow the path from (0, 0) to (2, 2).


    --- Example 3 ---
    Input: grid = [[1,2],[4,3]]
    Output: 1


    *** Constraints ***
    m == grid.length
    n == grid[i].length
    1 <= m, n <= 100
    1 <= grid[i][j] <= 4

*/

#include <climits>
#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 39.24% */
/* Space Beats: 30.10% */

/* Time  Complexity: O((ROWS * COLS)^2) */
/* Space Complexity: O(ROWS * COLS)     */
class Solution {
public:
    int minCost(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        vector<vector<int>> dp(ROWS, vector<int>(COLS, INT_MAX));
        dp[0][0] = 0;

        while (true)
        {
            // Store previous state to check for convergence
            vector<vector<int>> prev_state = dp;

            // Forward pass: check cells coming from left and top
            for (int row = 0; row < ROWS; row++)
            {
                for (int col = 0; col < COLS; col++)
                {
                    // Check cell above
                    if (row > 0)
                    {
                        dp[row][col] = min(dp[row][col],
                                           dp[row-1][col] + (grid[row-1][col] == 3 ? 0 : 1));
                    }

                    // Check cell to the left
                    if (col > 0)
                    {
                        dp[row][col] = min(dp[row][col],
                                           dp[row][col-1] + (grid[row][col-1] == 1 ? 0 : 1));
                    }
                }
            }

            // Backward pass: check cells coming from right and bottom
            for (int row = ROWS-1; row >= 0; row--)
            {
                for (int col = COLS-1; col >= 0; col--)
                {
                    // Check cell below
                    if (row < ROWS-1)
                    {
                        dp[row][col] = min(dp[row][col],
                                           dp[row+1][col] + (grid[row+1][col] == 4 ? 0 : 1));
                    }

                    // Check cell to the right
                    if (col < COLS-1)
                    {
                        dp[row][col] = min(dp[row][col],
                                           dp[row][col+1] + (grid[row][col+1] == 2 ? 0 : 1));
                    }
                }
            }

            // If no changes were made in this iteration, we've found optimal
            // solution
            if (prev_state == dp)
                break;
        }

        return dp[ROWS-1][COLS-1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 24.33% */
/* Space Beats: 23.91% */

/* Time  Complexity: O(ROWS * COLS * log(ROWS * COLS)) */
/* Space Complexity: O(ROWS * COLS)                    */
class Solution_Dijkstra {
public:
    int minCost(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        // Min-heap ordered by cost. Each element is {cost, row, col}
        priority_queue<vector<int>, vector<vector<int>>, greater<>> min_heap;
        min_heap.push({0, 0, 0});

        // Track minimum cost to reach each cell
        vector<vector<int>> min_cost(ROWS, vector<int>(COLS, INT_MAX));
        min_cost[0][0] = 0;

        // Direction vectors: right, left, down, up (matching grid values 1, 2, 3, 4)
        vector<pair<int,int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        const int DIRECTIONS = 4;


        while ( ! min_heap.empty())
        {
            auto curr = min_heap.top();
            min_heap.pop();

            int cost = curr[0];
            int row  = curr[1];
            int col  = curr[2];

            // Skip if we've found a better path to this cell
            if (min_cost[row][col] != cost)
                continue;

            for (int dir = 0; dir < DIRECTIONS; dir++)
            {
                int new_row = row + directions[dir].first;
                int new_col = col + directions[dir].second;

                // Check if it's Out-of-Bounds
                if (new_row < 0 || new_col <  0 || new_row == ROWS || new_col == COLS)
                    continue;

                /*
                    (dir + 1) because dir is 0-based, but actually directions
                    are 1-based

                    If ((dir + 1) == grid[row][col]) then that means the
                    previous cell, i.e. the ones we've from to this one, POINTS
                    to this current cell and in that case we do NOT need to add
                    a cost of 1 since we did NOT change the direction of the
                    arrow
                */
                int new_cost = cost + ((dir + 1) == grid[row][col] ? 0 : 1);

                // Update if we found a better path and push that cell again
                if (min_cost[new_row][new_col] > new_cost)
                {
                    min_cost[new_row][new_col] = new_cost;
                    min_heap.push( {new_cost, new_row, new_col} );
                }
            }
        }

        return min_cost[ROWS-1][COLS-1];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a famous 0-1 BFS technique. Since the cost is either 0 or 1.


    Dijkstra's algorithm is a perfect choice when we're looking for a shortest
    path, however ouw problem has a unique feature: The path costs either 0 or
    1.

    This is crucial because any path that doesn't have any "penalty", i.e. its
    entire cost is 0, is always better than the one that uses even a single
    1-cost edge.

    Therefore, it makes sense to first explore 0-cost edges. Once we're done
    processing all 0-cost edges, we can move to 1-cost edges.

    This is an algorithm called 0-1 BFS. It's a very famous technique for
    problems like these.

    In 0-1 BFS, we are using a deque, insetad of a queue. This allows us to
    prioritize 0-cost edges in a more efficient way. Each element of the deque
    will store {row, col} of a cell and we'll also have an additional min_cost
    grid to keep track of the minimum cost to reach each cell.

    Once we visit each cell, we will check its four neighboring cells' values.
    If moving to a neighbor cell doesn't require a change(,i.e. our current
    arrow points to that neighoring cell and thus its cost will be 0), we
    add tha tneighbor to the front of the deque because we first want to
    explore the ones that do NOT require any modification of arrows.

    However, if we do need to change an arrow in order to move to that neigbor
    cell, then we'll add the neighbor to the back of the deque. That way we
    are making sure it's getting explored later, after all 0-cost edges are
    done.

    For each neighbor we explore, we calculate the cost to teach that cell and
    compare it otthe current value in our helper min_cist grid. If the
    calculated cost is lower, we update min_cost to the new, cheaper, value.


    Once we're done with our BFS traversal, the minimum cost to reach the
    bottom-oright corner will be stored in min_cost. We return that as our
    final result.

*/

/* Time  Beats: 77.22% */
/* Space Beats: 36.15% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution__Zero_One_BFS {
public:
    int minCost(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        // Track minimum cost to reach each cell
        vector<vector<int>> min_cost(ROWS, vector<int>(COLS, INT_MAX));
        min_cost[0][0] = 0;

        // Use deque for 0-1 BFS - add zero cost moves to front, cost=1 to back
        deque<pair<int, int>> deque;
        deque.push_front({0, 0});

        // Direction vectors: right, left, down, up (matching grid values 1, 2, 3, 4)
        vector<pair<int,int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        const int DIRECTIONS = 4;

        while ( ! deque.empty())
        {
            auto [row, col] = deque.front();
            deque.pop_front();

            // Try all four directions
            for (int dir = 0; dir < 4; dir++)
            {
                int new_row = row + directions[dir].first;
                int new_col = col + directions[dir].second;

                /*
                    (dir + 1) because dir is 0-based, but actually directions
                    are 1-based

                    If ((dir + 1) == grid[row][col]) then that means the
                    previous cell, i.e. the ones we've from to this one, POINTS
                    to this current cell and in that case we do NOT need to add
                    a cost of 1 since we did NOT change the direction of the
                    arrow
                */
                int new_cost = ((dir + 1) == grid[row][col] ? 0 : 1);

                // Check if it's Out-of-Bounds
                if (new_row < 0     || new_col <  0    ||
                    new_row == ROWS || new_col == COLS ||
                    min_cost[row][col] + new_cost >= min_cost[new_row][new_col])
                {
                    continue;
                }

                min_cost[new_row][new_col] = new_cost + min_cost[row][col];

                // Add to the front if cost=0, or add to the back if cost=1
                if (new_cost == 0)
                    deque.push_front( {new_row, new_col} );
                else
                    deque.push_back(  {new_row, new_col} );
            }
        }

        return min_cost[ROWS - 1][COLS - 1];
    }
};

/*
    ------------
    --- IDEA ---
    ------------

    We can use the intuition of exploring all 0cost edges first and come up
    with a different approach.

    This one is a combination of a DFS and BFS.

    Since some paths cost 0 to traverse, we could explore a large portion of
    the grid without "paying" anything, i.e. with a total cost of 0.

    If we are allowed a cost of 1, we could expand from the parts of the grid
    that already have been explored and cover an even larger area. This way we
    can gradually increase the cost that we allow for exploration and thus
    cover the entire grid eventually.

    The main difference in this approach is that in the previous approaches we
    tried exploring the grid and populated the cost along the way. However,
    here we fix the cost and figure out how much can we explore the grid.

    To do that, we'll take use of both DFS and BFS.
    Imagine our exploration as having levels:

        + Cells reachable with cost 0 is one level.
        + Cells reachable with cost 1 is another level,
        + Cells reachable with cost 2 is another level, and so on
        ...

    Here's how it works:

    Starting at (0,0) we use DFS to follow the arrows without any modification.
    If a cell points to the right, then go right because that doesn't cost us
    anything, i.e. it costs 0, it's free.

    We keep following thse 0-cost edges until we can't go further. (Or if we've
    hit the bottom-right cell, then we immediately return 0)

    Think of this as drawing a continuous line through cells, following arrows
    until we have to lift our pencil up from the paper.


    Every time we reach a cell through DFs, we also add it t the queue. These
    cells will serve as the strating points for the next level of exploration.
    (This is a standard BFS behavior)

    After we're done with all 0-cost edges, we switch to BFS. We take a cell
    from the queue(as we typically do in BFS) and make modification to the
    direction, while doing that we're increasing the cost by 1. With the new
    direction of the arrow in the current cell we can now reach new cells.

    We now explore those new cells using DFS like before. As we are exploring
    the grid using DFS, we maintian a grid min_cost which holds the cost at
    which we first visited that cell(i.e. the LOWEST cost possible to reach
    that cell).

    We continue this in all directions until we're done with the current level.
    After the current level is done, we increase the cost by 1 again and start
    changing the direction arrows of cells in the queue(if there are any).

    We do this until our queue is NOT empty.

    Once we're done exploring the entire grid(or once we've hit the
    bottom-right cell) we simply return min_cost[ROWS-1][COLS-1].

*/

/* Time  Beats: 96.06% */
/* Space Beats: 56.12% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_DFS_and_BFS {
private:
    // Direction vectors: right, left, down, up (matching grid values 1,2,3,4)
    const vector<vector<int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

public:
    int minCost(vector<vector<int>>& grid)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        int cost = 0;

        // Track minimum cost to reach each cell
        vector<vector<int>> min_cost(ROWS, vector<int>(COLS, INT_MAX));

        // Queue for BFS part - stores cells that need cost increment
        queue<pair<int, int>> queue;

        // Start DFS from origin with cost 0
        dfs(grid, min_cost, queue, 0, 0, cost);

        // BFS part - process cells level by level with increasing cost
        while ( ! queue.empty())
        {
            cost++;
            int level_size = queue.size();

            for (int x = 0; x < level_size; x++)
            {
                auto [row, col] = queue.front();
                queue.pop();

                // Try all 4 directions for next level
                for (int dir = 0; dir < 4; dir++)
                {
                    dfs(grid, min_cost, queue, row + directions[dir][0], col + directions[dir][1], cost);
                }
            }
        }

        return min_cost[ROWS - 1][COLS - 1];
    }

private:
    // DFS to explore all reachable cells with current cost
    void dfs(vector<vector<int>>& grid,
             vector<vector<int>>& min_cost,
             queue<pair<int, int>>& queue,
             int row,
             int col,
             int cost)
    {
        const int ROWS = grid.size();
        const int COLS = grid[0].size();

        if (row < 0 || col < 0 || row == ROWS || col == COLS || min_cost[row][col] != INT_MAX)
            return;

        min_cost[row][col] = cost;
        queue.push({row, col});

        // Follow the arrow direction without cost increase
        int next_dir = grid[row][col] - 1;

        dfs(grid, min_cost, queue, row + directions[next_dir][0], col + directions[next_dir][1], cost);
    }
};
