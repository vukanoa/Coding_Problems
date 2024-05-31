#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    260) Single Number III
    ===========================

    ============
    Description:
    ============

    Given an integer array nums, in which exactly two elements appear only once
    and all the other elements appear exactly twice. Find the two elements that
    appear only once. You can return the answer in any order.

    You must write an algorithm that runs in linear runtime complexity and uses
    only constant extra space.

    ======================================================
    FUNCTION: vector<int> singleNumber(vector<int>& nums);
    ======================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,1,3,2,5]
    Output: [3,5]
    Explanation:  [5, 3] is also a valid answer.

    --- Example 2 ---
    Input: nums = [-1,0]
    Output: [-1,0]

    --- Example 3 ---
    Input: nums = [0,1]
    Output: [1,0]


    *** Constraints ***
    2 <= nums.length <= 3 * 10^4
    -2^31 <= nums[i] <= 2^31 - 1
    Each integer in nums will appear twice, only two integers will appear once.

*/


/*
    ------------
    --- IDEA ---
    ------------

    It would be pretty difficult to come up with this approach in an interview
    if you've never seen it before.

    Let's talk about intuition:

    I assume everyone already knows that a ^ a = 0 and that order for XORing
    doesn't matter at all.

    Now let's consider XOR-ing every element in nums.
    Elements x1 and x2 are our result.

    So if we have:

        nums = [a1, a2, x1, b1, x2, b2, ...]

    What can we say about its XOR?

    You can group pair of equal elements as:
        XOR_nums = (a1 ^ a2) ^ (b1 ^ b2) ^ ... ^ (x1 ^ x2).

    What will be the result of all these bracket, except for the very last one?
    It will be zero.

    So, if we XOR all the values in this vector, we will be left with just XOR
    of two elements which appear only once.

    Now what does it mean if a binary represetantion, of the result of XOR-ing
    two elements, at some position idx has bit 1?

    It means that one of (x1, x2) has bit 1 at that position and the other has
    bit 0.

    So how we can use this?

    Let's say now we will divide our array on this criteria:
    Let's divide our vector using this criteria:

    If at position idx there is bit 1 then we'll call it group 1.
    Otherwise, it's group 2.

    It's obvious that equal numbers will be in the same group because
    they're equal.

    Now let's think about XOR of these two, non-zero, groups.

    However, what will be the remainder? The one group that ISN'T 0?

    But what we will get in remainder? Quite interesting: in remainder
    from group 1 we will have element which contained bit 1 at position i
    and from group 2 element which contained bit 2 at position i. That's
    it, these numbers are our answer

*/

/* Time  Beats: 69.06% */
/* Space Beats: 98.70% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    std::vector<int> singleNumber(std::vector<int>& nums)
    {
        int entire_vec_xor = 0;
        for (const int& num : nums)
            entire_vec_xor ^= num;

        int first_group_xor  = 0;
        int second_group_xor = 0;

        int bit_from_the_right = 0;
        while ( ((entire_vec_xor >> bit_from_the_right) & 1) != 1)
            bit_from_the_right++;

        for (int num : nums)
        {
            if (((num >> bit_from_the_right) & 1) == 1)
                first_group_xor ^= num;
            else
                second_group_xor ^= num;
        }

        return {first_group_xor, second_group_xor};
    }
};
