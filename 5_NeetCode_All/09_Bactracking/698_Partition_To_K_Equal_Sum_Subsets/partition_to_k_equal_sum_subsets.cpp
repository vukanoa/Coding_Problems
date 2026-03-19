/*
    ==============
    === MEDIUM ===
    ==============

    =====================================
    698) Partition to K Equal Sum Subsets
    =====================================

    ============
    Description:
    ============

    Given an integer array nums and an integer k, return true if it is possible
    to divide this array into k non-empty subsets whose sums are all equal.

    ==================================================================
    FUNCTION: bool canPartitionSubsets(std::vector<int>& nums, int k);
    ==================================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [4,3,2,3,5,2,1], k = 4
    Output: true
    Explanation: It is possible to divide it into 4 subsets (5), (1, 4), (2,3),
    (2,3) with equal sums.

    --- Example 2 ---
    Input: nums = [1,2,3,4], k = 3
    Output: false

    *** Constraints ***
    1 <= k <= nums.length <= 16
    1 <= nums[i] <= 104
    The frequency of each element is in the range [1, 4].

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

/* Time  Beats: 12.49% */
/* Space Beats: 77.37% */

/* Time  Complexity: O(k^N) */
/* Space Complexity: O(N)   */
class Solution {
public:
    bool canPartitionKSubsets(vector<int>& nums, int k)
    {
        int sum = accumulate(nums.begin(), nums.end(), 0);

        if (sum % k)
            return false;

        /* Sort in DESCENDING order */
        sort(nums.begin(), nums.end(), greater<int>());

        vector<bool> used(nums.size(), false);

        return backtracking(nums, 0, k, 0, used, sum / k);
    }

private:
    bool backtracking(vector<int>& nums, int start, int k, int subset_sum, vector<bool>& used, int target)
    {
        if (k == 0)
            return true;

        if (subset_sum == target)
            return backtracking(nums, 0, k-1, 0, used, target);

        const int N = nums.size();
        for (int idx = start; idx < N; idx++)
        {
            if (used[idx] || subset_sum + nums[idx] > target)
                continue;

            used[idx] = true;

            if (backtracking(nums, idx + 1, k, subset_sum + nums[idx], used, target))
                return true;

            used[idx] = false;
        }

        return false;
    }
};
