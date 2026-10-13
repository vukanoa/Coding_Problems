/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    3788) Maximum Score of a Split
    ==============================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    Choose an index i such that 0 <= i < n - 1.

    For a chosen split index i:

        + Let prefixSum(i) be the sum of nums[0] + nums[1] + ... + nums[i].

        + Let suffixMin(i) be the minimum value among nums[i + 1], nums[i + 2],
          ..., nums[n - 1].

    The score of a split at index i is defined as:

    score(i) = prefixSum(i) - suffixMin(i)

    Return an integer denoting the maximum score over all valid split indices.

    ====================================================
    FUNCTION: long long maximumScore(vector<int>& nums);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [10,-1,3,-4,-5]
    Output: 17
    Explanation:
    The optimal split is at i = 2, score(2) = prefixSum(2) - suffixMin(2) = (10
    + (-1) + 3) - (-5) = 17.

    --- Example 2 ---
    Input: nums = [-7,-5,3]
    Output: -2
    Explanation:
    The optimal split is at i = 0, score(0) = prefixSum(0) - suffixMin(0) =
    (-7) - (-5) = -2.

    --- Example 3 ---
    Input: nums = [1,1]
    Output: 0
    Explanation:
    The only valid split is at i = 0, score(0) = prefixSum(0) - suffixMin(0) =
    1 - 1 = 0.


    *** Constraints ***
    2 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^`9

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 42.27% */
/* Space Beats: 53.64% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    long long maximumScore(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = LLONG_MIN;

        vector<long long> suffix_min(N, INT_MAX);
        suffix_min[N-1] = 1LL * nums[N-1];

        for (int i = N-2; i >= 0; i--)
            suffix_min[i] = min(1LL * nums[i], suffix_min[i+1]);

        long long prefix_sum = 0;
        for (int i = 0; i < N-1; i++)
        {
            prefix_sum += nums[i];
            result = max(result, prefix_sum - suffix_min[i+1]);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Space Efficient, same idea.

*/

/* Time  Beats: 80.91% */
/* Space Beats: 91.82% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Space_Efficient {
public:
    long long maximumScore(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = nums[0] - nums[1];

        long long prefix_sum = 0LL;
        long long suffix_min = nums[N - 1];

        for(int i = 0; i < N - 1; i++)
            prefix_sum += nums[i];

        for (int i = N-2; i >= 0; i--)
        {
            result = max(result, prefix_sum - suffix_min);

            suffix_min  = min(suffix_min, 1LL * nums[i]);
            prefix_sum -= nums[i];
        }

        return result;
    }
};
