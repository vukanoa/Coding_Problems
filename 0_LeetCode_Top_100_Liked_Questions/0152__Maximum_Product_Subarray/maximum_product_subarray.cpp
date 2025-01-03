#include <iostream>
#include <vector>
#include <climits>
#include <algorithm> // for *max_element(..),

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

/*
    ------------
    --- IDEA ---
    ------------

    Concise. Easiest one to grasp. You need to understand this one in order to
    understand Optimizations of Space in fruther Solutions down below.

*/

/* Time  Beats: 16.31% */
/* Space Beats:  5.20% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Concise_2024 {
public:
    int maxProduct(vector<int>& nums)
    {
        const int n = nums.size();

        vector<int> dp_max(n, 0);
        vector<int> dp_min(n, 0);

        dp_max[0] = dp_min[0] = nums[0];

        for (int i = 1; i < n; i++)
        {
            // If the prev one is zero, set both DPs to nums[i]
            if (nums[i-1] == 0)
            {
                dp_max[i] = dp_min[i] = nums[i];
                continue;
            }

            dp_max[i] = max( {nums[i], nums[i] * dp_max[i-1], nums[i] * dp_min[i-1]} );
            dp_min[i] = min( {nums[i], nums[i] * dp_max[i-1], nums[i] * dp_min[i-1]} );
        }

        return *max_element(dp_max.begin(), dp_max.end());
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This is Optimized Solution from the above.
    Instead of using the entire vector "dp", we simply use two variables and
    thus reduce the Time Complexity from O(n) to O(1).

*/

/* Time  Beats: 100.00% */
/* Space Beats:   6.69% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Concise_Optimized_2024 {
public:
    int maxProduct(vector<int>& nums)
    {
        const int n = nums.size();

        int dp_max = nums[0];
        int dp_min = nums[0];

        int result = nums[0];
        for (int i = 1; i < n; i++)
        {
            if (nums[i-1] == 0)
            {
                dp_max = dp_min = nums[i];

                result = max(result, dp_max);
                continue;
            }

            int largest  = max( {nums[i], nums[i] * dp_max, nums[i] * dp_min} );
            int smallest = min( {nums[i], nums[i] * dp_max, nums[i] * dp_min} );

            dp_max = largest;
            dp_min = smallest;

            result = max(result, dp_max);
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    It is sort of like Kadane's algorithm.
    However, we have to keep track of both highest and lowest values, even
    if we are looking for high, or maximum, value.

    Why is that?
    Consider this example:
    array: [-1,    -2,  -9, -6]

    If we were to keep only high values, then we would've had:
    array: [-1, -2, -9, -6]
    high:  [ 2, 18, 54,  0]

    In the above example we always multiply:
        1. nums[i] * high[i + 1]
        2. nums[i] * nums[i + 1]
    and we start second element from the back. That is: n-2

    If both products are positive, put the greater one in high[i].
    if one is positive and the other is negative, put the positive in high[i]
    If neither is positive, put 0 in high[i].

    In high[0] we check if current element, that is nums[0] in this case
    multiplied by high[1] is greater than high[1], that of course, would be
    false and yet we would then proceed to save the value of:
        nums[i] * nums[i + 1];
    instead.

    Thus we would make a mistake because it is true that max value of
    position 1 is 18, but the lowest value of position 1 was -108 and since
    we have integers that means we have both positive and negative elements,
    that further means that maybe multiplying a lowest value of next's
    position would actually give us the highest value globally.

    Thus we MUST have another array and that is the one consisted of lowest
    products, as well.

    There are two edge cases:
        1. There is only one element in the entire array.
               just return nums[0];

        2. The element itself could be "the maximum product subarray" of all
           the products in our array "high".
               For that reason we have to check if the element itself is
               greater than our "max" value.

    For 2nd Example of an Edge Case, consider this example:
    array: [0, 2]
    low:   [0, 0]
    high:  [0, 0]

    If we were to only follow an algorithm and return the highest value of
    our array named "high", then we would've returned 0. But we can clearly see
    that 2 is bigger than 0, thus we would have to include a checkup in, every
    iteration, if the current element is greater than "max" and if it is update
    variable "max".

    Here are all the examples with their corresponding "low" and "high" arrays:

        Example 1
    array: [  2,   3, -2, 4]
    low:   [-48, -24, -8, 0]
    high:  [  6,   0,  0, 0]

        Example 2
    array: [-2, 0, -1]
    low:   [ 0, 0,  0]
    high:  [ 0, 0,  0]

        Example 3
    array: [   2,    7,   5, -2,  3,  0,  4]
    low:   [-560, -280, -30, -6,  0,  0,  0]
    high:  [  70,   35,   0,  0,  0,  0,  0]

        Example 4
    array: [    2,     7,    5,   -2,  3,  8,  4]
    low:   [-7770, -3885, -555, -192,  0,  0,  0]
    high:  [   70,    35,    0,    0, 96, 32,  0]

        Example 5
    array: [    2,     7,     5,  -2,    3,   8,   4, -3]
    low:   [ -420,  -210,   -30,  -6, -288, -96, -12,  0]
    high:  [40320, 20160,  2880,  576,  96,  32,   0,  0]

        Example 6
    array: [-3, -1, -1]
    low:   [-3,  0,  0]
    high:  [ 3,  1,  0]

        Example 7
    array: [0, 2]
    low:   [0, 0]
    high:  [0, 0]

        Example 8
    array: [-2,   3, -4]
    low:   [-6, -12,  0]
    high:  [24,   0,  0]

        Example 9
    array: [-1,    -2,  -9, -6]
    low:   [-18, -108,   0,  0]
    high:  [108,   18,  54,  0]

        Example 10
    array: [ 2, -1, 1, 1]
    low:   [-2, -1, 0, 0]
    high:  [ 0,  0, 1, 0]

    The Algorithm of the above explained approach would be:
    int maxProduct(std::vector<int>& nums)
    {
        int n = nums.size();

        if (n == 1)
            return nums[0];

        std::vector<int> dp_low(n, 0);
        std::vector<int> dp_high(n, 0);

        for (int i = n - 2; i >= 0; i--)
        {
            int mul_low  = nums[i] * dp_low[i + 1];
            int mul_high = nums[i] * dp_high[i + 1];
            int mul_i = nums[i] * nums[i + 1];

            int max = std::max(mul_low, mul_high);
            max = std::max(max, mul_i);

            int min = std::min(mul_low, mul_high);
            min = std::min(min, mul_i);

            dp_low[i] = min;
            dp_high[i] = max;
        }

        int max = 0;
        for (int i = 0; i < n; i++)
        {
            if (dp_high[i] > max)
                max = dp_high[i];

            if (nums[i] > max)
                max = nums[i];
        }

        return max;
    }

    We can clearly see that there is a room for optimization. It's obvious that
    we don't have two separate for loops. That's first.

    Second, and the more, and actually most, important is reducing the Space
    Complexity of the above approach from:
        O(n) to O(1)

    So how should we go about doing that?

    Well, we can clearly see that in each iteration, the only thing we're
    actually using is:
        previously calculated "low" and previously calculated "high".

    Thus we can conclude that we don't need the whole array for storing
    "high" and "low" values, but only 2 variables that will store current's
    iteration values.
    Those values will be used in the NEXT iteration BEFORE the update of both
    "high" and "low" variables.

    Also, the reason we assign max to be nums[n - 1] is because that is the
    only element we won't be iterating with in the while loop, thus just assume
    that it is the answer and if proven otherwise in the loop, update the value.

    Thus, we end up with the implementation below.

*/

/* Time  Beats: 96.99% */
/* Space Beats: 99.47% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_DP {
public:
    int maxProduct(std::vector<int>& nums)
    {
        int n = nums.size();

        if (n == 1)
            return nums[0];

        int low  = 0;
        int high = 0;
        int max  = nums[n - 1];

        for (int i = n - 2; i >= 0; i--)
        {
            int mul_low  = nums[i] * low;
            int mul_high = nums[i] * high;
            int mul_i = nums[i] * nums[i + 1];

            high = std::max(mul_low, mul_high);
            high = std::max(high, mul_i);

            low  = std::min(mul_low, mul_high);
            low  = std::min(low, mul_i);

            if (high > max)
                max = high;

            if (nums[i] > max)
                max = nums[i];
        }

        return max;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    The above explanation is too much.

    Consider only these Examples:

    [-2, 3, 4] => 24

    [2, -5, -2, -4, 3] => 24

    [-1, -2, -3] => 6
    ~~~ ~~~
       v
    max +2
    min -2

    [-1, -2, -3] => 6
     ~~~~ ~~~~~
         v
    max  6
    min -6


    There is one Edge case:
    [-1, -2, -3, 0, 3, 5]

    Once we get to 0:
         6 * 0 = 0
        -6 * 0 = 0

        x * 0 = 0

    0 kill any further product, thus once we get to element 0, reset max and
    min to 1. (Since 1 is a "neutral element" for multiplying in Mathematics)

    However since we're checking it like this:
        dp_max = max(dp_max * nums[i], dp_min * nums[i], nums[i]);
        dp_min = min(dp_max * nums[i], dp_min * nums[i], nums[i]);

    We don't need to cover the Edge case specifically. This will get care of
    that.

*/

/* Time  Beats: 100% */
/* Space Beats: 86.21% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Neat_DP {
public:
    int maxProduct(std::vector<int>& nums)
    {
        int n = nums.size();

        int result = INT_MIN;
        int dp_min = 1;
        int dp_max = 1;

        for (int i = 0; i < n; i++)
        {
            int mul_low  = dp_min * nums[i];
            int mul_high = dp_max * nums[i];

            /* dp_max = max(dp_max * nums[i], dp_min * nums[i], nums[i]); */
            dp_max = std::max(mul_low, mul_high);
            dp_max = std::max(dp_max, nums[i]);

            /* dp_min = min(dp_max * nums[i], dp_min * nums[i], nums[i]); */
            dp_min = std::min(mul_low, mul_high);
            dp_min = std::min(dp_min, nums[i]);

            result = std::max(result, dp_max);
        }

        return result;
    }
};




/* Time  Beats: 100% */
/* Space Beats: 69.92% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Intuitive{
public:
    int maxProduct(std::vector<int>& nums)
    {
        int n = nums.size();
        int max = std::max(nums[0], nums[n-1]);

        int dp = nums[0];
        for (int i = 1; i < n; i++)
        {
            dp = dp == 0 ? nums[i] : nums[i] * dp;
            max = std::max(max, dp);
        }

        dp = nums[n - 1];
        for (int i = n - 2; i >= 0; i--)
        {
            dp = dp == 0 ? nums[i] : nums[i] * dp;
            max = std::max(max, dp);
        }

        return max;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

        [2,  8, -2, -1, -3, 0, 7, 4]

    max [2  16  -2  32   3  1  7  28]
    min [2   8 -32  -1 -96  1  7  28]

    It's important to notice that once we get to 0, we have to reset both "min"
    and "max" to neutral element for operations "multiply", which is 1.

    x * e = x

    Where 'e' is the neural element for operation "multiply".

    Also, in "for" loop I have to assign "min" to "tmp_min", since I want to
    use that value for calculating max as well. If I was not to do that, I'd be
    using "min" from the just caclulated result that was stored in min.

*/

/* Time  Beats: 88.98% */
/* Space Beats: 13.52% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Intuitive_2 {
public:
    int maxProduct(std::vector<int>& nums)
    {
        int max = nums[0];
        int min = nums[0];

        int largest = max;

        for (int i = 1; i < nums.size(); i++)
        {
            int tmp_min = min;

            if (min == 0) min = 1;
            if (max == 0) max = 1;

            min = std::min(nums[i] * min, nums[i] * max);
            min = std::min(min, nums[i]);

            max = std::max(nums[i] * tmp_min, nums[i] * max);
            max = std::max(max, nums[i]);

            largest = std::max(largest, max);
        }

        return largest;
    }
};


int
main()
{
    Solution_DP          sol_dp;
    Solution_Neat_DP     sol_neat_dp;
    Solution_Intuitive   sol_intuitive;
    Solution_Intuitive_2 sol_intuitive_2;

    /* Example 1 */
    // std::vector<int> nums = {2, 3, -2, 4};

    /* Example 2 */
    // std::vector<int> nums = {-2, 0, 1};

    /* Example 3 */
    // std::vector<int> nums = {2, 7, 5, -2, 3, 0, 4};

    /* Example 4 */
    // std::vector<int> nums = {2, 7, 5, -2, 3, 8, 4};

    /* Example 5 */
    // std::vector<int> nums = {2, 7, 5, -2, 3, 8, 4, -3};

    /* Example 6 */
    // std::vector<int> nums = {-3, -1, -1};

    /* Example 7 */
    // std::vector<int> nums = {0, 2};

    /* Example 8 */
    std::vector<int> nums = {-2, 3, -4};

    /* Example 9 */
    // std::vector<int> nums = {-1, -2, -9, -6};

    /* Example 10 */
    // std::vector<int> nums = {2, -1, 1, 1};

    /* Example 11 */
    // std::vector<int> nums = {2, -5, -2, -4, 3};

    /* Example 12 */
    // std::vector<int> nums = {-1, -2, -3, 0, 3, 5};


    std::cout << "\n\t================================";
    std::cout << "\n\t=== MAXIMUM PRODUCT SUBARRAY ===";
    std::cout << "\n\t================================\n";


    /* Write Input */
    bool first = true;
    std::cout << "\n\tArray: [";
    for (auto x: nums)
    {
        if (!first)
            std::cout << ", ";

        std::cout << x;
        first = false;
    }
    std::cout << "]\n";


    /* Solution */
    // int product = sol_dp.maxProduct(nums);
    int product = sol_neat_dp.maxProduct(nums);
    // int product = sol_intuitive.maxProduct(nums);
    // int product = sol_intuitive_2.maxProduct(nums);


    /* Write Output */
    std::cout << "\n\tMax Product is: " << product << "\n\n";


    return 0;
}
