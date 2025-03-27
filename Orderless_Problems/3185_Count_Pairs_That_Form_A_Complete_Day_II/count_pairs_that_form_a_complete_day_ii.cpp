/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    3185) Count Pairs That Form a Complete Day II
    =============================================

    ============
    Description:
    ============

    Given an integer array hours representing times in hours, return an integer
    denoting the number of pairs i, j where i < j and hours[i] + hours[j] forms
    a complete day.

    A complete day is defined as a time duration that is an exact multiple of
    24 hours.

    For example, 1 day is 24 hours, 2 days is 48 hours, 3 days is 72 hours, and
    so on.

    ==============================================================
    FUNCTION: long long countCompleteDayPairs(vector<int>& hours);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: hours = [12,12,30,24,24]
    Output: 2
    Explanation: The pairs of indices that form a complete day are (0, 1) and (3, 4).

    --- Example 2 ---
    Input: hours = [72,48,24,3]
    Output: 3
    Explanation: The pairs of indices that form a complete day are (0, 1), (0, 2), and (1, 2).


    *** Constraints ***
    1 <= hours.length <= 5 * 10^5
    1 <= hours[i] <= 10^9

*/

#include <unordered_map>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Firs thing you should notice is that we don't care if the pair forms 2, 3
    or 15 whole days, the only thing we care about is that the pair forms ANY
    amount of WHOLE(!!) days.

    That's why we can immediately go through the "hours" vectors and MOD all
    numbers by 24.

    If previously we had:

        hours = [37, 12, 26, 11]

    Now we'll have:

        hours = [13, 12,  2, 11]

    As you have can see, we could make a pair {37, 11} in the initial vector,
    however after the change, we can still take hours[0] and hours[3] to make
    a WHOLE day.

    Now it's:

        {13, 11}

    Which makes a WHOLE day and that's the only thing we care about.

    Also, notice that non-whole day hours[i] will NEVER form a WHOLE day with
    some whole-day hours[j].

    For example:

        13 is NEVER going to form a whole day with 0 or 24 or 48.

    The only way a whole-day hours[i] can form a valid pair is with ANOTHER
    whole-day hours[j].

    That's why in our single pass we'll only try to see if (24 - curr) exists
    already in our "umap_passed" which is essentially a CounterMap.

    It's literally Two-Sum problem. Make sure you know that. It's the very
    first problem on the LeetCode--"LeetCode: 1. Two Sum".


    However while we're iterating, we're counting the number of WHOLE days.
    Why?

    Because we've said that one whole-day hours[i] can make a valid pair ONLY
    with another whole-day hours[j].

    Therefore, once we get the totla number of whole-days in our "hours" vector
    we'll add that to our current result which was gained by working with
    non-whole-days hours[i], as we've already explained.

    But how can we know what is the amount of valid pairs our whole-days can
    make?

    It's simple. If there are X whole-days in "hours" vector, then it's by the
    formula:

        (X-1) * ((X-1) + 1) / 2


    The sum of the first N natural numbers is: N * (N + 1) / 2

    However, we can't use "N", because one pairs is consisted of TWO elements.
    If we had:

        hours = [24, 48, 72]

    How many pairs could we make?

    It's not: 3 * (3 + 1) / 2
    because that's 6.

    Instead it's: (3-1) * ((3-1) + 1) / 2
    because that's 3.

    So the standard formula for calculating the sum of first N natural numbers
    is:

        N * (N + 1) / 2

    However, in our case, N = X - 1.
    Where 'X' is the total number of whole-days in "hours" vector.

*/

/* Time  Beats: 80.91% */
/* Space Beats: 62.11% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long countCompleteDayPairs(vector<int>& hours)
    {
        const int N = hours.size();
        long long  result = 0;

        unordered_map<int,int> umap_passed;
        for (int i = 0; i < N; i++)
        {
            if (hours[i] % 24 != 0)
                hours[i] %= 24;
        }


        long long divisible_by_days = 0;

        if (hours[0] % 24 != 0)
            umap_passed[hours[0]]++;
        else
            divisible_by_days++;

        for (int i = 1; i < N; i++)
        {
            if (hours[i] % 24 == 0)
                divisible_by_days++;
            else
            {
                int target = 24 - hours[i];

                if (umap_passed.find(target) != umap_passed.end())
                    result += umap_passed[target];

                umap_passed[hours[i]]++;
            }
        }

        long long  n = divisible_by_days - 1;
        result += n * (n + 1) / 2;

        return result;
    }
};
