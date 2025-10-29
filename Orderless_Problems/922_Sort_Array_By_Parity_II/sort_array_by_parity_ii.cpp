/*
    ============
    === EASY ===
    ============

    ============================
    922) Sort Array By Parity II
    ============================

    ============
    Description:
    ============

    Given an array of integers nums, half of the integers in nums are odd, and
    the other half are even.

    Sort the array so that whenever nums[i] is odd, i is odd, and whenever
    nums[i] is even, i is even.

    Return any answer array that satisfies this condition.

    =============================================================
    FUNCTION: vector<int> sortArrayByParityII(vector<int>& nums);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,2,5,7]
    Output: [4,5,2,7]
    Explanation: [4,7,2,5], [2,5,4,7], [2,7,4,5] would also have been accepted.

    --- Example 2 ---
    Input: nums = [2,3]
    Output: [2,3]

    --- Example 3 ---

    *** Constraints ***
    2 <= nums.length <= 2 * 10^4
    nums.length is even.
    Half of the integers in nums are even.
    0 <= nums[i] <= 1000

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  94.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums)
    {
        const int N = nums.size();

        int i = 0;
        int j = 1;

        while (i < N && j < N)
        {
            if (nums[i] % 2 == 0)
                i += 2;
            else if (nums[j] % 2 == 1)
                j += 2;
            else
                swap(nums[i], nums[j]);
        }

        return nums;
    }
};
