/*
    ==============
    === MEDIUM ===
    ==============

    ========================================
    3727) Maximum Alternating Sum of Squares
    ========================================

    ============
    Description:
    ============

    You are given an integer array nums. You may rearrange the elements in any order.

    The alternating score of an array arr is defined as:

        score = arr[0]^2 - arr[1]^2 + arr[2]^2 - arr[3]^2 + ...

    Return an integer denoting the maximum possible alternating score of nums
    after rearranging its elements.

    =========================================================
    FUNCTION: long long maxAlternatingSum(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: 12
    Explanation:
    A possible rearrangement for nums is [2,1,3], which gives the maximum
    alternating score among all possible rearrangements.
    The alternating score is calculated as:
    score = 22 - 12 + 32 = 4 - 1 + 9 = 12

    --- Example 2 ---
    Input: nums = [1,-1,2,-2,3,-3]
    Output: 16
    Explanation:
    A possible rearrangement for nums is [-3,-1,-2,1,3,2], which gives the
    maximum alternating score among all possible rearrangements.
    The alternating score is calculated as:
    score = (-3)2 - (-1)2 + (-2)2 - (1)2 + (3)2 - (2)2 = 9 - 1 + 4 - 1 + 9 - 4 = 16


    *** Constraints ***
    1 <= nums.length <= 10^5
    -4 * 10^4 <= nums[i] <= 4 * 10^4

*/

#include <algorithm>
#include <cstdlib>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 24.79% */
/* Space Beats: 32.05% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0;

        vector<long long> abs_nums;
        abs_nums.reserve(N);

        for (int i = 0; i < N; i++)
            abs_nums.push_back(abs(nums[i]));

        /* SOrt */
        sort(abs_nums.begin(), abs_nums.end(), greater<int>());

        int L = 0;
        int R = N-1;
        while (L <= R)
        {
            result += abs_nums[L] * abs_nums[L];

            if (L < R)
                result -= abs_nums[R] * abs_nums[R];

            ++L;
            --R;
        }

        return result;
    }
};
