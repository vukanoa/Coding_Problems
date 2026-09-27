/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    3854) Minimum Operations to Make Array Parity Alternating
    =========================================================

    ============
    Description:
    ============

    You are given an integer array nums.

    An array is called parity alternating if for every index i where:

        0 <= i < n - 1,

    nums[i] and nums[i + 1] have different parity (one is even and the other is
    odd).

    In one operation, you may choose any index i and either increase nums[i] by
    1 or decrease nums[i] by 1.

    Return an integer array answer of length 2 where:

        + answer[0] is the minimum number of operations required to make the
          array parity alternating.

        + answer[1] is the minimum possible value of max(nums) - min(nums)
          taken over all arrays that are parity alternating and can be obtained
          by performing exactly answer[0] operations.

    An array of length 1 is considered parity alternating.

    ===============================================================
    FUNCTION: vector<int> makeParityAlternating(vector<int>& nums);
    ===============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [-2,-3,1,4]
    Output: [2,6]
    Explanation:
    Applying the following operations:
        Increase nums[2] by 1, resulting in nums = [-2, -3, 2, 4].
        Decrease nums[3] by 1, resulting in nums = [-2, -3, 2, 3].
    The resulting array is parity alternating, and the value of max(nums) -
    min(nums) = 3 - (-3) = 6 is the minimum possible among all parity
    alternating arrays obtainable using exactly 2 operations.


    --- Example 2 ---
    Input: nums = [0,2,-2]
    Output: [1,3]
    Explanation:
    Applying the following operation:
        Decrease nums[1] by 1, resulting in nums = [0, 1, -2].
    The resulting array is parity alternating, and the value of max(nums) -
    min(nums) = 1 - (-2) = 3 is the minimum possible among all parity
    alternating arrays obtainable using exactly 1 operation.


    --- Example 3 ---
    Input: nums = [7]
    Output: [0,0]
    Explanation:
    No operations are required. The array is already parity alternating, and
    the value of max(nums) - min(nums) = 7 - 7 = 0, which is the minimum
    possible.


    *** Constraints ***
    1 <= nums.length <= 10^5
    -10^9 <= nums[i] <= 10^9

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    People have found this problem to be extremely difficult for some reaosn.

    I don't think it was difficult at all. After all, you only have two options
    to choose from, either:

        1. Nums will begin with an ODD  parity number
        2. Nums will begin with an EVEN parity number


    But how do we know if we should increase od decrease some number that does
    not follow the currently parity rule?

    It's actually simple--if it's greater than the MINIMUM number, we can
    safely decrement it without changing the "max" or the "min".

    If it's smaller then tha MAXIMUM number, we can safely increment it without
    changing the "max" or the "min".


    The only tricky part here is if we have ALL of the values the same.
    For example:

        nums = [4, 4, 4, 4, 4]
                0  1  2  3  4


        min_elem = 4
        max_elem = 4

    So, if the element we need to change the parity of is a MAXIMUM number,
    then we decrement it. However since it's possible that we have ALL of the
    same numbers, it could be possible that by this decrement we'll have a new
    MINIMUM number.


    But it would be a mess to try and take note of all of this.

    Simply copy "nums" into two different vectors: "odd" and "even", that will
    represent nums starting with an odd or even number, repsectively.


    Now each time a number that we need to change the parity of is a MAX number
    we decrement. If it's a MIN number instead, we increment.


    At the end of each of the 2 for-loops, we check what are the MAXIMUM and
    MINIMUM elements, while the operations are counted while we go.


    At the end simply return a better result.

*/

/* Time  Beats: 65.38% */
/* Space Beats: 57.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    vector<int> makeParityAlternating(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> odd  = nums;
        vector<int> even = nums;
        
        int min_elem  = *min_element(odd.begin(), odd.end());
        int max_elem  = *max_element(odd.begin(), odd.end());
        int operations = 0;
        
        /******************/
        /* Start with ODD */
        /******************/
        for (int i = 0; i < N; i++)
        {
            if (i % 2 == 0) // At even_idx, there should be an ODD number
            {
                if (odd[i] % 2 == 0) // It's an EVEN number instead
                {
                    ++operations;
                    
                    if (odd[i] == min_elem)
                        ++odd[i];
                    else if (odd[i] == max_elem)
                        --odd[i];
                }
            }
            else // At odd_idx, there should be an EVEN number
            {
                if (nums[i] % 2 != 0) // It's an ODD number instead
                {
                    ++operations;
                    
                    if (odd[i] == min_elem)
                        ++odd[i];
                    else if (nums[i] == max_elem)
                        --odd[i];
                }                
            }
        }
        vector<int> odd_start = {operations, *max_element(odd.begin(), odd.end()) -
                                             *min_element(odd.begin(), odd.end())};


        // Reset
        min_elem = *min_element(even.begin(), even.end());
        max_elem = *max_element(even.begin(), even.end());
        operations = 0;

        /*******************/
        /* Start with EVEN */
        /*******************/
        for (int i = 0; i < N; i++)
        {
            if (i % 2 == 0) // At even_idx, there should be an EVEN number
            {
                if (even[i] % 2 != 0) // it's an ODD number instead
                {
                    ++operations;

                    if (even[i] == min_elem)
                        ++even[i];
                    else if (even[i] == max_elem)
                        --even[i];
                }
            }
            else // At odd_idx, there should be an ODD number
            {
                if (even[i] % 2 == 0) // it's an EVEN number instead
                {
                    ++operations;
                    
                    if (even[i] == min_elem)
                        ++even[i];
                    else if (even[i] == max_elem)
                        --even[i];
                }                
            }
        }
        vector<int> even_start = {operations, *max_element(even.begin(), even.end()) -
                                              *min_element(even.begin(), even.end())};
        

        // If operations are EQUAL, then return the one with a smaller DIFF
        if (odd_start[0] == even_start[0])
            return odd_start[1] < even_start[1] ? odd_start : even_start;
        
        // If starting with an ODD number requires LESS operations--Return that
        if (odd_start[0] < even_start[0])
            return odd_start;

        // Starting with an EVEN number requires LESS operations
        return even_start;
    }
};
