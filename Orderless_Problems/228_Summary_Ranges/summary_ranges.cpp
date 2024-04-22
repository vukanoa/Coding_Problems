#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    ===========================
    228) Summary Ranges
    ===========================

    ============
    Description:
    ============

    You are given a sorted unique integer array nums.

    A range [a,b] is the set of all integers from a to b (inclusive).

    Return the smallest sorted list of ranges that cover all the numbers in the
    array exactly. That is, each element of nums is covered by exactly one of
    the ranges, and there is no integer x such that x is in one of the ranges
    but not in nums.

    Each range [a,b] in the list should be output as:

        "a->b" if a != b
        "a" if a == b


    ==========================================================
    FUNCTION: vector<string> summaryRanges(vector<int>& nums);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [0,1,2,4,5,7]
    Output: ["0->2","4->5","7"]
    Explanation: The ranges are:
    [0,2] --> "0->2"
    [4,5] --> "4->5"
    [7,7] --> "7"

    --- Example 2 ---
    Input: nums = [0,2,3,4,6,8,9]
    Output: ["0","2->4","6","8->9"]
    Explanation: The ranges are:
    [0,0] --> "0"
    [2,4] --> "2->4"
    [6,6] --> "6"
    [8,9] --> "8->9"


    *** Constraints ***
    0 <= nums.length <= 20
    -2^31 <= nums[i] <= 2^31 - 1
    All the values of nums are unique.
    nums is sorted in ascending order.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive. You don't have to come up with some crazy Solution, just try to
    code it up and you'll realize that you can.

    There are only two important things in this Solution:
        1. Notice that we are essentially being asked to return one range per
           one consecutive "chunk" of numbers. In other words, if all the
           elements in "nums" are consectuve, then we'll only have a single
           range starting at nums[0] and ending at nums[N-1].

        2. In C++, you're allowed to write it like this:
               results.push_back(std::to_string(nums[start]) + "->" + std::to_string(nums[inner]));

*/

/* Time  Beats: 35.79% */
/* Space Beats: 84.59% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */ // "results" isn't counted as extra space
class Solution {
public:
    std::vector<std::string> summaryRanges(std::vector<int>& nums)
    {
        if (nums.empty())
            return {};

        const int N = nums.size();
        std::vector<std::string> results;

        int start = 0;
        while (start < N)
        {
            int inner;
            for (inner = start; inner < N; inner++)
            {
                if (inner+1 == N || nums[inner]+1 < nums[inner+1])
                {
                    if (inner-start+1 == 1)
                        results.push_back(std::to_string(nums[start]));
                    else
                        results.push_back(std::to_string(nums[start]) + "->" + std::to_string(nums[inner]));

                    break;
                }
            }

            start = inner+1;
        }

        return results;
    }
};
