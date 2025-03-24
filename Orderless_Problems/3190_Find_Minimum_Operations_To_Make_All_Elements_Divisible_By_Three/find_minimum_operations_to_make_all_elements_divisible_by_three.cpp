/*
    ============
    === EASY ===
    ============

    =====================================================================
    3190) Find Minimum Operations to Make All Elements Divisible by Three
    =====================================================================

    ============
    Description:
    ============

    You are given an integer array nums. In one operation, you can add or
    subtract 1 from any element of nums.

    Return the minimum number of operations to make all elements of nums
    divisible by 3.

    ===================================================
    FUNCTION: int minimumOperations(vector<int>& nums);
    ===================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4]
    Output: 3
    Explanation:
    All array elements can be made divisible by 3 using 3 operations:
    Subtract 1 from 1.
    Add 1 to 2.
    Subtract 1 from 4.

    --- Example 2 ---
    Input: nums = [3,6,9]
    Output: 0


    *** Constraints ***
    1 <= nums.length <= 50
    1 <= nums[i] <= 50

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The elegance of this Solution comes from the fact that it's either:

        1) Number is already divisible by 3, therefore we do nothing

        2) Number is either 1 value-point BELOW or 1 value-point ABOVE
           divisibleness by 3

    Therefore if the number is NOT divisible by three, we know that we can
    "tweak" it to be divisible by simply adding or subtracting one.

    Since we only need to count how many we need to add or subtract, we
    increment our result by 1 and that's it.

    And the end we simply return result;

*/

/* Time  Beats: 100.00% */
/* Space Beats:  78.94% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minimumOperations(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        for (int i = 0; i < N; i++)
        {
            if (nums[i] % 3 != 0)
                result++;
        }

        return result;
    }
};
