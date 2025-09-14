/*
    ============
    === EASY ===
    ============

    =================================================
    3684) Maximize Sum of At Most K Distinct Elements
    =================================================

    ============
    Description:
    ============

    You are given a positive integer array nums and an integer k.

    Choose at most k elements from nums so that their sum is maximized.
    However, the chosen numbers must be distinct.

    Return an array containing the chosen numbers in strictly descending order.

    =============================================================
    FUNCTION: vector<int> maxKDistinct(vector<int>& nums, int k);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [84,93,100,77,90], k = 3
    Output: [100,93,90]
    Explanation:
    The maximum sum is 283, which is attained by choosing 93, 100 and 90. We
    rearrange them in strictly descending order as [100, 93, 90].

    --- Example 2 ---
    Input: nums = [84,93,100,77,93], k = 3
    Output: [100,93,84]
    Explanation:
    The maximum sum is 277, which is attained by choosing 84, 93 and 100. We
    rearrange them in strictly descending order as [100, 93, 84]. We cannot
    choose 93, 100 and 93 because the chosen numbers must be distinct.

    --- Example 3 ---
    Input: nums = [1,1,1,2,2,2], k = 6
    Output: [2,1]
    Explanation:
    The maximum sum is 3, which is attained by choosing 1 and 2. We rearrange
    them in strictly descending order as [2, 1].

    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 10^9
    1 <= k <= nums.length

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 50.00% */
/* Space Beats: 60.00% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N + logN) */ // logN is TC of C++'s Sort
class Solution {
public:
    vector<int> maxKDistinct(vector<int>& nums, int k)
    {
        const int N = nums.size();
        vector<int> result;

        /* Sort */
        sort(nums.begin(), nums.end(), greater<int>());

        result.push_back(nums[0]);
        for (int i = 1; i < N; i++)
        {
            if (result.size() == k)
                break;

            if (result.back() == nums[i])
                continue;

            result.push_back(nums[i]);
        }

        return result;
    }
};
