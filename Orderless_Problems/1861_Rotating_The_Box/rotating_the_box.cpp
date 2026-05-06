/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1861) Rotating the Box
    ===========================

    ============
    Description:
    ============

    You are given an m x n matrix of characters box representing a side-view of
    a box. Each cell of the box is one of the following:

        + A stone '#'

        + A stationary obstacle '*'

        + Empty '.'

    The box is rotated 90 degrees clockwise, causing some of the stones to fall
    due to gravity. Each stone falls down until it lands on an obstacle,
    another stone, or the bottom of the box. Gravity does not affect the
    obstacles' positions, and the inertia from the box's rotation does not
    affect the stones' horizontal positions.

    It is guaranteed that each stone in box rests on an obstacle, another
    stone, or the bottom of the box.

    Return an n x m matrix representing the box after the rotation described
    above.

    =======================================================================
    FUNCTION: vector<vector<char>> rotateTheBox(vector<vector<char>>& box);
    =======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: box = [["#",".","#"]]
    Output: [["."],
             ["#"],
             ["#"]]

    --- Example 2 ---
    Input: box = [["#",".","*","."],
                  ["#","#","*","."]]
    Output: [["#","."],
             ["#","#"],
             ["*","*"],
             [".","."]]

    --- Example 3 ---
    Input: box = [["#","#","*",".","*","."],
                  ["#","#","#","*",".","."],
                  ["#","#","#",".","#","."]]
    Output: [[".","#","#"],
             [".","#","#"],
             ["#","#","*"],
             ["#","*","."],
             ["#",".","*"],
             ["#",".","."]]


    *** Constraints ***
    m == box.length
    n == box[i].length
    1 <= m, n <= 500
    box[i][j] is either '#', '*', or '.'.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    You can choose which way you want to simulate the "fall".
    Here what I do is I make rocks "fall to the right" and only thenI rotate.

    Keep in mind that this Solution DOES change the original "boxGrid" which is
    passed by reference.

    So this may not be allowed. In that case we'd need to first rotate and only
    then simulate the fall, but this time the fall is "fall downwards" and NOT
    "to the right".

*/

/* Time  Beats: 90.91% */
/* Space Beats: 15.72% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& boxGrid)
    {
        const int ROWS = boxGrid.size();
        const int COLS = boxGrid[0].size();

        /* Simulate "fall to the right" */
        for (int row = 0; row < ROWS; row++)
        {
            int col_to_put = 0;

            for (int col = 0; col < COLS; col++)
            {
                if (boxGrid[row][col] == '.')
                {
                    swap(boxGrid[row][col], boxGrid[row][col_to_put]);
                    col_to_put++;
                }
                else if (boxGrid[row][col] == '*')
                {
                    col_to_put = col + 1;
                }
            }
        }
        
        /* Rotate */
        vector<vector<char>> result(COLS, vector<char>(ROWS));
        for (int row = 0; row < ROWS; row++)
        {
            for (int col = 0; col < COLS; col++)
                result[col][ROWS-1 - row] = boxGrid[row][col];
        }
                
        return result;
    }
};
