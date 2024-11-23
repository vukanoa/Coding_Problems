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
    (In other words we MUST iterate through the rows and do it ourselves, but
    as you will see in the 2nd Solution down below, this part CAN be optimized)

    That's it.

*/

/* Time  Beats: 13.75% */
/* Space Beats: 98.78% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1)     */ // Result is not considered extra space
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




/*
    ------------
    --- IDEA ---
    ------------

    Overall Time Complexity is unchanged, however this one is MUCH more
    efficient since we are not "moving" each rock cell-by-cell, instead we are
    swapping with the rightmost empty cell.

    Checkout:LeetCode 26 "Remove Duplicates from Sorted Array" if you aren't
    familiar with this technique.

    However, in this one that wouldn't be enough, we actually need to SWAP the
    rock with the empty cell we wish to place rock at.

    In LeetCode 26, we do NOT care about elements after mth unique, but here we
    very much DO.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  98.78% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1)     */ // Result is not considered extra space
class Solution_Efficient {
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
            int to_place_idx = n-1;

            for (int j = n-1; j >= 0; j--)
            {
                if (box[i][j] == '#')
                    swap(box[i][to_place_idx--], box[i][j]);
                else if (box[i][j] == '*')
                    to_place_idx = j-1;
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




/*
    ------------
    --- IDEA ---
    ------------

    Here we are NOT modifying the Input and we're doing both "the fall" and the
    rotation at the same time.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  98.78% */

/* Time  Complexity: O(m * n) */
/* Space Complexity: O(1)     */ // Result is not considered extra space
class Solution_Efficient_Non-Modifying {
public:
    vector<vector<char>> rotateTheBox(vector<vector<char>>& box)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int m = box.size();
        const int n = box[0].size();

        vector<vector<char>> result(n, vector<char>(m, '.'));

        // Fall to the right and Rotate at the same time
        for (int i = 0; i < m; i++)
        {
            int to_place_idx = n-1;

            for (int j = n-1; j >= 0; j--)
            {
                if (box[i][j] == '#')
                {
                    result[to_place_idx][m-1 - i] = '#';
                    to_place_idx--;
                }
                else if (box[i][j] == '*')
                {
                    result[j][m-1 - i] = '*';
                    to_place_idx = j-1;
                }
            }
        }

        return result;
    }
};
