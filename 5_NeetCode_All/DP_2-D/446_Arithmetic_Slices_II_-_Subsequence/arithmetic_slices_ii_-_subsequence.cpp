#include <iostream>
#include <vector>

/*
    ============
    === HARD ===
    ============

    =======================================
    446) Arithmetic Slices II - Subsequence
    =======================================

    ============
    Description:
    ============

    Given an integer array nums, return the number of all the arithmetic
    subsequences of nums.

    A sequence of numbers is called arithmetic if it consists of at least three
    elements and if the difference between any two consecutive elements is the
    same.

        + For example, [1, 3, 5, 7, 9], [7, 7, 7, 7], and [3, -1, -5, -9] are
          arithmetic sequences.

        + For example, [1, 1, 2, 5, 7] is not an arithmetic sequence.

    A subsequence of an array is a sequence that can be formed by removing some
    elements (possibly none) of the array.

        For example, [2,5,10] is a subsequence of [1,2,1,2,4,1,5,10].

    The test cases are generated so that the answer fits in 32-bit integer.

    ==========================================================
    FUNCTION: int numberOfArithmeticSlices(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,4,6,8,10]
    Output: 7
    Explanation: All arithmetic subsequence slices are:
    [2,4,6]
    [4,6,8]
    [6,8,10]
    [2,4,6,8]
    [4,6,8,10]
    [2,4,6,8,10]
    [2,6,10]


    --- Example 2 ---
    Input: nums = [7,7,7,7,7]
    Output: 16
    Explanation: Any subsequence of this array is arithmetic.


    *** Constraints ***
    1  <= nums.length <= 1000
    -2^31 <= nums[i] <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 78.76% */
/* Space Beats: 67.98% */

/* Time  Complexity: O(n^2) */
/* Space Complexity: O(n^2) */
class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums)
    {
        long long n = nums.size();
        if (n <= 2)
            return 0;

        long long result = 0 ;
        unordered_map<long long,long long> dp[n+1];

        for (long long i = 1 ; i < n ; i++)
        {
            for (long long j = 0 ; j<i ; j++)
            {
                long long cnt = 1;
                long long diff = (long long)nums[i] - (long long)nums[j];

                // agr diff ke sath ek length alredy present hai to
                if (dp[j].count(diff))
                {
                   cnt = dp[j][diff];
                   dp[i][diff]+= cnt;
                   result += cnt;
                }

                dp[i][diff] += 1 ;  // 1 + to add curr element
            }
        }

        return result;
    }
};
