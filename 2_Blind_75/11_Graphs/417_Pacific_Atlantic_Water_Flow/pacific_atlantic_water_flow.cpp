/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    417) Pacific Atlantic Water Flow
    ================================

    ============
    Description:
    ============

    There is an m x n rectangular island that borders both the Pacific Ocean
    and Atlantic Ocean. The Pacific Ocean touches the island's left and top
    edges, and the Atlantic Ocean touches the island's right and bottom edges.

    The island is partitioned into a grid of square cells. You are given an m x
    n integer matrix heights where heights[r][c] represents the height above
    sea level of the cell at coordinate (r, c).

    The island receives a lot of rain, and the rain water can flow to
    neighboring cells directly north, south, east, and west if the neighboring
    cell's height is less than or equal to the current cell's height. Water can
    flow from any cell adjacent to an ocean into the ocean.

    Return a 2D list of grid coordinates result where result[i] = [ri, ci]
    denotes that rain water can flow from cell (ri, ci) to both the Pacific and
    Atlantic oceans.

    ===========================================================================
    FUNCTION: vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights)
    ===========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---


                      Pacific ocean

             +-----+-----+-----+-----+-----+ ~~~~~
             |  1  |  2  |  2  |  3  |  5  |
             +-----+-----+-----+-----+-----+
             |  3  |  2  |  3  |  4  |  4  |
     Pacific +-----+-----+-----+-----+-----+ Atlantic
      Ocean  |  2  |  4  |  5  |  3  |  1  |  Ocean
             +-----+-----+-----+-----+-----+
             |  6  |  7  |  1  |  4  |  5  |
             +-----+-----+-----+-----+-----+
             |  5  |  1  |  1  |  2  |  4  |
       ~~~~~ +-----+-----+-----+-----+-----+

                      Atlantic Ocean

    Input: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
    Output: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]

    Explanation: The following cells can flow to the Pacific and Atlantic
                 oceans, as shown below:
    [0,4]: [0,4] -> Pacific Ocean
           [0,4] -> Atlantic Ocean
    [1,3]: [1,3] -> [0,3] -> Pacific Ocean
           [1,3] -> [1,4] -> Atlantic Ocean
    [1,4]: [1,4] -> [1,3] -> [0,3] -> Pacific Ocean
           [1,4] -> Atlantic Ocean
    [2,2]: [2,2] -> [1,2] -> [0,2] -> Pacific Ocean
           [2,2] -> [2,3] -> [2,4] -> Atlantic Ocean
    [3,0]: [3,0] -> Pacific Ocean
           [3,0] -> [4,0] -> Atlantic Ocean
    [3,1]: [3,1] -> [3,0] -> Pacific Ocean
           [3,1] -> [4,1] -> Atlantic Ocean
    [4,0]: [4,0] -> Pacific Ocean
           [4,0] -> Atlantic Ocean

    Note that there are other possible paths for these cells to flow to the
    Pacific and Atlantic oceans.








    --- Example 2 ---
    Input: heights = [[1]]
    Output: [[0,0]]
    Explanation: The water can flow from the only cell to the Pacific and
                 Atlantic oceans.








    *** Constraints ***
    m == heights.length
    n == heights[r].length
    1 <= m, n <= 200
    0 <= heights[r][c] <= 10^5

*/

#include <queue>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    If you try to do it in a naive way, you would do a simple DFS for each
    height in the matrix. However that is very inefficient.

    The Time Complexity of that approach would be:

        O((ROWS * COLS * 4^(ROWS * COLS)),

    which is unacceptable.

    Then you'd maybe think: I can **memoize** paths that I've tried and I can
    use some other matrix, say "indicators" which will have the calculated
    values in it indicating if it's possible to reach either of oceans, both or
    none.

    However that approach is almost impossible to code up. Try it yourself, I
    haven't managed to do it.

    The right way to solve this problem is to start from the Pacific ocean and
    do a DFS from 0th row and 0th column and mark all the heights that you can
    reach.

    Second, start from the Atlantic ocean and do a DFS from the last row and
    last column and mark all the heights that you can reach.

    At the end iterate through all the positions of heights and check if that
    cell is reachable from BOTH the Pacific and Atlantic oceans.

    If it is reachable from BOTH the Pacific and Atlantic oceans, simply put
    its row and col to "results" as a pair.

    *******************************
    *** Important thing to note ***
    *******************************

    We're told that if we are on some height, we can't go "up", meaning that
    the water can only flow from that point to height that is either of equal
    height or height that is lower than current height.

    However, that's if you are starting from the height and then going to the
    ocean/s.

    But in this approach, we're doing the exact opposite. We're starting from
    the Ocean/s and then doing a DFS from it, therefore we can continue in a
    certain direction if current heights is LESS THAN OR EQUAL to the one we're
    trying to go on.

    Consider te very first example:

                      0     1     2     3     4
                   +-----+-----+-----+-----+-----+
                0  |  1  |  2  |  2  |  3  |  5  |
                   +-----+-----+-----+-----+-----+
                1  |  3  |  2  |  3  |  4  |  4  |
                   +-----+-----+-----+-----+-----+
                2  |  2  |  4  |  5  |  3  |  1  |
                   +-----+-----+-----+-----+-----+
                3  |  6  |  7  |  1  |  4  |  5  |
                   +-----+-----+-----+-----+-----+
                4  |  3  |  1  |  1  |  2  |  4  |
                   +-----+-----+-----+-----+-----+

    Consider heights[2][2], which is 5. From it, we can go to the right to 3,
    then from 3 we can go to 1 and then from 1 to the Atlantic Ocean.

    We can go from 5 to 3 because 5 is GREATER THAN OR EQUAL TO 3. Similarly,
    we can go from 3 to 1 because 3 is GREATER THAN OR EQUAL TO 1. And finally
    we can go from 1 to Atlantic Ocean.

    However, since we're going in the opposite direction, from the last column
    and 2nd row, which is value 1, we can go to the left because now we have to
    do an OPPOSITE check up.

    We can go from 1 to 3 because 1 is LESS THAN OR EQUAL TO 3. Etc.

    It's important to note this.

*/

/* Time  Beats: 87.47% */
/* Space Beats: 95.50% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_DFS {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights)
    {
        const int ROWS = heights.size();
        const int COLS = heights[0].size();
        vector<vector<int>> results;

        vector<vector<bool>> pacific (ROWS, vector<bool>(COLS, false));
        vector<vector<bool>> atlantic(ROWS, vector<bool>(COLS, false));

        /**********************/
        /* First and Last Row */
        /**********************/
        for (int row = 0; row < ROWS; row++)
        {
            dfs(row, 0     , -1, pacific,  heights); // Pacific
            dfs(row, COLS-1, -1, atlantic, heights); // ATLANTIC
        }

        /*************************/
        /* First and Last Column */
        /*************************/
        for (int col = 0; col < COLS; col++)
        {
            dfs(0     , col, -1, pacific,  heights); // Pacific
            dfs(ROWS-1, col, -1, atlantic, heights); // ATLANTIC
        }


        /***********/
        /* Results */
        /***********/
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (pacific[row][col] && atlantic[row][col])
                    results.push_back( {row, col} );
            }
        }

        return results;
    }

private:
    void dfs(int row, int col, int prev_height, vector<vector<bool>>& visited, vector<vector<int>>& heights)
    {
        const int ROWS = heights.size();
        const int COLS = heights[0].size();

        if (row < 0 || col < 0 || row >= ROWS || col >= COLS)
            return;

        if (heights[row][col] < prev_height || visited[row][col])
            return;

        visited[row][col] = true;

        /* Signing Cross */
        dfs(row-1, col  , heights[row][col], visited, heights);
        dfs(row+1, col  , heights[row][col], visited, heights);
        dfs(row  , col-1, heights[row][col], visited, heights);
        dfs(row  , col+1, heights[row][col], visited, heights);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Just a BFS Solution.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  94.96% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_BFS {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights)
    {
        const int ROWS = heights.size();
        const int COLS = heights[0].size();
        vector<vector<int>> results;

        vector<vector<bool>> pacific (ROWS, vector<bool>(COLS, false));
        vector<vector<bool>> atlantic(ROWS, vector<bool>(COLS, false));

        /* Signing Cross */
        vector<pair<int, int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};


        queue<pair<int,int>> queue_pacific;
        queue<pair<int,int>> queue_atlantic;

        /*************************/
        /* First and Last Column */
        /*************************/
        for (int row = 0; row < ROWS; row++)
        {
            queue_pacific.push ( {row, 0     } );
            queue_atlantic.push( {row, COLS-1} );

            pacific [row][0]      = true;
            atlantic[row][COLS-1] = true;
        }

        /**********************/
        /* First and Last Row */
        /**********************/
        for (int col = 0; col < COLS; col++)
        {
            queue_pacific.push ( {0     , col} );
            queue_atlantic.push( {ROWS-1, col} );

            pacific [0     ][col] = true;
            atlantic[ROWS-1][col] = true;
        }

        /***************/
        /* BFS Pacific */
        /***************/
        while ( ! queue_pacific.empty())
        {
            auto [row, col] = queue_pacific.front();
            queue_pacific.pop();

            for (const auto& dir : directions)
            {
                int new_row = row + dir.first;
                int new_col = col + dir.second;

                if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                    continue;

                if (heights[new_row][new_col] < heights[row][col])
                    continue;

                if (pacific[new_row][new_col]) // Already visited
                    continue;

                pacific[new_row][new_col] = true;
                queue_pacific.push( {new_row, new_col} );
            }
        }

        /****************/
        /* BFS Atlantic */
        /****************/
        while ( ! queue_atlantic.empty())
        {
            auto [row, col] = queue_atlantic.front();
            queue_atlantic.pop();

            for (const auto& dir : directions)
            {
                int new_row = row + dir.first;
                int new_col = col + dir.second;

                if (new_row < 0 || new_col < 0 || new_row >= ROWS || new_col >= COLS)
                    continue;

                if (heights[new_row][new_col] < heights[row][col])
                    continue;

                if (atlantic[new_row][new_col]) // Already visited
                    continue;

                atlantic[new_row][new_col] = true;
                queue_atlantic.push( {new_row, new_col} );
            }
        }

        /***********/
        /* Results */
        /***********/
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
            {
                if (pacific[row][col] && atlantic[row][col])
                    results.push_back( {row, col} );
            }
        }

        return results;
    }
};
