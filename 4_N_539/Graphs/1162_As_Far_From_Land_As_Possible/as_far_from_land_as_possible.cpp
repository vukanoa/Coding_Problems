#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    1162) As Far From Land As Possible
    ==================================

    ============
    Description:
    ============

    Given an n x n grid containing only values 0 and 1, where 0 represents
    water and 1 represents land, find a water cell such that its distance to
    the nearest land cell is maximized, and return the distance. If no land or
    water exists in the grid, return -1.

    The distance used in this problem is the Manhattan distance: the distance
    between two cells (x0, y0) and (x1, y1) is |x0 - x1| + |y0 - y1|.

    =====================================================
    FUNCTION: int maxDistance(vector<vector<int>>& grid);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: grid = [[1,0,1],[0,0,0],[1,0,1]]
    Output: 2
    Explanation: The cell (1, 1) is as far as possible from all the land with
                 distance 2.


    --- Example 2 ---
    Input: grid = [[1,0,0],[0,0,0],[0,0,0]]
    Output: 4
    Explanation: The cell (2, 2) is as far as possible from all the land with
                 distance 4.


    *** Constraints ***
    n == grid.length
    n == grid[i].length
    1 <= n <= 100
    grid[i][j] is 0 or 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    DFS + Multi-source BFS.

    Multi-source BFS is a very important technique to master. It could be
    considered fundamental.

    Check out LeetCode: Walls & Gates.


    This is a good example to show how this algorithm works:


                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  0  |  0  |  0  |  0  |  1  |  1  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  1  |  1  |  0  |  0  |  1  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  1  |  1  |  0  |  0  |  1  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  0  |  0  |  0  |  0  |  0  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  0  |  0  |  0  |  0  |  1  |  1  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  1  |  1  |  1  |  0  |  0  |  0  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  1  |  0  |  0  |  0  |  0  |  0  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+

    First we find all the land(1's) and push it's "coordinates"(indices) in
    a queue as a std::pair<int, int>.
    (Also we must exchange all 1's to 2's to prevent infinite loops)



    Now we have this:
    (This is order is because I always go: Up, Down, Left, Right)

    queue = {{0,5}, {1,5}, {2,5}, {0,6}, {1,1}, {2,1}, {2,2}, {1,2}, {4,5}, {5,5}, {5,0}, {6,0}, {5,1}, {5,2}}

                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  0  |  0  |  0  |  0  |  2  |  2  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  2  |  2  |  0  |  0  |  2  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  2  |  2  |  0  |  0  |  2  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  0  |  0  |  0  |  0  |  0  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  0  |  0  |  0  |  0  |  2  |  2  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  2  |  2  |  2  |  0  |  0  |  0  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  2  |  0  |  0  |  0  |  0  |  0  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+


    Now that we have a filled queue, we start doing BFS. For all the elements
    in the queue we "mark" every adjacent 0 as visited(turn it to 3) and we
    push it in the queue.

    (Here I'll designate visited water cells as '/' instead of 3, just for the
    sake of readabilty)


                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  /  |  /  |  0  |  /  |  2  |  2  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  /  |  2  |  2  |  /  |  /  |  2  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  /  |  2  |  2  |  /  |  /  |  2  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  0  |  /  |  /  |  0  |  0  |  /  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  /  |  /  |  /  |  0  |  /  |  2  |  2  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  2  |  2  |  2  |  /  |  0  |  /  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  2  |  /  |  /  |  0  |  0  |  0  |  0  |
                +-----+-----+-----+-----+-----+-----+-----+

    Now our queue looks like this:

    queue = {{4,0}, {4,1}, {6,1}, {5,3}, {4,2}, {6,2},               // This is around the first  land
             {0,1}, {1,0}, {2,0}, {3,1}, {3,2}, {3,3}, {1,3}, {0,2}, // This is around the second land
             {4,4}, {5,5}, {3,6}, {5,6},                             // This is around the third  land
             {4,0}, {6,1}, {4,1}, {4,2}, {6,2}, {6,3}}               // This is around the fourth land





    Now we do the BFS again.
    Again, we'll mark 0's as visited by turning them to 3, however here I'll
    designate it with a dash '-' this time, again for the sake of readability.

                +-----+-----+-----+-----+-----+-----+-----+
                |  -  |  /  |  /  |  -  |  /  |  2  |  2  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  /  |  2  |  2  |  /  |  /  |  2  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  /  |  2  |  2  |  /  |  /  |  2  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  -  |  /  |  /  |  -  |  -  |  /  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  /  |  /  |  /  |  -  |  /  |  2  |  2  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  2  |  2  |  2  |  /  |  -  |  /  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  2  |  /  |  /  |  -  |  0  |  -  |  -  |
                +-----+-----+-----+-----+-----+-----+-----+

    Now our queue looks like this:

    queue = {{0,3}, {4,3},
             {0,0}, {3,0}, {3,3}, {3,0},
             {4,5}, {6,5}, {6,6},
             {6,3}, {4,3}}


    Now you can see that there is only one 0, therefore our grid would look
    like this:

                +-----+-----+-----+-----+-----+-----+-----+
                |  -  |  /  |  /  |  -  |  /  |  2  |  2  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  /  |  2  |  2  |  /  |  /  |  2  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  /  |  2  |  2  |  /  |  /  |  2  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  -  |  /  |  /  |  -  |  -  |  /  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  /  |  /  |  /  |  -  |  /  |  2  |  2  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  2  |  2  |  2  |  /  |  -  |  /  |  /  |
                +-----+-----+-----+-----+-----+-----+-----+
                |  2  |  /  |  /  |  -  |  &  |  -  |  -  |
                +-----+-----+-----+-----+-----+-----+-----+

    Our queue = {{4,6}}

    And we can see that there are no more 0's, therefore, since we have run
    this BFS 3 times, we can conclude that the farthest 0 from all the lands is
    at distance 3.

    Notice that we do not have to calculate the distance using their formula
    since we were checking cells each turn in 4 different directions.

*/

/* Time  Beats: 94.37% */
/* Space Beats: 21.00% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int maxDistance(std::vector<std::vector<int>>& grid)
    {
        const int N = grid.size();
        std::queue<std::pair<int, int>> queue;

        /* Push each Island in a Queue */
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (grid[i][j] == 1)
                    dfs(grid, queue, i, j);
            }
        }

        /* If all water   OR if all land */
        if (queue.empty() || queue.size() == N*N)
            return -1;

        std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        int max_distance = -1;

        while (!queue.empty())
        {
            max_distance++;

            int size = queue.size();
            for (int i = 0; i < size; i++)
            {
                std::pair<int, int> field = queue.front();
                queue.pop();

                for (const auto& dir : directions)
                {
                    int row = field.first  + dir.first;
                    int col = field.second + dir.second;

                    if (row < 0 || col < 0 || row == N || col == N || grid[row][col] != 0)
                        continue;

                    grid[row][col] = 3;
                    queue.push( {row, col} );
                }
            }
        }

        /* Restore Grid to original state (We are NOT in obligation to do it)*/
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (grid[i][j] == 2)
                    grid[i][j] = 1;
                else if (grid[i][j] == 3)
                    grid[i][j] = 0;
            }
        }

        return max_distance;
    }

private:
    void dfs(std::vector<std::vector<int>>& grid,
             std::queue<std::pair<int, int>>& queue,
             int i,
             int j)
    {
        const int N = grid.size();

        if (i < 0 || j < 0 || i == N || j == N || grid[i][j] != 1)
            return;

        queue.push( {i, j} );

        grid[i][j] = 2;

        dfs(grid, queue, i-1, j  );
        dfs(grid, queue, i+1, j  );
        dfs(grid, queue, i  , j-1);
        dfs(grid, queue, i  , j+1);
    }
};
