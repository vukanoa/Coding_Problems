/*
    ==============
    === MEDIUM ===
    ==============

    =============================================================
    3732) Maximum Product of Three ELements After One Replacement
    =============================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    You must replace exactly one element in the array with any integer value in
    the range [-10^5, 10^5] (inclusive).

    After performing this single replacement, determine the maximum possible
    product of any three elements at distinct indices from the modified array.

    Return an integer denoting the maximum product achievable.

    ==================================================
    FUNCTION: long long maxProduct(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [-5,7,0]
    Output: 3500000
    Explanation:
    Replacing 0 with -10^5 gives the array [-5, 7, -105], which has a product
    (-5) * 7 * (-10^5) = 3500000. The maximum product is 3500000.

    --- Example 2 ---
    Input: nums = [-4,-2,-1,-3]
    Output: 1200000
    Explanation:
    Two ways to achieve the maximum product include:
        [-4, -2, -3] → replace -2 with 105 → product = (-4) * 105 * (-3) = 1200000.
        [-4, -1, -3] → replace -1 with 105 → product = (-4) * 105 * (-3) = 1200000.
    The maximum product is 1200000.

    --- Example 3 ---
    Input: nums = [0,10,0]
    Output: 0
    Explanation:
    There is no way to replace an element with another integer and not have a 0
    in the array. Hence, the product of all three elements will always be 0,
    and the maximum product is 0.


    *** Constraints ***
    3 <= nums.length <= 10^5
    -10^5 <= nums[i] <= 10^5

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 49.36% */
/* Space Beats: 96.47% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // This is SC of C++'s Intro Sort
class Solution {
public:
    long long maxProduct(vector<int>& nums)
    {
        const int N = nums.size();
        long long result = 0LL;

        const int SMALLEST_VAL = -1 * 1e5;
        const int LARGEST_VAL  = 1e5;

        /* Sort in ASCENDING order */
        sort(nums.begin(), nums.end());

        int zeroes_count = count(nums.begin(), nums.end(), 0);
        if (zeroes_count >= N-1)
            return 0;

        if (nums[0] < 0 && nums[1] < 0)
            result = max(result, 1LL * nums[0] * nums[1] * LARGEST_VAL);

        if (nums[N-2] > 0 && nums[N-1] > 0)
            result = max(result, 1LL * nums[N-2] * nums[N-1] * LARGEST_VAL);

        if (nums[0] < 0 && nums[N-1] > 0)
            result = max(result, 1LL * nums[0] * nums[N-1] * SMALLEST_VAL);
        

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 85.90% */
/* Space Beats: 40.38% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Linear {
public:
    long long maxProduct(const vector<int>& nums)
    {
        long long largest        = 0;
        long long second_largest = 0;

        for (const int& num : nums)
        {
            long long abs_num = llabs(1LL * num);

            if (abs_num >= largest)
            {
                second_largest = largest;
                largest        = abs_num;
            }
            else if (abs_num > second_largest)
            {
                second_largest = abs_num;
            }
        }

        return largest * second_largest * 1e5;
    }
};
