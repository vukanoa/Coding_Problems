/*
    ============
    === HARD ===
    ============

    ==============================================
    3077) Maximum Strength of K Disjoint Subarrays
    ==============================================

    ============
    Description:
    ============

    You are given an array of integers nums with length n, and a positive odd
    integer k.

    Select exactly k disjoint subarrays sub1, sub2, ..., subk from nums such
    that the last element of subi appears before the first element of sub{i+1}
    for all 1 <= i <= k-1. The goal is to maximize their combined strength.

    The strength of the selected subarrays is defined as:

    strength = k * sum(sub1)- (k - 1) * sum(sub2) + (k - 2) * sum(sub3) - ... -
    2 * sum(sub{k-1}) + sum(subk)

    where sum(subi) is the sum of the elements in the i-th subarray.

    Return the maximum possible strength that can be obtained from selecting
    exactly k disjoint subarrays from nums.

    =====
    Note: that the chosen subarrays don't need to cover the entire array.
    =====

    ==============================================================
    FUNCTION: long long maximumStrength(vector<int>& nums, int k);
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,-1,2], k = 3
    Output: 22
    Explanation:
    The best possible way to select 3 subarrays is: nums[0..2], nums[3..3], and nums[4..4]. The strength is calculated as follows:
    strength = 3 * (1 + 2 + 3) - 2 * (-1) + 2 = 22


    --- Example 2 ---
    Input: nums = [12,-2,-2,-2,-2], k = 5
    Output: 64
    Explanation:
    The only possible way to select 5 disjoint subarrays is: nums[0..0], nums[1..1], nums[2..2], nums[3..3], and nums[4..4]. The strength is calculated as follows:
    strength = 5 * 12 - 4 * (-2) + 3 * (-2) - 2 * (-2) + (-2) = 64
    Example 3:
    Input: nums = [-1,-2,-3], k = 1
    Output: -1
    Explanation:
    The best possible way to select 1 subarray is: nums[0..0]. The strength is -1.


    --- Example 3 ---


    *** Constraints ***
    1 <= n <= 10^4
    -10^9 <= nums[i] <= 10^9
    1 <= k <= n
    1 <= n * k <= 10^6
    k is odd.

*/

#include <climits>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    While reading the question I figured out that at every idx of the "nums" we
    have to decide whether to:

        1. Put current element in the current subarray, OR

        2. End the subarray and start a new one (can only be done if there was
           atleast one element in the current subarray before moving onto the
           next), OR

        3. Entirely skip that element and go to the next element
           (will have to start new subarray of course)

    So of course Memoization was the first natural thing to come to my mind.

    The solution is pretty straightforward, it's a recursive solution with
    unique states, which allows us to Memoize(NOT "memorize") the work so that
    we don't compute the same sub-problem more than once.

    A state is composed of:

        1. Index   // Current position we're at
        2. k       // How many subarrays do we need to form
        3. started // If we currently have a started subarray that isn't closed


    #########
    ### 1 ###
    #########
    If we have already put ATLEAST ONE element, it means we CAN terminate the
    current subarray and start working on the next subarray.
    Hence:

        if (started)
            ...


    #########
    ### 2 ###
    #########
    Next, naturaly, there's the option of putting the current nums[idx] element
    in the current subarray, whether or not it has been started. By adding this
    current element we can EITHER "append" it to an already existing and
    ongoing subarray OR we can start the next subarray with our current
    nums[idx].
    Hence:

        // Start a new subarray on this nums[idx]
        long long ret_val = (k % 2 == 0 ? -1 : 1) * k * nums[idx] + solve(idx + 1, k, true, nums);

        if current value of 'k' is ODD,  then we should ADD      current sum.
        if current value of 'k' is EVEN, then we should SUBTRACT current sum


    #########
    ### 3 ###
    #########
    Lastly, we also check if we had NOT put even a single element in the
    current subarray, i.e. started == false, then we have an EXTRA option to
    SKIP the current element, i.e. nums[idx], and go to the next element.
    Hence:

    if ( ! started)
        ...

*/

/* Time  Beats: 12.07% */
/* Space Beats: 16.38% */

/* Time  Complexity: O(N * K * 2) */
/* Space Complexity: O(N * K * 2) */
class Solution {
public:
    vector<vector<vector<long long>>> memo;
    const long long NEG_INF = LLONG_MIN / 2; // To avoid Overflow

    long long maximumStrength(vector<int>& nums, int k)
    {
        const int N = nums.size();

        memo = vector<vector<vector<long long>>> (N, vector<vector<long long>> (k + 1, vector<long long> (2, NEG_INF)));

        return solve(0, 1LL*k, false, nums);
    }

private:
    long long solve(int idx, long long k, bool started, vector<int>& nums)
    {
        if (k == 0)
            return 0;

        if (idx == nums.size())
        {
            if (k == 1 && started)
                return 0;

            return NEG_INF;
        }

        if (memo[idx][k][started] != NEG_INF)
            return memo[idx][k][started];

        long long result = NEG_INF;

        if (started) // Then we can terminate it and start a new one at idx
            result = solve(idx, k - 1, false, nums);

        // Start a new subarray on this nums[idx]
        long long ret_val = (k % 2 == 0 ? -1 : 1) * k * nums[idx] + solve(idx + 1, k, true, nums);

        result = max(result, ret_val);

        if ( ! started) // If it's NOT started, we can SKIP this current idx
            result = max(solve(idx + 1, k, false, nums), result);

        return memo[idx][k][started] = result;
    }
};
