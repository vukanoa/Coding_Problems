#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    554) Brick Wall
    ===========================

    ============
    Description:
    ============

    There is a rectangular brick wall in front of you with n rows of bricks.
    The ith row has some number of bricks each of the same height (i.e., one
    unit) but they can be of different widths. The total width of each row is
    the same.

    Draw a vertical line from the top to the bottom and cross the least bricks.
    If your line goes through the edge of a brick, then the brick is not
    considered as crossed. You cannot draw a line just along one of the two
    vertical edges of the wall, in which case the line will obviously cross no
    bricks.

    Given the 2D array wall that contains the information about the wall,
    return the minimum number of crossed bricks after drawing such a vertical
    line.

    ===============================================================
    FUNCTION: int leastBricks(std::vector<std::vector<int>>& wall);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: wall = [[1,2,2,1],[3,1,2],[1,3,2],[2,4],[3,1,2],[1,3,1,1]]
    Output: 2


    --- Example 2 ---
    Input: wall = [[1],[1],[1]]
    Output: 3


    *** Constraints ***
    n == wall.length
    1 <= n <= 104
    1 <= wall[i].length <= 10^4
    1 <= sum(wall[i].length) <= 2 * 10^4
    sum(wall[i]) is the same for each row i.
    1 <= wall[i][j] <= 231 - 1

*/

/* Time  Beats: 79.81% */
/* Space Beats: 52.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int leastBricks(std::vector<std::vector<int>>& wall)
    {
        std::unordered_map<int, int> umap;

        for (int i = 0; i < wall.size(); i++)
        {
            int gap = 0;
            for (int j = 0; j < wall[i].size() - 1; j++)
            {
                gap += wall[i][j];

                if (umap.count(gap))
                    umap[gap]++;
                else
                    umap.insert({gap, 1});
            }
        }

        int max = 0;
        for (auto& entry : umap)
            max = std::max(max, entry.second);

        return wall.size() - max;
    }
};
