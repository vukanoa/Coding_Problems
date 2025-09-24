/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    2580) Count Ways to Group Overlapping Ranges
    ============================================

    ============
    Description:
    ============

    You are given a 2D integer array ranges where ranges[i] = [starti, endi]
    denotes that all integers between starti and endi (both inclusive) are
    contained in the ith range.

    You are to split ranges into two (possibly empty) groups such that:

        + Each range belongs to exactly one group.
        + Any two overlapping ranges must belong to the same group.

    Two ranges are said to be overlapping if there exists at least one integer
    that is present in both ranges.

        + For example, [1, 3] and [2, 5] are overlapping because 2 and 3 occur
          in both ranges.

    Return the total number of ways to split ranges into two groups. Since the
    answer may be very large, return it modulo 10^9 + 7.

    =====================================================
    FUNCTION: int countWays(vector<vector<int>>& ranges);
    =====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: ranges = [[6,10],[5,15]]
    Output: 2
    Explanation:
    The two ranges are overlapping, so they must be in the same group.
    Thus, there are two possible ways:
    - Put both the ranges together in group 1.
    - Put both the ranges together in group 2.

    --- Example 2 ---
    Input: ranges = [[1,3],[10,20],[2,5],[4,8]]
    Output: 4
    Explanation:
    Ranges [1,3], and [2,5] are overlapping. So, they must be in the same group.
    Again, ranges [2,5] and [4,8] are also overlapping. So, they must also be in the same group.
    Thus, there are four possible ways to group them:
    - All the ranges in group 1.
    - All the ranges in group 2.
    - Ranges [1,3], [2,5], and [4,8] in group 1 and [10,20] in group 2.
    - Ranges [1,3], [2,5], and [4,8] in group 2 and [10,20] in group 1.


    *** Constraints ***
    1 <= ranges.length <= 10^5
    ranges[i].length == 2
    0 <= starti <= endi <= 10^9

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 40.43% */
/* Space Beats: 79.78% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
private:
    const int MOD = 1e9 + 7;

public:
    int countWays(vector<vector<int>>& ranges)
    {
        const int N = ranges.size();
        const int MOD = 1e9 + 7;
        long long result = 1LL;

        /* Sort */
        sort(ranges.begin(), ranges.end());

        int groups = 1;
        int end = ranges[0][1];
        for (int i = 1; i < N; i++)
        {
            if (end < ranges[i][0]) // New group
                groups++;

            end = max(end, ranges[i][1]);
        }

        return modular_exponentiation(2, groups);
    }

private:
    long long modular_exponentiation(long long base, long long exponent)
    {
        long long result = 1;
        base %= MOD;

        while (exponent > 0)
        {
            // If the current LSB is set(i.e. 1)
            if (exponent & 1)
                result = (result * base) % MOD;

            base = (base * base) % MOD;

            // Right Shift
            exponent >>= 1;
        }

        return result;
    }
};
