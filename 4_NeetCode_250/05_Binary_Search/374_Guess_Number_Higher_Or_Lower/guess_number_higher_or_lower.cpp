/*
    ============
    === EASY ===
    ============

    =================================
    374) Guess Number Higher or Lower
    =================================

    ============
    Description:
    ============

    We are playing the Guess Game. The game is as follows:

    I pick a number from 1 to n. You have to guess which number I picked.

    Every time you guess wrong, I will tell you whether the number I picked is
    higher or lower than your guess.

    You call a pre-defined API int guess(int num), which returns three possible
    results:

       -1: Your guess is higher than the number I picked (i.e. num >  pick).
        1: Your guess is lower  than the number I picked (i.e. num <  pick).
        0: your guess is equal  to   the number I picked (i.e. num == pick).

    Return the number that I picked.

    =================================
    FUNCTION: int guessNumber(int n);
    =================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10, pick = 6
    Output: 6

    --- Example 2 ---
    Input: n = 1, pick = 1
    Output: 1

    --- Example 3 ---
    Input: n = 2, pick = 1
    Output: 1

    *** Constraints ***
    1 <= n <= 2^31 - 1
    1 <= pick <= n

*/

using namespace std;

/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return      -1 if num is higher than the picked number
 *               1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

/*
    ------------
    --- IDEA ---
    ------------

    This is a "Lower Bound" implementation. If we guesses a STRICTLY SMALLER
    number, i.e. pick > our_guess, then simply:

        low = mid + 1;

    Otherwise

        high = mid;

    At the very end, we're left with a single element that and low == high.
    We just return that.

    This is essentially "lower_bound" implementation.

*/

/* Time  Beats: 56.86% */
/* Space Beats: 94.06% */

/* Time  Complexity: O(logN) */
/* Space Complexity: O(1)    */
class Solution {
public:
    int guessNumber(int n)
    {
        /* Lower Bound */
        int low  = 1;
        int high = n;

        int my_guess;
        while (low < high)
        {
            int mid = low + (high - low) / 2;

            my_guess = guess(mid);

            if (my_guess == 1) // pick > mid
                low  = mid + 1;
            else
                high = mid;
        }

        return low; // Or "high", it does NOT matter
    }
};
