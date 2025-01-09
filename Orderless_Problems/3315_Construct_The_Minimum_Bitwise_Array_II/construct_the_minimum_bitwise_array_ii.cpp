/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    3315) Construct the Minimum Bitwise Array II
    ============================================

    ============
    Description:
    ============

    You are given an array nums consisting of n prime integers.

    You need to construct an array ans of length n, such that, for each
    index i, the bitwise OR of ans[i] and ans[i] + 1 is equal to nums[i], i.e.
    ans[i] OR (ans[i] + 1) == nums[i].

    Additionally, you must minimize each value of ans[i] in the resulting
    array.

    If it is not possible to find such a value for ans[i] that satisfies the
    condition, then set ans[i] = -1.

    =========================================================
    FUNCTION: vector<int> minBitwiseArray(vector<int>& nums);
    =========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [2,3,5,7]
    Output: [-1,1,4,3]
    Explanation:
        For i = 0, as there is no value for ans[0] that satisfies ans[0] OR (ans[0] + 1) = 2, so ans[0] = -1.
        For i = 1, the smallest ans[1] that satisfies ans[1] OR (ans[1] + 1) = 3 is 1, because 1 OR (1 + 1) = 3.
        For i = 2, the smallest ans[2] that satisfies ans[2] OR (ans[2] + 1) = 5 is 4, because 4 OR (4 + 1) = 5.
        For i = 3, the smallest ans[3] that satisfies ans[3] OR (ans[3] + 1) = 7 is 3, because 3 OR (3 + 1) = 7.


    --- Example 2 ---
    Input: nums = [11,13,31]
    Output: [9,12,15]
    Explanation:
        For i = 0, the smallest ans[0] that satisfies ans[0] OR (ans[0] + 1) = 11 is 9, because 9 OR (9 + 1) = 11.
        For i = 1, the smallest ans[1] that satisfies ans[1] OR (ans[1] + 1) = 13 is 12, because 12 OR (12 + 1) = 13.
        For i = 2, the smallest ans[2] that satisfies ans[2] OR (ans[2] + 1) = 31 is 15, because 15 OR (15 + 1) = 31.


    *** Constraints ***
    1 <= nums.length <= 100
    2 <= nums[i] <= 10^9
    nums[i] is a prime number.

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    I solved this problem by noticing a pattern in the given examples:

        Input | Answer | Input | Answer
        -------------------------------
        2           -1      10
        3            1      11       1
        5            4     101     100
        7            3     111      11
        11           9    1011    1001
        13          12    1101    1100
        31          15   11111    1111

    + If the binary ends in 01 (like 5 and 13), then the answer is to just
      subtract 1.

    + If the binary consists of all 1s (like 7 and 31), the answer is to remove
      the leftmost 1.

    + "11" is the only one that doesn't fit into the above. I noticed that the
      answer involves removing that 2nd 1 from the right (1011 -> 1001). And in
      general, the approach is to remove the leftmost 1 of the longest chain of
      1s starting from the right. So for 11, we remove the 2nd 1 to make it
      1001, because if we add a 1, it can be ORed back to 11:

           1001
        OR 1010
           ----
           1011

    This holds true for all numbers except for 2.



    Some more examples:

    1111111 (127) would become 0111111 | 1000000 (63 | 64).

       0111111
    OR 1000000
       -------
       1111111

    11101111 (239) would become 11100111 | 11101000 (231 | 232).


       11100111
    OR 11101000
       --------
       11101111

    1110001 (113) would become 1110000 | 1110001 (112 | 113).


       1110000
    OR 1110001
       -------
       1110001

    Approach

    If the number is 2, add -1 to the answer array. Else, start checking the
    bits from the right. Move left everytime there is a 1. When the first 0 is
    found, remove the 1 to the right. This minimizes the number as much as
    possible.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  48.71% */

/* Time  Complexity: O(n * logk) */
/* Space Complexity: O(1)        */
class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums)
    {
        const int N = nums.size();
        vector<int> ans(N);

        for (int i = 0; i < nums.size(); i++)
        {
            int num = nums[i];

            if (num == 2)
            {
                ans[i] = -1;
                continue;
            }

            int num_copy = num;
            int count = 0;

            // Count consecutive 1s from the right
            while ((num & 1) == 1)
            {
                count++;
                num >>= 1;
            }

            // [count]th bit is the position of the last 1, like 100111 (count = 3)
            // Subtract the bit                                     ^
            ans[i] = num_copy - (1 << (count - 1));
        }

        return ans;
    }
};
