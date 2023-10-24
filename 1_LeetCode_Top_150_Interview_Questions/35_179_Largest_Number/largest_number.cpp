#include <iostream>
#include <vector>
#include <algorithm>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    179) Largest Number
    ===========================

    ============
    Description:
    ============

    Given a list of non-negative integers nums, arrange them such that they
    form the largest number and return it.

    Since the result may be very large, so you need to return a string instead
    of an integer.

    ==================================================
    FUNCTION: string largestNumber(vector<int>& nums);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [10,2]
    Output: "210"

    --- Example 2 ---
    Input: nums = [3,30,34,5,9]
    Output: "9534330"


    *** Constraints ***
    1 <= nums.length <= 100
    0 <= nums[i] <= 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    --- Example 2 ---
    Input: nums = [3,30,34,5,9]

    How can we know which is the most optimal order?
    Well, order by the largest first digit.

    What if first digits are the same as with: 33 and 34?
    Then take the one that is larger.

    What if first digits are the same, but the one doesn't have the 2nd digit
    whereas the other has a 2nd digit of 0?
        3 vs 30

    How can we decide which one should be put first?

    When we look at them:
        1) 330
        2) 303

    it's obvious to us, but how are we going to compare it?
    We cannot use number comparison since in this case, 30 is greater than 3,
    but 303 is not the order we should put these numbers in.

    So how can we do that?

    Simply compare strings "330" and "303".

    For that we need to convert the entire vector "nums" to strings.
    After that just sort the vector but using our own custom comparator.

    That's it.

*/

/* Time  Beats:  100% */
/* Space Beats: 71.79% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string largestNumber(std::vector<int>& nums)
    {
        std::vector<std::string> nums_str;

        for (int& num : nums)
            nums_str.push_back(std::to_string(num));

        std::sort(nums_str.begin(), nums_str.end(), [&](std::string& n1, std::string& n2){ return n1 + n2 > n2 + n1; });

        std::string result = "";

        for (std::string& str : nums_str)
            result += str;

        while(result[0] == '0' && result.length() > 1)
            result.erase(0, 1);

        return result;
    }
};
