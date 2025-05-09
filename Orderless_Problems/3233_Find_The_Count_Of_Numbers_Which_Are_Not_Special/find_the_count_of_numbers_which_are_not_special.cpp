/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3233) Find the Count of Numbers which are not special
    =====================================================

    ============
    Description:
    ============

    You are given 2 positive integers l and r. For any number x, all positive
    divisors of x except x are called the proper divisors of x.

    A number is called special if it has exactly 2 proper divisors.
    For example:

        The number 4 is special because it has proper divisors 1 and 2.
        The number 6 is not special because it has proper divisors 1, 2, and 3.

    Return the count of numbers in the range [l, r] that are not special.

    ============================================
    FUNCTION: int nonSpecialCount(int l, int r);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: l = 5, r = 7
    Output: 3
    Explanation:
    There are no special numbers in the range [5, 7].

    --- Example 2 ---
    Input: l = 4, r = 16
    Output: 11
    Explanation:
    The special numbers in the range [4, 16] are 4 and 9.


    *** Constraints ***
    1 <= l <= r <= 10^9

*/

#include <cmath>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 27.03% */
/* Space Beats: 68.03% */

/* Time  Complexity: O(sqrt(r)) */
/* Space Complexity: O(sqrt(r)) */
class Solution {
public:
    int nonSpecialCount(int l, int r)
    {
        vector<bool> prime(sqrt(r) + 1, true);
        prime[0] = false;
        prime[1] = false;

        for (int num = 2; num * num <= sqrt(r); num++)
        {
            if ( ! prime[num])
                continue;

            for (int i = num * num; i <= sqrt(r); i += num)
                prime[i] = false;
        }

        int special = 0;
        for (int num = 2; num <= sqrt(r); num++)
        {
            if ( ! prime[num])
                continue;

            int square = num * num;
            if (l <= square && square <= r)
                special++;
        }

        int total = r - l + 1;

        return total - special;
    }
};
