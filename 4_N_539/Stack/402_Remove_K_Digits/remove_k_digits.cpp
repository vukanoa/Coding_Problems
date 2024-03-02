#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    402) Remove K Digits
    ===========================

    ============
    Description:
    ============

    Given string num representing a non-negative integer num, and an integer k,
    return the smallest possible integer after removing k digits from num.

    ==================================================
    FUNCTION: string removeKDigits(string num, int k);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = "1432219", k = 3
    Output: "1219"
    Explanation: Remove the three digits 4, 3, and 2 to form the new number
                 1219 which is the smallest.


    --- Example 2 ---
    Input: num = "10200", k = 1
    Output: "200"
    Explanation: Remove the leading 1 and the number is 200. Note that the
                 output must not contain leading zeroes.


    --- Example 3 ---
    Input: num = "10", k = 2
    Output: "0"
    Explanation: Remove all the digits from the number and it is left with
                 nothing which is 0.



    *** Constraints ***
    1 <= k <= num.length <= 10^5
    num consists of only digits.
    num does not have any leading zeros except for the zero itself.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.30% */
/* Space Beats: 51.91% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string removeKdigits(std::string num, int k)
    {
        std::string stack;

        for (int i = 0; i < num.length(); i++)
        {
            while (k > 0 && !stack.empty() && stack.back() > num[i])
            {
                stack.pop_back();
                k--;
            }

            stack.push_back(num[i]);
        }

        while (k-- > 0 && !stack.empty())
            stack.pop_back();

        // Remove leading zeroes
        stack.erase(0, stack.find_first_not_of('0'));

        return stack != "" ? stack : "0";
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Absolutely equivalent to the one above, however this one makes sure there
    aren't any leading zeroes to begin with, whereas the above Solution has
    leading zeroes but removes them before returning the string, i.e. "stack".

*/

/* Time  Beats: 95.52% */
/* Space Beats: 40.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    std::string removeKdigits(std::string num, int k)
    {
        std::string stack;

        for (int i = 0; i < num.length(); i++)
        {
            while (k > 0 && !stack.empty() && stack.back() > num[i])
            {
                stack.pop_back();
                k--;
            }

            if (!(stack.empty() && num[i] == '0')) // To prevent leading zeroes
                stack.push_back(num[i]);
        }

        while (k-- > 0 && !stack.empty())
            stack.pop_back();

        return stack != "" ? stack : "0";
    }
};
