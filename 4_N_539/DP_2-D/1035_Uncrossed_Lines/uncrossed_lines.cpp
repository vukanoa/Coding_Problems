#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    1035) Uncrossed Lines
    ===========================

    ============
    Description:
    ============

    You are given two integer arrays nums1 and nums2. We write the integers of
    nums1 and nums2 (in the order they are given) on two separate horizontal
    lines.

    We may draw connecting lines: a straight line connecting two numbers
    nums1[i] and nums2[j] such that:

        nums1[i] == nums2[j], and
        the line we draw does not intersect any other connecting
        (non-horizontal) line.

    Note that a connecting line cannot intersect even at the endpoints (i.e.,
    each number can only belong to one connecting line).

    Return the maximum number of connecting lines we can draw in this way.

    ========================================================================
    FUNCTION: int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2);
    ========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        1 4 2
        |  \
        1 2 4
    Input: nums1 = [1,4,2], nums2 = [1,2,4]
    Output: 2
    Explanation: We can draw 2 uncrossed lines as in the diagram.
    We cannot draw 3 uncrossed lines, because the line from nums1[1] = 4 to
    nums2[2] = 4 will intersect the line from nums1[2]=2 to nums2[1]=2.

    --- Example 2 ---
         2 5 1 2 5
          \_  \ \_
            \  \  \
        10 5 2 1 5 2

        or

         2 5 1 2 5
         \  \   \
          \_ \__ \
            \   \ \
        10 5 2 1 5 2

    Input: nums1 = [2,5,1,2,5], nums2 = [10,5,2,1,5,2]
    Output: 3



    --- Example 3 ---

        1 3 7 1 7 5
        |      \
        1 9 2 5 1

        or

        1 3 7 1 7 5
        |       _/
        |      /
        1 9 2 5 1
    Input: nums1 = [1,3,7,1,7,5], nums2 = [1,9,2,5,1]
    Output: 2


    *** constraints ***
    1 <= nums1.length, nums2.length <= 500
    1 <= nums1[i], nums2[j] <= 2000

*/

/*
    ------------
    --- IDEA ---
    ------------

    This is the naive approach. It works, but it's too slow.
    It gives TLE(Time Limit Exceeded)

    However, I wanted to write this down too to show how this naive approach
    would be implemented.

*/

/******************************/
/***** This code gives TLE ****/
/******************************/
class Solution_TLE_Backtracking {
public:
    int maxUncrossedLines(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int result = 0;

        backtracking_up(nums1, nums2, 0, 0, 0, result);

        return result;
    }

private:
    void backtracking_up(std::vector<int>& nums1,
                         std::vector<int>& nums2,
                         int up_start,
                         int bot_start,
                         int curr_lines,
                         int& result)
    {
        if (up_start == nums1.size())
            return;

        for (int i = up_start; i < nums1.size(); i++)
            backtracking_down(nums1, nums2, i, bot_start, curr_lines, result);
    }

    void backtracking_down(std::vector<int>& nums1,
                           std::vector<int>& nums2,
                           int up_idx,
                           int bot_start,
                           int curr_lines,
                           int& result)
    {
        if (bot_start == nums2.size())
            return;

        for (int i = bot_start; i < nums2.size(); i++)
        {
            if (nums1[up_idx] != nums2[i])
                continue;

            result = std::max(result, curr_lines+1);
            backtracking_up(nums1, nums2, up_idx+1, i+1, curr_lines+1, result);
        }

        backtracking_up(nums1, nums2, up_idx+1, bot_start, curr_lines, result);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Optimizing Backtracking(DFS) approach to cache calculated work.

*/

/* Time  Beats: 32.79% */
/* Space Beats: 58.52% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_Memoization {
public:
    int maxUncrossedLines(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int ROWS = nums1.size();
        int COLS = nums2.size();

        std::vector<std::vector<int>> dp(ROWS, std::vector<int>(COLS, -1));

        return dfs(nums1, nums2, dp, 0, 0);
    }

private:
    int dfs(std::vector<int>& nums1,
            std::vector<int>& nums2,
            std::vector<std::vector<int>>& dp,
            int i,
            int j)
    {
        int ROWS = nums1.size();
        int COLS = nums2.size();

        if (i == ROWS || j == COLS )
            return 0;

        if (dp[i][j] != -1)
            return dp[i][j];

        if (nums1[i] == nums2[j])
            dp[i][j] = 1 + dfs(nums1, nums2, dp, i+1, j+1);
        else
            dp[i][j] = std::max(dfs(nums1, nums2, dp, i+1, j  ),
                                dfs(nums1, nums2, dp, i  , j+1));

        return dp[i][j];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a common LCS problem.

                    1 4 2 2
                    |  / /
                    1 2 2 4

            // Litterally the same as if we had 2 strings "adbb" and "abdd"
                    a d b b
                    a b b d


             0     1     2     3     4
             1     2     2     4     ""
          +-----+-----+-----+-----+-----+
    0  1  |  3  |  2  |  1  |  1  =  0  =
          +-----+-----+-----+-----+-----+
    1  4  |  2  |  2  |  1  |  1  =  0  =
          +-----+-----+-----+-----+-----+
    2  2  |  2  |  2  |  1  |  0  =  0  =
          +-----+-----+-----+-----+-----+
    3  2  |  1  |  1  |  1  |  0  =  0  =
          +=====+=====+=====+=====+=====+
    4  "" |  0  |  0  |  0  |  0  |  0  |
          +=====+=====+=====+=====+=====+

*/

/* Time  Beats: 76.83% */
/* Space Beats: 58.52% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(ROWS * COLS) */
class Solution_LCS{
public:
    int maxUncrossedLines(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int ROWS = nums1.size();
        int COLS = nums2.size();

        std::vector<std::vector<int>> dp(ROWS+1, std::vector<int>(COLS+1, 0));

        for (int i = ROWS-1; i >= 0; i--)
        {
            for (int j = COLS-1; j >= 0; j--)
            {
                if (nums1[i] == nums2[j])
                    dp[i][j] = 1 + dp[i+1][j+1];

                dp[i][j] = std::max({dp[i][j], dp[i+1][j], dp[i][j+1]});
            }
        }

        return dp[0][0];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above just more Space efficient. We're only using a single vector
    instead of the whole matrix(i.e. vector of vectors).

*/

/* Time  Beats: 60.95% */
/* Space Beats: 75.20% */

/* Time  Complexity: O(ROWS * COLS) */
/* Space Complexity: O(COLS) */
class Solution_LCS_Space_Efficient {
public:
    int maxUncrossedLines(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        int ROWS = nums1.size();
        int COLS = nums2.size();

        std::vector<int> dp(COLS+1, 0);

        for (int i = ROWS-1; i >= 0; i--)
        {
            std::vector<int> curr_row(COLS+1, 0);

            for (int j = COLS-1; j >= 0; j--)
            {
                if (nums1[i] == nums2[j])
                    curr_row[j] = 1 + dp[j+1];

                curr_row[j] = std::max({curr_row[j], dp[j], curr_row[j+1]});
            }

            dp.clear();
            dp = curr_row;
        }

        return dp[0];
    }
};
