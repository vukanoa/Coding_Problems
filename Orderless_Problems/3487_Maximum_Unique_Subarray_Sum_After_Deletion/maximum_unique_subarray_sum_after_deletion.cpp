/*
    ============
    === EASY ===
    ============

    ================================================
    3487) Maximum Unique Subarray Sum After Deletion
    ================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    You are allowed to delete any number of elements from nums without making
    it empty. After performing the deletions, select a

    of nums such that:

        + All elements in the subarray are unique.
        + The sum of the elements in the subarray is maximized.

    Return the maximum sum of such a subarray.

    ========================================
    FUNCTION: int maxSum(vector<int>& nums);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4,5]
    Output: 15
    Explanation: Select the entire array without deleting any element to obtain
                 the maximum sum.

    --- Example 2 ---
    Input: nums = [1,1,0,1,1]
    Output: 1
    Explanation: Delete the element nums[0] == 1, nums[1] == 1, nums[2] == 0,
                 and nums[3] == 1. Select the entire array [1] to obtain the
                 maximum sum.

    --- Example 3 ---
    Input: nums = [1,2,-1,-2,1,0,-1]
    Output: 3
    Explanation: Delete the elements nums[2] == -1 and nums[3] == -2, and
                 select the subarray [2, 1] from [1, 2, 1, 0, -1] to obtain the
                 maximum sum.


    *** Constraints ***
    1 <= nums.length <= 100
    -100 <= nums[i] <= 100

*/

#include <algorithm>
#include <numeric>
#include <unordered_set>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   0.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxSum(vector<int>& nums)
    {
        unordered_set<int> positives;

        const int N = nums.size();

        bool all_negatives = true;
        for (int i = 0; i < N; i++)
        {
            if (nums[i] > 0)
            {
                positives.insert(nums[i]);
                all_negatives = false;
            }
        }

        if (all_negatives)
            return *max_element(nums.begin(), nums.end());

        vector<int> vec(positives.begin(), positives.end());

        return accumulate(vec.begin(), vec.end(), 0);
    }
};
