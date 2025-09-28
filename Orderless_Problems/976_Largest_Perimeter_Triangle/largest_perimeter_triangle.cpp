/*
    ============
    === EASY ===
    ============

    ===============================
    976) Largest Perimeter Triangle
    ===============================

    ============
    Description:
    ============

    Given an integer array nums, return the largest perimeter of a triangle
    with a non-zero area, formed from three of these lengths. If it is
    impossible to form any triangle of a non-zero area, return 0.

    ==================================================
    FUNCTION: int largestPerimeter(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,1,2]
    Output: 5
    Explanation: You can form a triangle with three side lengths: 1, 2, and 2.

    --- Example 2 ---
    Input: nums = [1,2,1,10]
    Output: 0
    Explanation:
    You cannot use the side lengths 1, 1, and 2 to form a triangle.
    You cannot use the side lengths 1, 1, and 10 to form a triangle.
    You cannot use the side lengths 1, 2, and 10 to form a triangle.
    As we cannot use any three side lengths to form a triangle of non-zero
    area, we return 0.


    *** Constraints ***
    3 <= nums.length <= 10^4
    1 <= nums[i] <= 10^6

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is the condition that needs to be true in order to construct a valid
    triangle:

        if (nums[L] + nums[M] > nums[R])

    Therefore, we just sort the Input and fix the consecutive points.
    For each VALID triangle, we calculate its perimeter by adding all the sides

    That's it.

*/

/* Time  Beats: 30.97% */
/* Space Beats: 95.69% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(N)        */
class Solution {
public:
    int largestPerimeter(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        /* Sort */
        sort(nums.begin(), nums.end());

        int L = 0;
        int M = 1;
        int R = 2;

        while (R < N)
        {
            if (nums[L] + nums[M] > nums[R])
                result = max(result, nums[L] + nums[M] + nums[R]);

            // Increment this Fixed-Window
            L++;
            M++;
            R++;
        }

        return result;
    }
};
