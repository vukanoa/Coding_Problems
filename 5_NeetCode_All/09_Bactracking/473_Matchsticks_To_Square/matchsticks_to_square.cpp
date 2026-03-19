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

#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 21.36% */
/* Space Beats: 90.94% */

/* Time  Complexity: O(4^N) */
/* Space Complexity: O(N)   */
class Solution {
public:
    bool makesquare(vector<int>& matchsticks)
    {
        const int N = matchsticks.size();
        if (N < 4)
            return false;

        int sum = accumulate(matchsticks.begin(), matchsticks.end(), 0);

        if (sum % 4 != 0)
            return false;

        int side_length = sum / 4;

        /* Sort */
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());
        vector<int> sides(4, 0);

        return backtracking(0, sides, side_length, matchsticks);
    }

    bool backtracking(int match_idx, vector<int>& sides, int& side_length, vector<int>& matchsticks)
    {
        const int N = matchsticks.size();
        if (match_idx == N)
            return true;

        for (int side_idx = 0; side_idx < 4; side_idx++)
        {
            if (sides[side_idx] + matchsticks[match_idx] > side_length)
                continue;

            sides[side_idx] += matchsticks[match_idx];

            if (backtracking(match_idx+1, sides, side_length, matchsticks))
                return true;

            sides[side_idx] -= matchsticks[match_idx];
        }

        return false;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 44.83% */
/* Space Beats: 99.02% */

/* Time  Complexity: O(4^N) */
/* Space Complexity: O(N)   */
class Solution_2 {
public:
    bool makesquare(vector<int>& matchsticks)
    {
        const int N = matchsticks.size();

        if (N < 4)
            return false;

        unsigned long long total_sum = accumulate(matchsticks.begin(), matchsticks.end(), 0ULL);

        if (total_sum % 4 != 0)
            return false;

        /* Sort in DESCENDING order!!! (VERY important!) */
        sort(matchsticks.begin(), matchsticks.end(), greater<int>());

        unsigned long long target_sum = total_sum / 4;

        return backtracking(0, 0, 0, 0, 0, target_sum, matchsticks);
    }

private:
    bool backtracking(int idx, int left, int top, int right, int bottom, unsigned long long& target_sum, vector<int>& matchsticks)
    {
        if (left > target_sum || top > target_sum || right > target_sum || bottom > target_sum)
            return false;

        if (idx == matchsticks.size())
            return true;

        int x = matchsticks[idx];
        if (backtracking(idx + 1, left + x, top    , right    , bottom    , target_sum, matchsticks)) return true;
        if (backtracking(idx + 1, left    , top + x, right    , bottom    , target_sum, matchsticks)) return true;
        if (backtracking(idx + 1, left    , top    , right + x, bottom    , target_sum, matchsticks)) return true;
        if (backtracking(idx + 1, left    , top    , right    , bottom + x, target_sum, matchsticks)) return true;

        return false;
    }
};
