/*
    ============
    === EASY ===
    ============

    ========================================
    3917) COunt Indices with Opposite Parity
    ========================================

    ============
    Description:
    ============

    You are given an integer array nums of length n.

    The score of an index i is defined as the number of indices j such that:

        + i < j < n, and

        + nums[i] and nums[j] have different parity (one is even and the other
          is odd).

    Return an integer array answer of length n, where answer[i] is the score of
    index i.

    =============================================================
    FUNCTION: vector<int> countOppositeParity(vector<int>& nums);
    =============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4]
    Output: [2,1,1,0]
    Explanation:
        nums[0] = 1, which is odd. Thus, the indices j = 1 and j = 3 satisfy the conditions, so the score of index 0 is 2.
        nums[1] = 2, which is even. Thus, the index j = 2 satisfies the conditions, so the score of index 1 is 1.
        nums[2] = 3, which is odd. Thus, the index j = 3 satisfies the conditions, so the score of index 2 is 1.
        nums[3] = 4, which is even. Thus, no index satisfies the conditions, so the score of index 3 is 0.
    Thus, the answer = [2, 1, 1, 0].

    --- Example 2 ---
    Input: nums = [1]
    Output: [0]
    Explanation:
    There is only one element in nums. Thus, the score of index 0 is 0.


    *** Constraints ***
    1 <= nums.length <= 100
    1 <= nums[i] <= 100

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explantory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  45.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    vector<int> countOppositeParity(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> answer(N, 0);

        int odd  = 0;
        int even = 0;

        for (int j = N-1; j >= 0; j--)
        {
            if (nums[j] & 1)
            {
                answer[j] = even;
                ++odd;
            }
            else
            {
                answer[j] = odd;
                ++even;
            }
        }

        return answer;
    }
};
