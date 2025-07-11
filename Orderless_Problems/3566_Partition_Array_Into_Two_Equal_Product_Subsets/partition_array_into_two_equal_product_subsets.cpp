/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    3566) Partition Array Into Two Equal Product Subsets
    ====================================================

    ============
    Description:
    ============

    You are given an integer array nums containing distinct positive integers
    and an integer target.

    Determine if you can partition nums into two non-empty disjoint subsets,
    with each element belonging to exactly one subset, such that the product
    of the elements in each subset is equal to target.

    Return true if such a partition exists and false otherwise.
    A subset of an array is a selection of elements of the array. 

    =========================================================================
    FUNCTION: bool checkEqualPartitions(vector<int>& nums, long long target);
    =========================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,1,6,8,4], target = 24
    Output: true
    Explanation: The subsets [3, 8] and [1, 6, 4] each have a product of 24.
                 Hence, the output is true.

    --- Example 2 ---
    Input: nums = [2,5,3,7], target = 15
    Output: false
    Explanation: There is no way to partition nums into two non-empty disjoint
                 subsets such that both subsets have a product of 15. Hence,
                 the output is false.


    *** Constraints ***
    3 <= nums.length <= 12
    1 <= target <= 10^15
    1 <= nums[i] <= 100
    All elements of nums are distinct.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 29.42% */
/* Space Beats: 46.47% */

/* Time  Complexity: O(2^N * N) */
/* Space Complexity: O(1)       */
class Solution {
public:
    static bool checkEqualPartitions(vector<int>& nums, long long target)
    {
        const int N = nums.size();
        const int max_bitmask = (1 << N) - 1;

        for (int curr_mask = 1; curr_mask <= max_bitmask; curr_mask++)
        {
            unsigned long long product_in_first_partition  = 1;
            unsigned long long product_in_second_partition = 1;

            for (int idx = 0; idx < N; idx++)
            {
                if ((curr_mask >> idx) & 1)
                    product_in_first_partition *= nums[idx];
                else
                    product_in_second_partition *= nums[idx];
            }

            if (product_in_first_partition == target && product_in_second_partition == target)
                return 1;
        }

        return 0;
    }
};
