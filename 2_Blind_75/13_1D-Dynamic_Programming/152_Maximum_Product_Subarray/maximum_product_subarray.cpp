/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    152) Maximum Product Subarray
    =============================

    ============
    Description:
    ============

    Given an integer array "nums", find a subarray that has the largest
    product, and return the product.

    (A subarray is a contiguous non-empty sequence of elements within an array)

    The test cases are generated so that the answe will fit in a 32-bit
    integer.

    ============================================
    FUNCTION: int maxProduct(vector<int>& nums);
    ============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  nums = [2, 3, -2, 4]
    Output: 6
    Explanation: [2, 3] has the largest product 6.

    --- Example 2 ---
    Input:  nums = [-2, 0, -1]
    Output: 0
    Explanation: The result cannot be 2, because [-2, -1] is not a subarray.

    *** Constraints ***
    1 <= nums.length <= 2* 10^4
    -10 <= nums[i] <= 10
    The product of any prefix or suffix of "nums" is guaranteed to fit in a
        32-bit integer

*/

#include <vector>
#include <algorithm>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Concise. Easiest one to grasp. You need to understand this one in order to
    understand the optimized version that uses O(1) Space.

    Consider this:

          nums = [  2,   8,  -2,  -1,  -3,   0,   7,   4]
                    0    1    2    3    4    5    6    7

        dp_min = [  2,   8, -32,  -1, -96,   1,   7,  28]
        dp_max = [  2,  16,  -2,  32,   3,   1,   7,  28] ---> result = 32


    But why is "32", i.e. [2, 8, -2, -1] a subarray with a MAXIMUM PRODUCT?
    Every time we stumble upon a NEGATIVE element, we don't reset the product
    completely, instead we keep both "dp_min" and "dp_max", since next element
    can flip the sign from the dp_min and potentially become "dp_max" which is
    the largest in the entire "dp_max" vector.




    Also, it's VERY important to notice that once we get to 0, we have to reset
    both:
        
        dp_min = 1;
        dp_max = 1;

    i.e. to neutral element for binary operator "multiply", which is 1.

        x * e = x

    Where 'e' is the neural element for operation "multiply".
    We MUST do that or otherwise every 0 element will mess up our current
    products.

    Here are all the examples with their corresponding "dp_min" and "dp_max"
    vectors:

        #################
        ### Example 1 ###
        #################
        nums:   [  2,   3,  -2,   4]
        dp_min: [  2,   3, -12, -48]
        dp_max: [  2,   6,  -2,   4]  ---> result = 6


        #################
        ### Example 2 ###
        #################
        nums:   [-2, 0, -1]
        dp_min: [-2, 1, -1]
        dp_max: [-2, 1, -1] ---> result = 0(don't consider zeroe's values)


        #################
        ### Example 3 ###
        #################
        nums:   [   2,   7,   5,   -2,    3,   0,   4]
        dp_min: [   2,   7,   5, -140, -420,   1,   4]
        dp_max: [   2,  14,  70,   -2,    3,   1,   4]


        #################
        ### Example 4 ###
        #################
        nums:   [    2,    7,    5,   -2,    3,    8,    4]
        dp_min: [    2,    7,    5, -140, -420,    1,    4]
        dp_max: [    2,   14,   70,   -2,    3,    1,    4]


        #################
        ### Example 5 ###
        #################
        nums:   [    2,     7,     5,  -2,    3,   8,   4, -3]
        dp_min: [ -420,  -210,   -30,  -6, -288, -96, -12,  0]
        dp_max: [40320, 20160,  2880,  576,  96,  32,   0,  0]


        #################
        ### Example 5 ###
        #################
        nums:   [    2,     7,     5,    -2,     3,     8,      4,    -3]
        dp_min: [    2,     7,     5,  -140,  -420, -3360, -13440,  -288]
        dp_max: [    2,    14,    70,    -2,     3,    24,     96, 40320]


        #################
        ### Example 6 ###
        #################
        nums:   [   -3,    -1,    -1]
        dp_min: [   -3,    -1,    -3]
        dp_max: [   -3,     3,     1]


        #################
        ### Example 7 ###
        #################
        nums:   [    0,     2]
        dp_min: [    0,     0]
        dp_max: [    0,     2]


        #################
        ### Example 8 ###
        #################
        nums:   [   -2,     3,    -4]
        dp_min: [   -2,    -6,   -12]
        dp_max: [   -2,     3,    24]


        #################
        ### Example 9 ###
        #################
        nums:   [   -1,    -2,    -9,    -6]
        dp_min: [   -1,    -2,   -18,  -108]
        dp_max: [   -1,     2,    18,   108]


        ##################
        ### Example 10 ###
        ##################
        nums:   [    2,    -1,     1,     1]
        dp_min: [    2,    -2,    -2,    -2]
        dp_max: [    2,    -1,     1,     1]

*/

/* Time  Beats: 100.00% */
/* Space Beats:  5.06% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maxProduct(vector<int>& nums)
    {
        const int N = nums.size();

        vector<int> dp_max(N, 0);
        vector<int> dp_min(N, 0);

        dp_max[0] = nums[0];
        dp_min[0] = nums[0];

        for (int i = 1; i < N; i++)
        {
            if (nums[i] == 0)
                continue;

            dp_max[i] = max( {nums[i], nums[i] * dp_max[i-1], nums[i] * dp_min[i-1]} );
            dp_min[i] = min( {nums[i], nums[i] * dp_max[i-1], nums[i] * dp_min[i-1]} );
        }

        return *max_element(dp_max.begin(), dp_max.end());
    }
};
