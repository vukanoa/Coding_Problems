/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    2874) Maximum Value of an Ordered Triplet II
    ============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums.

    Return the maximum value over all triplets of indices (i, j, k) such that
    i < j < k. If all such triplets have a negative value, return 0.

    The value of a triplet of indices (i, j, k) is equal to
    (nums[i] - nums[j]) * nums[k].

    ===========================================================
    FUNCTION: long long maximumTripletValue(vector<int>& nums);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [12,6,1,2,7]
    Output: 77
    Explanation: The value of the triplet (0, 2, 4) is
                 (nums[0] - nums[2]) * nums[4] = 77. It can be shown that there
                 are no ordered triplets of indices with a value greater than
                 77.


    --- Example 2 ---
    Input: nums = [1,10,3,4,19]
    Output: 133
    Explanation: The value of the triplet (1, 2, 4) is
                 (nums[1] - nums[2]) * nums[4] = 133. It can be shown that
                 there are no ordered triplets of indices with a value greater
                 than 133.


    --- Example 3 ---
    Input: nums = [1,2,3]
    Output: 0
    Explanation: The only ordered triplet of indices (0, 1, 2) has a negative
                 value of (nums[0] - nums[1]) * nums[2] = -3. Hence, the answer
                 would be 0.


    *** Constraints ***
    3 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is a famous "trick" when you're asked to do something with triplets
    such that:

        i < j < k

    You iterate only with 'j' pointer, and the remaining two are pre-calculated


    Similar thing is true for when you have quadruplets such that:

        i < j < k < m

    However, this one can't be done in O(N), but it CAN be done in O(N^2) which
    is an optimization of order O(N^2) as well.

    Here you'd fix 'j' and 'k' and you'd pre-calculate 'i' and 'm'.


    This is a fundamental trick for these kinds of problems.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  12.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Greedy_and_Prefix_Sum {
public:
    long long maximumTripletValue(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0;

        vector<int> left_max(N);
        vector<int> right_max(N);

        for (int i = 1; i < N; i++)
        {
            left_max[i]        = max(left_max[i - 1],  nums[i - 1]);
            right_max[N-1 - i] = max(right_max[N - i], nums[N - i]);
        }

        for (int j = 1; j < N-1; j++)
            result = max(result, 1LL * (left_max[j] - nums[j]) * right_max[j]);

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is a standard "triplet trick". Essentially fix the middle one and
    iterate calculate the other two along the way.

    However, this is one Optimization on top of that. We don't need to have an
    additional two vectors of size N, instead we just keep track of the
    "left_max" and "diff_max" as we go and calculate the "result".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  97.21% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long maximumTripletValue(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0;

        long long left_max = 0;
        long long diff_max = 0;

        for (int idx = 0; idx < N; idx++)
        {
            result = max(result, 1LL * (diff_max * nums[idx]));

            diff_max = max(diff_max, 1LL * (left_max - nums[idx]));
            left_max = max(left_max, 1LL * nums[idx]);
        }

        return result < 0 ? 0 : result;
    }
};
