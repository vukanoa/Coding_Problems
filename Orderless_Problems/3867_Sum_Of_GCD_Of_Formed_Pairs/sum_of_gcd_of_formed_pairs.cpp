/*
    ==============
    === MEDIUM ===
    ==============

    ================================
    3867) Sum of GCD of Formed Pairs
    ================================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    Construct an array prefixGcd where for each index i:

        Let mxi = max(nums[0], nums[1], ..., nums[i]).
        prefixGcd[i] = gcd(nums[i], mxi).

    After constructing prefixGcd:

        + Sort prefixGcd in non-decreasing order.

        + Form pairs by taking the smallest unpaired element and the largest
          unpaired element.

        + Repeat this process until no more pairs can be formed.

        + For each formed pair, compute the gcd of the two elements.

        + If n is odd, the middle element in the prefixGcd array remains
          unpaired and should be ignored.

    Return an integer denoting the sum of the GCD values of all formed pairs.
    The term gcd(a, b) denotes the greatest common divisor of a and b. 

    ==============================================
    FUNCTION: long long gcdSum(vector<int>& nums);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,6,4]
    Output: 2

    --- Example 2 ---
    Input: nums = [3,6,2,8]
    Output: 5

    --- Example 3 ---

    *** Constraints ***
    1 <= n == nums.length <= 10^5
    1 <= nums[i] <= 10^9

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

/* Time  Beats: 43.32% */
/* Space Beats: 75.58% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long gcdSum(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0LL;

        vector<int> prefixGcd(N, 0);
        int max_so_far = 0;
        for (int i = 0; i < N; i++)
        {
            max_so_far = max(max_so_far, nums[i]);

            prefixGcd[i] = gcd(nums[i], max_so_far);
        }

        /* Sort */
        sort(prefixGcd.begin(), prefixGcd.end());

        int L = 0;
        int R = N-1;

        while (L < R)
        {
            result += 1LL * gcd(prefixGcd[L], prefixGcd[R]);

            L++;
            R--;
        }

        return result;
    }
};
