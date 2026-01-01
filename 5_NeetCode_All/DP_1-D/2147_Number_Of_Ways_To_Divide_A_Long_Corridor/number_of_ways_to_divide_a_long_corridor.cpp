/*
    ============
    === HARD ===
    ============

    ==============================================
    2147) Number of Ways to Divide a Long Corridor
    ==============================================

    ============
    Description:
    ============

    Along a long library corridor, there is a line of seats and decorative
    plants. You are given a 0-indexed string corridor of length n consisting of
    letters 'S' and 'P' where each 'S' represents a seat and each 'P'
    represents a plant.

    One room divider has already been installed to the left of index 0, and
    another to the right of index n - 1. Additional room dividers can be
    installed. For each position between indices i - 1 and i (1 <= i <= n - 1),
    at most one divider can be installed.

    Divide the corridor into non-overlapping sections, where each section has
    exactly two seats with any number of plants. There may be multiple ways to
    perform the division. Two ways are different if there is a position with a
    room divider installed in the first way but not in the second way.

    Return the number of ways to divide the corridor. Since the answer may be
    very large, return it modulo 109 + 7. If there is no way, return 0.

    ============================================
    FUNCTION: int numberOfWays(string corridor);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: corridor = "SSPPSPS"
    Output: 3
    Explanation: There are 3 different ways to divide the corridor.  The black
                 bars in the above image indicate the two room dividers already
                 installed.  Note that in each of the ways, each section has
                 exactly two seats.


    --- Example 2 ---
    Input: corridor = "PPSPSP"
    Output: 1
    Explanation: There is only 1 way to divide the corridor, by not installing
                 any additional dividers.  Installing any would create some
                 section that does not have exactly two seats.


    --- Example 3 ---
    Input: corridor = "S"
    Output: 0
    Explanation: There is no way to divide the corridor because there will
                 always be a section that does not have exactly two seats.


    *** Constraints ***
    n == corridor.length
    1 <= n <= 10^5
    corridor[i] is either 'S' or 'P'.

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 47.00% */
/* Space Beats: 51.50% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int numberOfWays(string corridor)
    {
        const int N = corridor.size();
        const int MOD = 1e9 + 7;
        vector<int> position;

        for (int i = 0; i < corridor.size(); i++)
        {
            if (corridor[i] == 'S')
                position.push_back(i);
        }
        
        if (position.empty() || position.size() & 1)
            return 0;
        
        long long result = 1;
        for (int i = 2; i < position.size(); i += 2)
        {
            int len_of_gap = position[i] - position[i - 1];

            result = (result * len_of_gap) % MOD;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 63.69% */
/* Space Beats: 64.25% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Space_Optimized {
public:
    int numberOfWays(string corridor)
    {
        const int MOD = 1e9 + 7;

        int zero = 0;
        int one  = 0;
        int two  = 1;

        for (char thing : corridor)
        {
            if (thing == 'S')
            {
                zero = one;
                swap(one, two);
            }
            else
            {
                two = (two + zero) % MOD;
            }
        }

        return zero;
    }
};
