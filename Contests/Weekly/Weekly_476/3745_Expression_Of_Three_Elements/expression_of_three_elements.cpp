/*
    ============
    === EASY ===
    ============

    ==========================================
    3754) Maximize Expression of Tree Elements
    ==========================================

    ============
    Description:
    ============

    You are given an integer array nums.

    Choose three elements a, b, and c from nums at distinct indices such that
    the value of the expression a + b - c is maximized.

    Return an integer denoting the maximum possible value of this expression.

    ===========================================================
    FUNCTION: int maximizeExpressionOfThree(vector<int>& nums);
    ===========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,4,2,5]
    Output: 8
    Explanation:
    We can choose a = 4, b = 5, and c = 1. The expression value is 4 + 5 - 1 =
    8, which is the maximum possible.

    --- Example 2 ---
    Input: nums = [-2,0,5,-2,4]
    Output: 11
    Explanation:
    We can choose a = 5, b = 4, and c = -2. The expression value is 5 + 4 -
    (-2) = 11, which is the maximum possible.


    *** Constraints ***
    3 <= nums.length <= 100
    -100 <= nums[i] <= 100

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 27.41% */
/* Space Beats: 52.41% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maximizeExpressionOfThree(vector<int>& nums)
    {
        const int N = nums.size();
        int largest_first  = INT_MIN;
        int largest_second = INT_MIN;
        int smallest_first = INT_MAX;

        for (int i = 0; i < N; i++)
        {
            if (nums[i] > largest_first)
            {
                largest_second = largest_first;
                largest_first  = nums[i];
            }
            else if (nums[i] > largest_second)
            {
                largest_second = nums[i];
            }

            smallest_first = min(smallest_first, nums[i]);
        }

        return largest_first + largest_second - smallest_first;
    }
};
