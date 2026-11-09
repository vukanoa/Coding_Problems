/*
    ============
    === EASY ===
    ============

    ======================================
    3931) Check Adjacent Digit Differences
    ======================================

    ============
    Description:
    ============

    You are given a string s consisting of digits.

    Return true if the absolute difference between every pair of adjacent
    digits is at most 2, otherwise return false.

    The absolute difference between a and b is defined as abs(a - b).

    =================================================
    FUNCTION: bool isAdjacentDiffAtMostTwo(string s);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "132"
    Output: true
    Explanation:
        The absolute difference between digits at s[0] and s[1] is abs(1 - 3) = 2.
        The absolute difference between digits at s[1] and s[2] is abs(3 - 2) = 1.
        Since both differences are at most 2, the answer is true.

    --- Example 2 ---
    Input: s = "129"
    Output: false
    Explanation:
        The absolute difference between digits at s[0] and s[1] is abs(1 - 2) = 1.
        The absolute difference between digits at s[1] and s[2] is abs(2 - 9) = 7, which is greater than 2.
        Therefore, the answer is false.


    *** Constraints ***
    2 <= s.length <= 100
    s consists only of digits.

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  47.23% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool isAdjacentDiffAtMostTwo(string s)
    {
        const int N = s.size();

        for (int i = 0; i < N-1; i++)
        {
            if (abs((s[i] - '0') - (s[i+1] - '0')) > 2)
                return false;
        }

        return true;
    }
};
