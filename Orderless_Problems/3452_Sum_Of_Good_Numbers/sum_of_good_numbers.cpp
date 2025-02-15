/*
    ============
    === EASY ===
    ============

    ===========================
    3452) SUm of Good Numbers
    ===========================

    ============
    Description:
    ============

    Given an array of integers nums and an integer k, an element nums[i] is
    considered good if it is strictly greater than the elements at indices
    i - k and i + k (if those indices exist). If neither of these indices
    exists, nums[i] is still considered good.

    Return the sum of all the good elements in the array.

    =========================================================
    FUNCTION: int sumOfGoodNumbers(vector<int>& nums, int k);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,3,2,1,5,4], k = 2
    Output: 12
    Explanation: The good numbers are nums[1] = 3, nums[4] = 5, and nums[5] = 4
                 because they are strictly greater than the numbers at indices
                 i - k and i + k.

    --- Example 2 ---
    Input: nums = [2,1], k = 1
    Output: 2
    Explanation: The only good number is nums[0] = 2 because it is strictly
                 greater than nums[1].


    *** Constraints ***
    2 <= nums.length <= 100
    1 <= nums[i] <= 1000
    1 <= k <= floor(nums.length / 2)

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory;

*/

/* Time  Beats: 100.00% */
/* Space Beats:     -% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int sumOfGoodNumbers(vector<int>& nums, int k)
    {
        const int N = nums.size();
        int sum = 0;

        for (int i = 0; i < N; i++)
        {
            bool greater = true;

            if (i - k >= 0)
                greater = nums[i] > nums[i - k];

            if (i + k < N)
                greater = greater && nums[i] > nums[i + k];

            if (greater)
                sum += nums[i];
        }

        return sum;
    }
};
