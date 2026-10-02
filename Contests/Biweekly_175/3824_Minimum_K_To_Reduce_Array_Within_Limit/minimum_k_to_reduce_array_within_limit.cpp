/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    3824) Minimum K to Reduce Array Within Limit
    ============================================

    ============
    Description:
    ============

    You are given a positive integer array nums.

    For a positive integer k, define nonPositive(nums, k) as the minimum number
    of operations needed to make every element of nums non-positive. In one
    operation, you can choose an index i and reduce nums[i] by k.

    Return an integer denoting the minimum value of k such that
    nonPositive(nums, k) <= k2.

    ==========================================
    FUNCTION: int minimumK(vector<int>& nums);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [3,7,5]
    Output: 3
    Explanation:
    When k = 3, nonPositive(nums, k) = 6 <= k2.
        Reduce nums[0] = 3 one time. nums[0] becomes 3 - 3 = 0.
        Reduce nums[1] = 7 three times. nums[1] becomes 7 - 3 - 3 - 3 = -2.
        Reduce nums[2] = 5 two times. nums[2] becomes 5 - 3 - 3 = -1.

    --- Example 2 ---
    Input: nums = [1]
    Output: 1
    Explanation:
    When k = 1, nonPositive(nums, k) = 1 <= k2.
        Reduce nums[0] = 1 one time. nums[0] becomes 1 - 1 = 0.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^5

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simple Binary search on "result range". This is a fundamental "Koko Eating
    Bananas", i.e. Binary Search problem.

*/

/* Time  Beats: 83.27% */
/* Space Beats: 35.06% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int minimumK(vector<int>& nums)
    {
        const int N = nums.size();

        int low = 1;
        int high = 1e5;

        while (low < high)
        {
            long long mid_k = low + (high - low) / 2; // Low-leaning mid

            if (operations(nums, mid_k) <= (mid_k * mid_k))
                high = mid_k;
            else
                low  = mid_k + 1;
        }

        return low; // Or "high" it does NOT matter
    }

private:
    int operations(vector<int>& nums, long long k)
    {
        const int N = nums.size();
        int result = 0;
        
        for (int i = 0; i < N; i++)
            result += (nums[i] + k - 1) / k;

        return result;
    }
};
