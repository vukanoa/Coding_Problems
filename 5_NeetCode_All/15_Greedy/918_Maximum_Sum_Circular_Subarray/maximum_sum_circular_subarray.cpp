/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    918) Maximum Sum Circular Subarray
    ==================================

    ============
    Description:
    ============

    Given a circular integer array nums of length n, return the maximum
    possible sum of a non-empty subarray of nums.

    A circular array means the end of the array connects to the beginning of
    the array. Formally, the next element of nums[i] is nums[(i + 1) % n] and
    the previous element of nums[i] is nums[(i - 1 + n) % n].

    A subarray may only include each element of the fixed buffer nums at most
    once. Formally, for a subarray nums[i], nums[i + 1], ..., nums[j], there
    does not exist i <= k1, k2 <= j with k1 % n == k2 % n.

    ========================================================
    FUNCTION: int maxSubarraySumCircular(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,-2,3,-2]
    Output: 3
    Explanation: Subarray [3] has maximum sum 3.

    --- Example 2 ---
    Input: nums = [5,-3,5]
    Output: 10
    Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10.

    --- Example 3 ---
    Input: nums = [-3,-2,-3]
    Output: -2
    Explanation: Subarray [-2] has maximum sum -2.


    *** Constraints ***
    n == nums.length
    1 <= n <= 3 * 10^4
    -3 * 10^4 <= nums[i] <= 3 * 10^4

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    This is a MESSY way of solving this problem. I advise you to take a look at
    a Solution_Efficient down below.


    Also we've used a common technique for circular arrays which is doubling
    the array.

    However, this was NOT necessary in this approach, but for general dicactir
    purposes it's solved this way.

*/

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Messy {
public:
    int maxSubarraySumCircular(vector<int>& nums)
    {
        const int N = nums.size();

        bool all_negatives = true;

        int max_elem  = INT_MIN;
        int total_sum = 0;
        for (int i = 0; i < N; i++)
        {
            max_elem   = max(max_elem, nums[i]);
            total_sum += nums[i];

            if (nums[i] >= 0)
                all_negatives = false;
        }

        if (all_negatives)
            return max_elem;

        vector<int> extended_nums = nums;
        extended_nums.insert(extended_nums.end(), nums.begin(), nums.end());

        int min_subarray_sum = 0;
        int sum = 0;

        /* Find MINIMUM Subarray */
        int start = 0;
        int end   = 0;
        while (end < 2 * N)
        {
            if (end - start == N)
            {
                sum -= extended_nums[start];
                start++;

                while (start < end && extended_nums[start] >= 0)
                {
                    sum -= extended_nums[start];
                    start++;
                }
            }

            if (sum + extended_nums[end] >= 0)
            {
                sum = 0;
                start = end + 1;
            }
            else
            {
                sum += extended_nums[end];
                min_subarray_sum = min(min_subarray_sum, sum);
            }

            // Increment
            end++;
        }

        /* Find MAXIMUM Subarray */
        int max_subarray_sum = 0;
        sum = 0;

        start = 0;
        end   = 0;
        while (end < 2 * N)
        {
            if (end - start == N)
            {
                sum -= extended_nums[start];
                start++;

                while (start < end && extended_nums[start] <= 0)
                {
                    sum -= extended_nums[start];
                    start++;
                }
            }

            if (sum + extended_nums[end] < 0)
            {
                sum = 0;
                start = end + 1;
            }
            else
            {
                sum += extended_nums[end];
                max_subarray_sum = max(max_subarray_sum, sum);
            }

            // Increment
            end++;
        }

        return max(max_subarray_sum, total_sum - min_subarray_sum);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Kadane's algorithm + tricks for handling circular array.

    If the maximum subarray is in the middle or only connected to one of the
    edges of our array "nums", then that means we'd be able to retrieve the
    result of this problem by using a standard Kadane's Algorithm.

    However, the problem arises once we can use the property and the crux of
    this problem's description--We have a circular integer array.

    What does that mean?

    That means that if we had, for example, this array:
        Input: nums = [5,-3,5]

    Maximum subarray is not 7, but 10.
    How?

    Since the last element is connected to the first element--because it's a
    circular array--then instead of taking -3 into account, we can only take
    elements on the edges of the array and, thus, have a maximum subarray of
    10.

    We are taking these:

                   -------     -------
                         |     |
        Input: nums = [5 | -3  | 5]
                         |     |
                   -------     -------

    So how should we do that with Kadane's algorithm?
    It's not super obvious, but not too difficult to figure out either.

    We should do an INVERT the problem. Instead of searching for a maximum
    subarray, we're going to search for a MINIMUM subarray.

    Why?

    Because by finding the minimum contiguous subarray(or just subarray, since
    that is what subarray means, but wanted to be explicit) we can find the
    value of the MINIMUM subarray that, when subtracted from the total_sum,
    we'd get a MAXIMUM CIRCULAR subarray.

    By having a total sum of the entire array "nums" and by subtracting the
    MINIMUM subarray, we're going to obtain the maximum value for a subarray
    where two ends of the array are connected, with one or more central
    elements excluded from the sum.

    In other words:

        total_sum - global_min;

    global_min is the value of the subarray with the lowest sum.


    However, this inverted way can simply NOT be the correct solution, that's
    why we MUST take the maximum of either:

        max(max_subarray_sum, total_sum - min_subarray_sum)


    Consider this Example:

        nums = [-4, -7, -9, -8, 6, 7, -10, -6, 9, 2]
                 0   1   2   3  4  5   6    7  8  9

    In this the case MINIMUM subarray will be this:

        nums = [-4, -7, -9, -8, 6, 7, -10, -6, 9, 2]
                 0   1   2   3  4  5   6    7  8  9
                 ^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    However, by removing this MINIMUM subarray, we'd end up with a result of:

        9 + 2 = 11

    Which is NOT the correct result. The correct result is:

        6 + 7 = 13


    So how do we reconcile this?

    irst, do a standard Kadane's Algorithm, which would obtain a result of 13,
    and then do this INVERTED version, which would get us a result of
    (total_sum - min_subarray_sum) = 11.

    Simply take greater of the two obtained results.



    However, there is one edge case: When all the elements are NEGATIVE.

    =================
    === EDGE CASE ===
    =================

    Consider this example:
        nums = [-8, -3, -8]

    At the end global_max would be -3 and global_min would be -19.

    However if we were to check what's greater out of these two:
        1. global_max
            or
        2. total_sum - global_min

    We'd stumble upon a, not so obvious, edge case:
        global_max             = -3
        total_sum - global_min = -19 - (-19) = -19 + 19 = 0

    So what's bigger? -3 or 0?

    Obviously 0. however that's not possible to get with this example since
    are obliged to take at least one element. We aren't allowed to consider an
    empty subarray, therefore we'd mistakenly return 0 instead of 3.

    So how should we circumvent this issue?

    If the global_max is NEGATIVE at the end, then return max_element of the
    array as a result.

*/

/* Time  Beats: 100.00% */
/* Space Beats: 100.00% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_Elegant {
public:
    int maxSubarraySumCircular(std::vector<int>& nums)
    {
        int total_sum = 0;

        int global_max = nums[0];
        int global_min = nums[0];

        int curr_max = 0;
        int curr_min = 0;

        for (const int& num : nums)
        {
            total_sum += num;

            curr_max   = max(curr_max + num, num);
            curr_min   = min(curr_min + num, num);

            global_max = max(global_max, curr_max);
            global_min = min(global_min, curr_min);
        }

        // max_element will be negative IF AND ONLY IF all elements are negative
        return global_max < 0 ? global_max : max(global_max, total_sum - global_min);
    }
};
