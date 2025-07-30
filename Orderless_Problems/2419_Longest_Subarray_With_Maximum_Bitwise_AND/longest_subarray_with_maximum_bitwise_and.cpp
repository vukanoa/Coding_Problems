/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    2419) Longest Subarray With Maximum Bitwise AND
    ===============================================

    ============
    Description:
    ============

    You are given an integer array nums of size n.

    Consider a non-empty subarray from nums that has the maximum possible
    bitwise AND.

        In other words, let k be the maximum value of the bitwise AND of any
        subarray of nums. Then, only subarrays with a bitwise AND equal to k
        should be considered.

    Return the length of the longest such subarray.

    The bitwise AND of an array is the bitwise AND of all the numbers in it.

    A subarray is a contiguous sequence of elements within an array.

    =================================================
    FUNCTION: int longestSubarray(vector<int>& nums);
    =================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3,3,2,2]
    Output: 2
    Explanation:
    The maximum possible bitwise AND of a subarray is 3.
    The longest subarray with that value is [3,3], so we return 2.

    --- Example 2 ---
    Input: nums = [1,2,3,4]
    Output: 1
    Explanation:
    The maximum possible bitwise AND of a subarray is 4.
    The longest subarray with that value is [4], so we return 1.


    *** Constraints ***
    1 <= nums.length <= 10^5
    1 <= nums[i] <= 10^6

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The biggest "bitwise AND" value is CERTAINLY the max element of the "nums".

    How do we know that?
    If you try to represent every number from "nums" in binary, you'll see that
    if you do "bitwise AND" of the max element with ANY OTHER non-max
    element(i.e. any element that is LESS than the max element), you'd
    certainly DECREASE the value.

    Therefore, it's better not to touch it at all - Hence, max element is the
    biggest obtainable "bitwise AND" value.


    Once you realize that, the problem becomes trivial. It's a standard
    "Sliding Window" technique, or it could also be considered "Two Pointers".

*/

/* Time  Beats: 100.00% */
/* Space Beats:  86.04% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int longestSubarray(vector<int>& nums)
    {
        const int N = nums.size();
        int result = 1;

        int L = 0;
        int R = 0;

        int max_bitwise_AND = *max_element(nums.begin(), nums.end());

        while (R < N)
        {
            if ((nums[R] & max_bitwise_AND) != max_bitwise_AND)
                L = R+1;

            result = max(result, R - L + 1);

            // Increment
            R++;
        }

        return result;
    }
};
