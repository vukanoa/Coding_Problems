/*
    ============
    === HARD ===
    ============

    ==============================
    3886) Sum of SOrtable Integers
    ==============================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    An integer k is called sortable if k divides n and you can sort nums in
    non-decreasing order by sequentially performing the following operations:

        + Partition nums into consecutive of length k.

        + Cyclically rotate each subarray independently any number of times to
          the left or to the right.

    Return an integer denoting the sum of all possible sortable integers k.

    ==================================================
    FUNCTION: int sortableIntegers(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,2]
    Output: 3
    Explanation:
        For n = 3, possible divisors are 1 and 3.
        For k = 1: each subarray has one element. No rotation can sort the array.
        For k = 3: the single subarray [3, 1, 2] can be rotated once to produce [1, 2, 3], which is sorted.
        Only k = 3 is sortable. Hence, the answer is 3.

    --- Example 2 ---
    Input: nums = [7,6,5]
    Output: 0
    Explanation:
        For n = 3, possible divisors are 1 and 3.
        For k = 1: each subarray has one element. No rotation can sort the array.
        For k = 3: the single subarray [7, 6, 5] cannot be rotated into non-decreasing order.
        No k is sortable. Hence, the answer is 0.

    --- Example 3 ---
    Input: nums = [5,8]
    Output: 3
    Explanation:
        For n = 2, possible divisors are 1 and 2.
        Since [5, 8] is already sorted, every divisor is sortable. Hence, the answer is 1 + 2 = 3.


    *** Constraints ***
    1 <= n == nums.length <= 10^5
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

/* Time  Beats: 83.82% */
/* Space Beats: 55.49% */

/* Time  Complexity: O(N * sqrt(N)) */
/* Space Complexity: O(1)           */
class Solution {
public:
    int sortableIntegers(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;
        
        for (int k = 1; k <= N; k++)
        {
            if (N % k != 0)
                continue;

            if (check(nums, k))
                result += k;
        }

        return result;
    }

private:
    bool check(vector<int>& nums, int k_length)
    {
        const int N = nums.size();
        int prev_max = 0;
        
        for (int i = 0; i < N; i += k_length)
        {
            if (nums[i] < prev_max)
                return false;
            
            int curr_max    = nums[i];
            bool dip_exists = false;
            
            for (int j = i+1; j < i+k_length; j++)
            {
                if (nums[j] < prev_max)
                    return false;
                
                if (nums[j-1] > nums[j])
                {
                    if (dip_exists)
                        return false; // Since it's a SECOND dip in this subarr

                    dip_exists = true;
                }
                
                curr_max = max(curr_max, nums[j]);
            }
            
            // If rotated, last must be <= first
            if (dip_exists)
            {
                // First   &   Last       within this subarray
                //  |           |
                //  |__         |
                //    |         |
                //    v         v
                if (nums[i] < nums[i + k_length - 1])
                    return false;
            }
            // If dip does NOT exist, then that means current subarray is
            // ALREADY sorted in NON-decreasing order
            
            prev_max = curr_max;
        }
        
        return true;
    }
};
