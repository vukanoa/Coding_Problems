/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    2587) Rearrange Array to Maximize Prefix Score
    ==============================================

    ============
    Description:
    ============

    You are given a 0-indexed integer array nums. You can rearrange the
    elements of nums to any order (including the given order).

    Let prefix be the array containing the prefix sums of nums after
    rearranging it. In other words, prefix[i] is the sum of the elements from
    0 to i in nums after rearranging it. The score of nums is the number of
    positive integers in the array prefix.

    Return the maximum score you can achieve.

    ==========================================
    FUNCTION: int maxScore(vector<int>& nums);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,-1,0,1,-3,3,-3]
    Output: 6
    Explanation: We can rearrange the array into nums = [2,3,1,-1,-3,0,-3].
    prefix = [2,5,6,5,2,2,-1], so the score is 6.
    It can be shown that 6 is the maximum score we can obtain.

    --- Example 2 ---
    Input: nums = [-2,-3,0]
    Output: 0
    Explanation: Any rearrangement of the array will result in a score of 0.


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^6 <= nums[i] <= 10^6

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

/* Time  Beats: 72.07% */
/* Space Beats: 54.11% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // O(logN) is Time Complexity of C++'s Sort
class Solution {
public:
    int maxScore(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        /* Sort */
        sort(nums.begin(), nums.end());

        /* Reverse */
        reverse(nums.begin(), nums.end());

        if (nums[0] <= 0)
            return 0;

        result = 1;
        long long prefix_sum = nums[0];
        for (int i = 1; i < N; i++)
        {
            prefix_sum += nums[i];
            if (prefix_sum > 0)
                result++;
        }

        return result;
    }
};
