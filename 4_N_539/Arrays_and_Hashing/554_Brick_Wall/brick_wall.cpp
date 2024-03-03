#include <iostream>
#include <vector>
#include <unordered_map>

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
        +-----+-----+-----+-----+-----+-----+
        |     |           |           |     |
        +-----+-----+-----+-----+-----+-----+
        |                 |     |           |
        +-----+-----+-----+-----+-----+-----+
        |     |                 |           |
        +-----+-----+-----+-----+-----+-----+
        |           |                       |
        +-----+-----+-----+-----+-----+-----+
        |                 |     |           |
        +-----+-----+-----+-----+-----+-----+
        |     |                 |     |     |
        +-----+-----+-----+-----+-----+-----+

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

/*
    ------------
    --- IDEA ---
    ------------

    The picture makes it obvious, therefore make sure to look at it carefully.

        +-----+-----+-----+-----+-----+-----+
        #     |           |           |     #
        +-----+-----+-----+-----+-----+-----+
        #                 |     |           #
        +-----+-----+-----+-----+-----+-----+
        #     |                 |           #
        +-----+-----+-----+-----+-----+-----+
        #           |                       #
        +-----+-----+-----+-----+-----+-----+
        #                 |     |           #
        +-----+-----+-----+-----+-----+-----+
        #     |                 |     |     #
        +-----+-----+-----+-----+-----+-----+

    If you cannot come up with a Solution straight form the picture, here is
    the explanation.

    We are told that we should minimize crossing the row over the bricks. That
    could also be read like this - We want to maximize the number of endings on
    the same column.

    We are told to:"Draw a vertical line from the top to the bottom and cross
    the least bricks."

    We could also read that as:"Which column has the most endpoints of bricks?"

    (Left and right endings are not considered)

    That question alone should give you he answer on how to solve this problem.
    Once you've noticed that and asked that question, you're done. Now you only
    have to code what you've jus said, which is the easy part.

    We cannot use a vector of size total_width of a row since we're told in
    the constraints:
        1 <= sum(wall[i].length) <= 2 * 10^4

    Which means that we'd get a MLE(Memory Limit Exceeded).

    But even if that wasn't specified, we can notice that it's pretty possible
    not to use some of the "points"(columns) as there can be no endings at that
    column. Therefore, we don't have to keep the 0 value unnecessarily.

    Which data structure can help us keep track of some, but not necessarily
    all elements? Hash Map.

    The only important thing to note here is this:

    If we have this row: [1, 2, 2, 1]

          1         2           2        1     <--- Widths of bricks
        +-----+-----+-----+-----+-----+-----+
        #     |           |           |     #
        +-----+-----+-----+-----+-----+-----+
        0     1     2     3     4     5     6  <--- Columns

    It's importnat to notice that, since we're only looking at the endings of
    bricks(i.e. right end point), we DON'T have to look at the ending of the
    very last brick since that represents the edges of the entire wall which
    we are told to ignore since we could always just go down the edges and have
    the total number of crossed bricks equal 0. Therefore, we DON'T have to
    check for the end of the last brick and that is why in the nested "for" we
    go from:
        j = 0; j < wall[curr_row].size() - 1;
                                        ^^^^^

    That's why we have this -1, we don't care about the last brick's end point.

    At the end of processing the entire wall, our Hash Map "ending_map" will
    have each used columns(columns that have at least one brick ending at that
    column) and their respective number of bricks that end that that column.

    So instead of just returning the highest value from the Hash Map, we must
    subtract that value from the total number of rows since that represents the
    number of bricks we actually had to cross.

*/

/* Time  Beats: 97.89% */
/* Space Beats: 25.85% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int leastBricks(std::vector<std::vector<int>>& wall)
    {
        std::unordered_map<int, int> uncrossed_bricks;

        for (int row = 0; row < wall.size(); row++)
        {
            int gap = 0;
            for (int col = 0; col < wall[row].size() - 1; col++)
            {
                gap += wall[row][col]; // wall[row][col] <==> brick_width

                uncrossed_bricks[gap]++; // Initial value is 0
            }
        }

        int max_uncrossed_bricks = 0;
        for (auto& entry : uncrossed_bricks)
            max_uncrossed_bricks = std::max(max_uncrossed_bricks, entry.second);

        return wall.size() - max_uncrossed_bricks; // Least crossed bricks
    }
};
