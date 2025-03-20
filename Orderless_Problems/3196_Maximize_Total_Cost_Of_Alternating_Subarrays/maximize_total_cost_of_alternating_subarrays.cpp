/*
    ==============
    === MEDIUM ===
    ==============

    ==================================================
    3196) Maximize Total Cost of Alternating Subarrays
    ==================================================

    ============
    Description:
    ============

    You are given an integer array nums with length n.

    The cost of a

    nums[l..r], where 0 <= l <= r < n, is defined as:

    cost(l, r) = nums[l] - nums[l + 1] + ... + nums[r] * (−1)r − l

    Your task is to split nums into subarrays such that the total cost of the
    subarrays is maximized, ensuring each element belongs to exactly one
    subarray.

    Formally, if nums is split into k subarrays, where k > 1, at indices
    i1, i2, ..., ik − 1, where 0 <= i1 < i2 < ... < ik - 1 < n - 1, then the
    total cost will be:

    cost(0, i1) + cost(i1 + 1, i2) + ... + cost(ik − 1 + 1, n − 1)

    Return an integer denoting the maximum total cost of the subarrays after
    splitting the array optimally.

    =====
    Note: If nums is not split into subarrays, i.e. k = 1, the total cost is
          simply cost(0, n - 1).
    =====

    ========================================================
    FUNCTION: long long maximumTotalCost(vector<int>& nums);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,-2,3,4]
    Output: 10
    Explanation: One way to maximize the total cost is by splitting
    [1, -2, 3, 4] into subarrays [1, -2, 3] and [4]. The total cost will be
    (1 + 2 + 3) + 4 = 10.

    --- Example 2 ---
    Input: nums = [1,-1,1,-1]
    Output: 4
    Explanation: One way to maximize the total cost is by splitting
    [1, -1, 1, -1] into subarrays [1, -1] and [1, -1]. The total cost will be
    (1 + 1) + (1 + 1) = 4.

    --- Example 3 ---
    Input: nums = [0]
    Output: 0
    Explanation: We cannot split the array further, so the answer is 0.

    --- Example 4 ---
    Input: nums = [1,-1]
    Output: 2
    Explanation: Selecting the whole array gives a total cost of 1 + 1 = 2,
                 which is the maximum.


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    It's important to notice that since this is the formula:

        cost(l, r) = nums[l] - nums[l + 1] + ... + nums[r] * (−1)^(r − l)

    if we consider a single element a range, for example:

        cost(4, 4) = nums[4] * (-1)^(4 - 4)

    That number will ALWAYS be as is, in other words--If it's positive it will
    stay positive. If it's negative, it will stay negative.


    The next thing to notice is this:

        If we've ended previous subarray at index BEFORE this one, then this
        one must be added AS IS, meaning: if it's positive it stays positive,
        if it's negative it stays negative.

    Otherwise, we want to take the maximum possible sum so far and negate the
    current element.

    If the current element is negative, we will increase our total sum even
    further, however if it's a positive number, we'll decrease it.


    There's not much more to it, but it's difficult to break out of the
    "Description", it's purposefully vague and makes you think you really need
    to make subarrays or something like that.

    If you still don't get it, I advise you to go through this example with
    pen and paper:

        nums = [1,    3,  -12,   5,   6,  -7,  -48, -80, -390, -100,   4]
                0     1    2     3    4    5    6    7     8     9    10


    The crux is this:

    We can make ANY NUMBER OF Subarrays if we want, however only the elements
    that end on a ODD index WITHIN THE INDIVIDUAL SUBARRAY can be negated,
    therefore you should prioritize to end your odd-size subarrays with a
    negative numbers, but now always since maybe ending it on the next negative
    will increase the total sum.


    If we've ended the previous subarray, then the current element needs to be
    added AS IS.

    If we've DIDN'T end the previous subbarray at the element before, then
    consider ending it at this one. That's why we ALWAYS have to subtract the
    current element from "add_result" which is a result of elements where the
    last added element is added AS IS, it's not an end of the previous subarray

    Thta's it.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  76.21% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    long long maximumTotalCost(vector<int> nums)
    {
        const int N = nums.size();

        long long add_result = nums[0];
        long long sub_result = nums[0];

        for (int i = 1; i < N; i++)
        {
            long tmp_add = max(add_result, sub_result) + nums[i];
            long tmp_sub = add_result - nums[i];

            add_result = tmp_add;
            sub_result = tmp_sub;
        }

        return max(add_result, sub_result);
    }
};
