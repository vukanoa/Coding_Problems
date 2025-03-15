/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    3201) Find the Maximum Length of Valid Subsequence I
    ====================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    A subsequence sub of nums with length x is called valid if it satisfies:

        (sub[0] + sub[1]) % 2 == (sub[1] + sub[2]) % 2 == ... == (sub[x - 2] + sub[x - 1]) % 2.

    Return the length of the longest valid subsequence of nums.

    A subsequence is an array that can be derived from another array by
    deleting some or no elements without changing the order of the remaining
    elements.

    ===============================================
    FUNCTION: int maximumLength(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,4]
    Output: 4
    Explanation:
    The longest valid subsequence is [1, 2, 3, 4].

    --- Example 2 ---
    Input: nums = [1,2,1,1,2,1,2]
    Output: 6
    Explanation:
    The longest valid subsequence is [1, 2, 1, 2, 1, 2].

    --- Example 3 ---
    Input: nums = [1,3]
    Output: 2
    Explanation:
    The longest valid subsequence is [1, 3].


    *** Constraints ***
    2 <= nums.length <= 2 * 10^5
    1 <= nums[i] <= 10^7

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

/* Time  Beats: 31.09% */
/* Space Beats: 14.42% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int maximumLength(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 0;

        vector<int> even_e_e(N, 1);
        vector<int> even_o_o(N, 1);

        vector<int> odd_o_e(N, 1);

        int leftmost_odd  = N;
        int leftmost_even = N;

        if (nums[N-1] & 1) // Odd
            leftmost_odd = N-1;
        else
            leftmost_even = N-1;

        for (int i = N-2; i >= 0; i--)
        {
            if (nums[i] & 1) // Odd
            {
                if (leftmost_odd < N)
                    even_o_o[i] = 1 + even_o_o[leftmost_odd];

                if (leftmost_even < N)
                    odd_o_e[i] = 1 + odd_o_e[leftmost_even];

                leftmost_odd = i;
            }
            else // Even
            {

                if (leftmost_even < N)
                    even_e_e[i] = 1 + even_e_e[leftmost_even];

                if (leftmost_odd < N)
                    odd_o_e[i] = 1 + odd_o_e[leftmost_odd];

                leftmost_even = i;
            }
        }

        int one = *max_element(even_e_e.begin(), even_e_e.end());
        int two = *max_element(even_o_o.begin(), even_o_o.end());
        int thr = *max_element(odd_o_e.begin(), odd_o_e.end());

        return max( {one, two, thr} );
    }
};
