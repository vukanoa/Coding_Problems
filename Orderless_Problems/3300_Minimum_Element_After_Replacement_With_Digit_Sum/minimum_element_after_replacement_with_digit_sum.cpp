/*
    ============
    === EASY ===
    ============

    ======================================================
    3300) Minimum Element After Replacement With Digit Sum
    ======================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    You replace each element in nums with the sum of its digits.

    Return the minimum element in nums after all replacements.

    ============================================
    FUNCTION: int minElement(vector<int>& nums);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [10,12,13,14]
    Output: 1
    Explanation: nums becomes [1, 3, 4, 5] after all replacements, with
                 minimum element 1.

    --- Example 2 ---
    Input: nums = [1,2,3,4]
    Output: 1
    Explanation: nums becomes [1, 2, 3, 4] after all replacements,
                 with minimum element 1.

    --- Example 3 ---
    Input: nums = [999,19,199]
    Output: 10
    Explanation: nums becomes [27, 10, 19] after all replacements,
                 with minimum element 10.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 10^4

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Just implement what you're told. There is no much more to it than that.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  41.51% */

/* Time  Complexity: O(N * D) */ // 'D' is average number of digits in each number
/* Space Complexity: O(1)     */
class Solution {
public:
    int minElement(vector<int>& nums)
    {
        const int N = nums.size();

        int result = INT_MAX;
        for (const int& num : nums)
            result = min(result, sum_digits(num));

        return result;
    }

private:
    int sum_digits(int num)
    {
        int sum = 0;

        while (num > 0)
        {
            sum += num % 10;
            num /= 10;
        }

        return sum;
    }
};
