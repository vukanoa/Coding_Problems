/*
    ============
    === EASY ===
    ============

    ====================================================
    2016) Maximum Difference Between Increasing Elements
    ====================================================

    ============
    Description:
    ============

    Given a 0-indexed integer array nums of size n, find the maximum difference
    between nums[i] and nums[j] (i.e., nums[j] - nums[i]), such that
    0 <= i < j < n and nums[i] < nums[j].

    Return the maximum difference. If no such i and j exists, return -1.

    ===================================================
    FUNCTION: int maximumDifference(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [7,1,5,4]
    Output: 4
    Explanation:
    The maximum difference occurs with i = 1 and j = 2,
    nums[j] - nums[i] = 5 - 1 = 4.
    Note that with i = 1 and j = 0,
    the difference nums[j] - nums[i] = 7 - 1 = 6, but i > j, so it is not valid.

    --- Example 2 ---
    Input: nums = [9,4,3,2]
    Output: -1
    Explanation:
    There is no i and j such that i < j and nums[i] < nums[j].

    --- Example 3 ---
    Input: nums = [1,5,2,10]
    Output: 9
    Explanation:
    The maximum difference occurs with i = 0 and j = 3,
    nums[j] - nums[i] = 10 - 1 = 9.


    *** Constraints ***
    n == nums.length
    2 <= n <= 1000
    1 <= nums[i] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   5.67% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maximumDifference(vector<int>& nums)
    {
        const int N = nums.size();
        int result = -1;

        vector<int> max_right(N, 0);
        max_right[N-1] = nums.back();

        for (int i = N-2; i >= 0; i--)
            max_right[i] = max(nums[i], max_right[i+1]);

        int min_left = nums[0];
        for (int i = 1; i < N; i++)
        {
            if (min_left < max_right[i])
                result = max(result, max_right[i] - min_left);

            min_left = min(min_left, nums[i]);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    If you look closely, we don't really need vector max_right, instead we can
    update our min_left as we go.

    Each time current min_left is strictly SMALLER than nums[i], we try to
    update our result.

    Otherwise, it's certain the nums[i] is LESS THAN OR EQUALS to min_left,
    therefore we update min_left.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  71.76% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Optimized {
public:
    int maximumDifference(vector<int>& nums)
    {
        const int N = nums.size();
        int result = -1;

        int min_left = nums[0];
        for (int i = 1; i < N; ++i)
        {
            if (min_left < nums[i])
                result = max(result, nums[i] - min_left);
            else
                min_left = nums[i]; // It's LESS THAN OR EQUAL to current min
        }

        return result;
    }
};
