#include <iostream>
#include <vector>

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

/*
    ------------
    --- IDEA ---
    ------------

    You can choose which way you want to simulate the "fall". Here what I do is
    I make rocks "fall to the right" and then I rotate.

    Since we MUST actually return the rotated 2D vector, there's no other way
    around it other than actually doing it yourself.

    That's it.

*/

/* Time  Beats: 13.75% */
/* Space Beats: 98.78% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(m * n) */
class Solution {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int m = box.size();
        const int n = box[0].size();

        if (m * n == 1)
            return box;

        // Fall to the right
        for (int i = 0; i < m; i++)
        {
            for (int j = n-1; j > 0; j--)
            {
                if (box[i][j-1] == '#' && box[i][j] == '.')
                {
                    while (j < n && box[i][j] == '.')
                    {
                        box[i][j-1] = '.';
                        box[i][j  ] = '#';
                        j++;
                    }
                }
            }
        }

        // Rotate
        vector<vector<char>> result(n, vector<char>(m, '.'));
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
                result[j][m-1 - i] = box[i][j];
        }

        return result;
    }
};
