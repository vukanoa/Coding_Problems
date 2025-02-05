/*
    ============
    === EASY ===
    ============

    ===========================
    3248) Snake In Matrix
    ===========================

    ============
    Description:
    ============

    There is a snake in an n x n matrix grid and can move in four possible
    directions. Each cell in the grid is identified by the position:
        grid[i][j] = (i * n) + j.

    The snake starts at cell 0 and follows a sequence of commands.

    You are given an integer n representing the size of the grid and an array
    of strings commands where each command[i] is either "UP", "RIGHT", "DOWN",
    and "LEFT". It's guaranteed that the snake will remain within the grid
    boundaries throughout its movement.

    Return the position of the final cell where the snake ends up after
    executing commands.

    ====================================================================
    FUNCTION: int finalPositionOfSnake(int n, vector<string>& commands);
    ====================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 2, commands = ["RIGHT","DOWN"]
    Output: 3

    --- Example 2 ---
    Input: n = 3, commands = ["DOWN","RIGHT","UP"]
    Output: 1


    *** Constraints ***
    2 <= n <= 10
    1 <= commands.length <= 100
    commands consists only of "UP", "RIGHT", "DOWN", and "LEFT".
    The input is generated such the snake will not move outside of the
    boundaries.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Since we're told this:

        "It's guaranteed that the snake will remain within the grid
        boundaries throughout its movement."

    We can simply count the total horizontal and total vertical shift.

    We'll treat:
        1) "UP"    as -1 vertical
        1) "DOWN"  as +1 horizontal
        1) "LEFT"  as -1 vertical
        1) "RIGHT" as +1 horizontal

    Now simply iterate through commands and count. Afterwards, return by the
    given formula.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.44% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int finalPositionOfSnake(int n, vector<string>& commands)
    {
        int horizontal = 0;
        int vertical   = 0;
        for (const string& str : commands)
        {
            switch (str[0])
            {
                case 'U':
                    vertical--;
                    break;

                case 'D':
                    vertical++;
                    break;

                case 'L':
                    horizontal--;
                    break;

                case 'R':
                    horizontal++;
                    break;
            }
        }

        return (n * vertical) + horizontal;
    }
};
