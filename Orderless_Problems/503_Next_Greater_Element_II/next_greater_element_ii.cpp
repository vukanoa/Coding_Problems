/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    503) Next Greater Element II
    ============================

    ============
    Description:
    ============

    Given a circular integer array nums (i.e., the next element of
    nums[nums.length - 1] is nums[0]), return the next greater number for every
    element in nums.

    The next greater number of a number x is the first greater number to its
    traversing-order next in the array, which means you could search circularly
    to find its next greater number. If it doesn't exist, return -1 for this
    number.

    =============================================================
    FUNCTION: vector<int> nextGreaterElements(vector<int>& nums);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1]
    Output: [2,-1,2]
    Explanation: The first 1's next greater number is 2; 
    The number 2 can't find next greater number. 
    The second 1's next greater number needs to search circularly, which is
    also 2.

    --- Example 2 ---
    Input: nums = [1,2,3,4,3]
    Output: [2,3,4,-1,4]


    *** Constraints ***
    1 <= nums.length <= 10^4
    -10^9 <= nums[i] <= 10^9

*/

#include <stack>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 60.88% */
/* Space Beats: 37.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> nextGreaterElements(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> result(N, -1);

        stack<int> monotonic_stack; // Monotonicly DECREASING stack

        for (int i = 2*N - 1; i >= 0; i--)
        {
            while ( ! monotonic_stack.empty() && monotonic_stack.top() <= nums[i % N])
                monotonic_stack.pop();

            if ( ! monotonic_stack.empty() && (i < N))
                result[i] = monotonic_stack.top();

            monotonic_stack.push(nums[i % N]);
        }

        return result;
    }
};
