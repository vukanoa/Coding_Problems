/*
    ============
    === EASY ===
    ============

    ======================================
    4010) Maximize Pair Strength using GCD
    ======================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Choose exactly one pair of distinct indices i and j. The strength of the
    pair is defined as (nums[i] * nums[j]) / gcd(nums[i], nums[j])^2.

    Return the maximum strength over all possible pairs.

    =======================================================
    FUNCTION: long long maxPairStrength(vector<int>& nums);
    =======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,5]
    Output: 15
    Explanation:
    Choosing i = 1 and j = 2 gives strength (3 * 5) / gcd(3, 5)2 = 15 / 1 = 15,
    which is the maximum over all pairs.

    --- Example 2 ---
    Input: nums = [4,6,8]
    Output: 12
    Explanation:
    Choosing i = 1 and j = 2 gives strength (6 * 8) / gcd(6, 8)2 = 48 / 4 = 12,
    which is the maximum over all pairs.

    --- Example 3 ---
    Input: nums = [3,3]
    Output: 1
    Explanation:
    Choosing i = 0 and j = 1 gives strength (3 * 3) / gcd(3, 3)2 = 9 / 9 = 1,
    the maximum over all pairs.


    *** Constraints ***
    2 <= nums.length <= 2000
    1 <= nums[i] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 28.35% */
/* Space Beats:  6.40% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long maxPairStrength(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0LL;

        for (int i = 0; i < N-1; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                long long g = iter_gcd(nums[i], nums[j]);

                result = max(result, (1LL * nums[i] * nums[j] / (g*g)));
            }
        }

        return result;
    }

private:
    int iter_gcd(int a, int b)
    {
        while (b != 0)
        {
            int tmp = b;

            b = a % b;
            a = tmp;
        }

        return a;
    }
};
