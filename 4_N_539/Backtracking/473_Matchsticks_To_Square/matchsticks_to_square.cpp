#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    473) Matchsticks to Square
    ===========================

    ============
    Description:
    ============

    You are given an integer array matchsticks where matchsticks[i] is the
    length of the ith matchstick. You want to use all the matchsticks to make
    one square. You should not break any stick, but you can link them up, and
    each matchstick must be used exactly one time.

    Return true if you can make this square and false otherwise.

    ====================================================
    FUNCTION: bool makesquare(vector<int>& matchsticks);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: matchsticks = [1,1,2,2,2]
    Output: true
    Explanation: You can form a square with length 2, one side of the square
    came two sticks with length 1.


    --- Example 2 ---
    Input: matchsticks = [3,3,3,3,4]
    Output: false
    Explanation: You cannot find a way to form a square with all the
    matchsticks.


    *** Constraints ***
    1 <= matchsticks.length <= 15
    1 <= matchsticks[i] <= 10^8

*/

/*
    ------------
    --- IDEA ---
    ------------

    Classic Backtracking.

*/

/* Time  Beats: 19.14% */
/* Space Beats: 94.11% */

/* Time  Complexity: O(4^n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool makesquare(std::vector<int>& matchsticks)
    {
        if (matchsticks.size() < 4)
            return false;

        int sum = std::accumulate(matchsticks.begin(), matchsticks.end(), 0);
        int side_length = sum / 4;

        if (sum != side_length * 4)
            return false;

        std::sort(matchsticks.begin(), matchsticks.end(),std::greater<int>());
        std::vector<int> sides(4, 0);

        return backtracking(matchsticks, 0, sides, side_length);
    }

    bool backtracking(std::vector<int>& matchsticks, int i, std::vector<int>& sides, int& side_length)
    {
        if (i == matchsticks.size())
            return true;

        for (int x = 0; x < 4; x++)
        {
            if (sides[x] + matchsticks[i] > side_length)
                continue;

            sides[x] += matchsticks[i];

            if (backtracking(matchsticks, i+1, sides, side_length))
                return true;

            sides[x] -= matchsticks[i];
        }

        return false;
    }
};
