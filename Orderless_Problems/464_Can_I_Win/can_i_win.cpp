/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    464) Can I Win
    ===========================

    ============
    Description:
    ============

    In the "100 game" two players take turns adding, to a running total, any
    integer from 1 to 10. The player who first causes the running total to
    reach or exceed 100 wins.

    What if we change the game so that players cannot re-use integers?

    For example, two players might take turns drawing from a common pool of
    numbers from 1 to 15 without replacement until they reach a total >= 100.

    Given two integers maxChoosableInteger and desiredTotal, return true if the
    first player to move can force a win, otherwise, return false. Assume both
    players play optimally.

    ==================================================================
    FUNCTION: bool canIWin(int maxChoosableInteger, int desiredTotal);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: maxChoosableInteger = 10, desiredTotal = 11
    Output: false
    Explanation:
    No matter which integer the first player choose, the first player will lose.
    The first player can choose an integer from 1 up to 10.
    If the first player choose 1, the second player can only choose integers from 2 up to 10.
    The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
    Same with other integers chosen by the first player, the second player will always win.

    --- Example 2 ---
    Input: maxChoosableInteger = 10, desiredTotal = 0
    Output: true

    --- Example 3 ---
    Input: maxChoosableInteger = 10, desiredTotal = 1
    Output: true


    *** Constraints ***
    1 <= maxChoosableInteger <= 20
    0 <= desiredTotal <= 300

*/

#include <cstring>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 90.64% */
/* Space Beats: 89.27% */

/* Time  Complexity: O(2^N * N) */
/* Space Complexity: O(2^N * N) */
class Solution {
private:
    int memo[1 << 21];

public:
    bool canIWin(int n, int target)
    {
        if (target == 0)
            return true;

        if (target > (n * (n + 1)) / 2)
            return false;

        /* Memset */ 
        memset(memo, -1, sizeof(memo));

        return solve(0, target, n);
    }

private:
    bool solve(int mask, int target, int n)
    {
        if (target <= 0)
            return memo[mask] = (__builtin_popcount(mask) % 2 != 0);

        if (memo[mask] != -1)
            return memo[mask];

        int bits_used = __builtin_popcount(mask);
        bool curr_player_wins = (bits_used & 1);

        for (int i = 0; i < n; i++)
        {
            if (mask & (1 << i))
                continue;

            int new_mask = mask | (1 << i);

            if ((bits_used % 2 != 0 && ! solve(new_mask, target - i - 1, n)) ||
                (bits_used % 2 == 0 &&   solve(new_mask, target - i - 1, n)))
            {
                return memo[mask] = ! curr_player_wins;
            }
        }

        return memo[mask] = bits_used & 1;
    }
};
