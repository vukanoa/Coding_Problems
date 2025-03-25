/*
    ============
    === EASY ===
    ============

    ============================================
    3184) Count Pairs That Form a Complete Day I
    ============================================

    ============
    Description:
    ============

    Given an integer array hours representing times in hours, return an integer
    denoting the number of pairs i, j where i < j and hours[i] + hours[j] forms
    a complete day.

    A complete day is defined as a time duration that is an exact multiple of
    24 hours.

    For example, 1 day is 24 hours, 2 days is 48 hours, 3 days is 72 hours,
    and so on.

    ========================================================
    FUNCTION: int countCompleteDayPairs(vector<int>& hours);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: hours = [12,12,30,24,24]
    Output: 2
    Explanation:
    The pairs of indices that form a complete day are (0, 1) and (3, 4).

    --- Example 2 ---
    Input: hours = [72,48,24,3]
    Output: 3
    Explanation:
    The pairs of indices that form a complete day are (0, 1), (0, 2), and (1, 2).


    *** Constraints ***
    1 <= hours.length <= 100
    1 <= hours[i] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Basic Brute-Force.

    Constraints allow it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  47.10% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(1)   */
class Solution {
public:
    int countCompleteDayPairs(vector<int>& hours)
    {
        const int N = hours.size();
        int result = 0;

        for (int i = 0; i < N; i++)
            hours[i] %= 24;

        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                if ((hours[i] + hours[j]) % 24 == 0)
                    result++;
            }
        }

        return result;
    }
};
