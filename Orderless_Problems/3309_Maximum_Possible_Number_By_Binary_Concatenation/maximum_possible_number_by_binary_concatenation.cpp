/*
    ==============
    === MEDIUM ===
    ==============

    =====================================================
    3309) Maximum Possible Number by Binary Contamination
    =====================================================

    ============
    Description:
    ============

    You are given an array of integers nums of size 3.

    Return the maximum possible number whose binary representation can be
    formed by concatenating the binary representation of all elements in nums
    in some order.

    =====
    Note: that the binary representation of any number does not contain leading
          zeros.
    =====

    ===============================================
    FUNCTION: int maxGoodNumber(vector<int>& nums);
    ===============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: nums = [1,2,3]
    Output: 30
    Explanation: Concatenate the numbers in the order [3, 1, 2] to get the
                 result "11110", which is the binary representation of 30.

    --- Example 2 ---
    Input: nums = [2,8,16]
    Output: 1296
    Explanation: Concatenate the numbers in the order [2, 8, 16] to get the
                 result "10100010000", which is the binary representation of
                 1296.


    *** Constraints ***
    nums.length == 3
    1 <= nums[i] <= 127

*/

#include <sstream>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    You have to know how to convert a number to its binary representation in
    string. It's done like this:

        for (int idx = 7; idx >= 0; idx--)
        {
            if (nums[i] & (1 << idx))
                out << 1;
            else
                out << 0;
        }

    However, we had to modify this a little bit because we do NOT want any
    leading zeroes. Take a look down below at what we've done. I'm sure you'll
    understand it.


    Next, once you have that, and since there are always exactly 3 elements in
    "nums", then there is exactly 3! (3 factorial) permutations, which is 6.

    We can write that manually.

    However, before we do that, we need to convert a string of binary
    representation to an integer.

    How do we do that?

    Simply:
        std::stoi(string_binary_representation, nullptr, 2);

    Now just write all 6 permutations and obtain integers from it and return the
    largest one.

    This one is not difficult, it's just requires you to know these conversions

*/

/* Time  Beats: 100.00% */
/* Space Beats: 51.05%  */

/* Time  Complexity: O(1) */
/* Space Complexity: O(1) */
class Solution {
public:
    int maxGoodNumber(vector<int>& nums)
    {
        const int FIXED_SIZE_THREE = 3;
        int result = 0;

        vector<string> bin_str(3);

        for (int i = 0; i < FIXED_SIZE_THREE; i++)
        {
            ostringstream out;
            bool leading_zero = true;

            for (int idx = 7; idx >= 0; idx--)
            {
                if (nums[i] & (1 << idx))
                {
                    out << 1;
                    leading_zero = false;
                }
                else if ( ! leading_zero)
                    out << 0;
            }

            bin_str[i] = out.str();
        }

        // Since nums is ALWAYS of size 3, then there are 3! == 6 permutations
        string one   = bin_str[0] + bin_str[1] + bin_str[2];
        string two   = bin_str[0] + bin_str[2] + bin_str[1];
        string three = bin_str[1] + bin_str[0] + bin_str[2];
        string four  = bin_str[1] + bin_str[2] + bin_str[0];
        string five  = bin_str[2] + bin_str[0] + bin_str[1];
        string six   = bin_str[2] + bin_str[1] + bin_str[0];

        int number_1 = std::stoi(one,   nullptr, 2);
        int number_2 = std::stoi(two,   nullptr, 2);
        int number_3 = std::stoi(three, nullptr, 2);
        int number_4 = std::stoi(four,  nullptr, 2);
        int number_5 = std::stoi(five,  nullptr, 2);
        int number_6 = std::stoi(six,   nullptr, 2);

        return max( {number_1, number_2, number_3, number_4, number_5, number_6} );
    }
};
