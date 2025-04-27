/*
    ============
    === EASY ===
    ============

    ======================================================
    3992) Count Subarrays of Length Three With a Condition
    ======================================================

    ============
    Description:
    ============

    Given an integer array nums, return the number of subarrays of length 3
    such that the sum of the first and third numbers equals exactly half of the
    second number.

    ================================================
    FUNCTION: int countSubarrays(vector<int>& nums);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,4,1]
    Output: 1
    Explanation:
    Only the subarray [1,4,1] contains exactly 3 elements where the sum of the first and third numbers equals half the middle number.

    --- Example 2 ---
    Input: nums = [1,1,1]
    Output: 0
    Explanation:
    [1,1,1] is the only subarray of length 3. However, its first and third numbers do not add to half the middle number.


    *** Constraints ***
    3 <= nums.length <= 100
    -100 <= nums[i] <= 100

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
/* Space Beats:  55.56% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int countSubarrays(vector<int>& nums)
    {
        const int n = nums.size();
        int result = 0;

        int left  = 0;
        int right = 2;

        while (right < n)
        {
            if ( 1.0 * (nums[left] + nums[right]) == (1.0 * nums[right-1] / 2))
                result++;

            left++;
            right++;
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    More elegant way of writing it. If you are a beginner it's beneficial to
    see both implementations.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  45.56% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    int countSubarrays(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 1; i < N-1; i++)
        {
            if (nums[i] & 1)
                continue;

            if (nums[i] / 2 == (nums[i-1] + nums[i+1]))
                result++;
        }

        return result;
    }
};
