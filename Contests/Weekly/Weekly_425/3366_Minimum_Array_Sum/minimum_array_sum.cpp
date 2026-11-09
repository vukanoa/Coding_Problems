/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3366) Minimum Array Sum
    ===========================

    ============
    Description:
    ============

    You are given an integer array nums and three integers k, op1, and op2.

    You can perform the following operations on nums:

        + Operation 1: Choose an index i and divide nums[i] by 2, rounding up
                       to the nearest whole number. You can perform this
                       operation at most op1 times, and not more than once per
                       index.

        + Operation 2: Choose an index i and subtract k from nums[i], but only
                       if nums[i] is greater than or equal to k. You can
                       perform this operation at most op2 times, and not more
                       than once per index.

    Note: Both operations can be applied to the same index, but at most once
    each.

    Return the minimum possible sum of all elements in nums after performing
    any number of operations.

    ======================================================================
    FUNCTION: int minArraySum(vector<int>& nums, int k, int op1, int op2);
    ======================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,8,3,19,3], k = 3, op1 = 1, op2 = 1
    Output: 23
    Explanation:
        Apply Operation 2 to nums[1] = 8, making nums[1] = 5.
        Apply Operation 1 to nums[3] = 19, making nums[3] = 10.
        The resulting array becomes [2, 5, 3, 10, 3], which has the minimum
        possible sum of 23 after applying the operations.


    --- Example 2 ---
    Input: nums = [2,4,3], k = 3, op1 = 2, op2 = 1
    Output: 3
    Explanation:
        Apply Operation 1 to nums[0] = 2, making nums[0] = 1.
        Apply Operation 1 to nums[1] = 4, making nums[1] = 2.
        Apply Operation 2 to nums[2] = 3, making nums[2] = 0.
        The resulting array becomes [1, 2, 0], which has the minimum possible
        sum of 3 after applying the operations.



    *** Constraints ***
    1 <= nums.length <= 100
    0 <= nums[i] <= 10^5
    0 <= k <= 10^5
    0 <= op1, op2 <= nums.length

*/

#include <climits>
#include <cmath>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 33.19% */
/* Space Beats: 84.28% */

/* Time  Complexity: O(N^3) */
/* Space Complexity: O(N^3) */
class Solution_Top_Down__Memoization {
private:
    int memo[101][101][101];
    
public:
    int minArraySum(vector<int>& nums, int k, int op1, int op2)
    {
        const int N = nums.size();
        
        /* Memset */
        memset(memo, 0xff, sizeof(memo));

        /* SOlve */
        return solve(0, op1, op2, nums, k);
    }

private:
    int solve(int idx, int rem_op1, int rem_op2, vector<int>& nums, int k)
    {
        const int N = nums.size();

        if (idx == N)
            return 0;

        if (memo[idx][rem_op1][rem_op2] != -1)
            return memo[idx][rem_op1][rem_op2];


        // Skip
        int skip = nums[idx] + solve(idx+1, rem_op1, rem_op2, nums, k);
        
        // Take
        int take_one     = INT_MAX;
        int take_two     = INT_MAX;
        int take_one_two = INT_MAX;
        int take_two_one = INT_MAX;

        if (rem_op1 > 0)
        {
            int reduced_val = static_cast<int>(ceil(1.0 * nums[idx] / 2));

            take_one    = reduced_val + solve(idx+1, rem_op1-1, rem_op2  , nums, k);
        }

        if (rem_op2 > 0 && nums[idx] >= k)
        {
            int reduced_val = (nums[idx] - k);

            take_two    = reduced_val + solve(idx+1, rem_op1  , rem_op2-1, nums, k);
        }

        if ((rem_op1 > 0 && rem_op2 > 0) && (static_cast<int>(ceil(1.0 * nums[idx] / 2)) >= k))
        {
            int reduced_val = (static_cast<int>(ceil(1.0 * nums[idx] / 2)) - k);

            take_one_two = reduced_val + solve(idx+1, rem_op1-1, rem_op2-1, nums, k);
        }


        if ((rem_op1 > 0 && rem_op2 > 0) && (nums[idx] >= k))
        {
            int reduced_val = (static_cast<int>(ceil(1.0 * (nums[idx] - k) / 2)));

            take_two_one = reduced_val + solve(idx+1, rem_op1-1, rem_op2-1, nums, k);
        }

        return memo[idx][rem_op1][rem_op2] = min( {skip, take_one, take_two, take_one_two, take_two_one} );
    }
};
