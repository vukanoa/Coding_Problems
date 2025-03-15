/*
    ============
    === EASY ===
    ============

    ==================================
    3200) Maximum Height of a Triangle
    ==================================

    ============
    Description:
    ============

    You are given two integers red and blue representing the count of red and
    blue colored balls. You have to arrange these balls to form a triangle such
    that the 1st row will have 1 ball, the 2nd row will have 2 balls, the 3rd
    row will have 3 balls, and so on.

    All the balls in a particular row should be the same color, and adjacent
    rows should have different colors.

    Return the maximum height of the triangle that can be achieved.

    =====================================================
    FUNCTION: int maxHeightOfTriangle(int red, int blue);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: red = 2, blue = 4
    Output: 3

    --- Example 2 ---
    Input: red = 2, blue = 1
    Output: 2

    --- Example 3 ---
    Input: red = 1, blue = 1
    Output: 1

    --- Example 4 ---
    Input: red = 10, blue = 1
    Output: 2


    *** Constraints ***
    1 <= red, blue <= 100

*/

#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It's a pain to write this bug-free. There's no special "trick" here, just
    cover all the cases carefully.

*/

/* Time  Beats: 42.60% */
/* Space Beats: 23.96% */

/* Time  Complexity: O(sqrt(max(red, blue))) */
/* Space Complexity: O(1)                    */
class Solution {
public:
    int maxHeightOfTriangle(int red, int blue)
    {
        int start_red     = 0;
        int non_start_red = 0;

        int start_blue     = 0;
        int non_start_blue = 0;

        int tmp_red = red;
        int step = 1;
        while (tmp_red >= step)
        {
            start_red++;

            tmp_red -= step;
            step += 2;
        }

        tmp_red = red;
        step = 2;
        while (tmp_red >= step)
        {
            non_start_red++;

            tmp_red -= step;
            step += 2;
        }


        int tmp_blue = blue;
        step = 1;
        while (tmp_blue >= step)
        {
            start_blue++;

            tmp_blue -= step;
            step += 2;
        }

        tmp_blue = blue;
        step = 2;
        while (tmp_blue >= step)
        {
            non_start_blue++;

            tmp_blue -= step;
            step += 2;
        }

        int left = 0;
        while (start_red > 0 && non_start_blue > 0)
        {
            left += 2;

            start_red--;
            non_start_blue--;
        }

        if (start_red > 0)
            left++;

        int right = 0;
        while (non_start_red > 0 && start_blue > 0)
        {
            right += 2;

            non_start_red--;
            start_blue--;
        }

        if (start_blue > 0)
            right++;

        return max(max(1, left), max(1, right));
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Similar as above, but written in a more concise way.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 59.17% */

/* Time  Complexity: O(sqrt(max(red, blue))) */
/* Space Complexity: O(1) */
class Solution_Concise {
public:
    int maxHeightOfTriangle(int red, int blue)
    {
        return max(helper(red, blue), helper(blue, red));
    }

private:
    int helper(int red, int blue)
    {
        int height = 0;
        int blocks_in_row = 1;

        while (true)
        {
            if (blocks_in_row % 2 == 1)
            {
                if (red >= blocks_in_row)
                    red -= blocks_in_row;
                else
                    break;
            }
            else
            {
                if (blue >= blocks_in_row)
                    blue -= blocks_in_row;
                else
                    break;
            }

            height++;
            blocks_in_row++;
        }

        return height;
    }
};
