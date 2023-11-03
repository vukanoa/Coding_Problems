#include <iostream>
#include <vector>
#include <sstream>

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

/* Time  Beats: 83.43% */
/* Space Beats: 17.54% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string removeKdigits(std::string num, int k)
    {
        if (num.length() == k)
            return "0";

        std::vector<char> stack;
        int i = 0;
        while (i < num.length())
        {
            while (k > 0 && !stack.empty() && stack.back() > num[i]) // We can compare characters
            {
                k--;
                stack.pop_back();
            }

            if (!stack.empty())
                stack.push_back(num[i]);
            else if (num[i] != '0') // Make sure there aren't any leading zeros
                stack.push_back(num[i]);

            i++;
        }

        // If, say, all the numbers were increasing: num="12345", k=2
        while (!stack.empty() && k-- > 0)
            stack.pop_back();

        // Make a string
        std::ostringstream out;
        for (char& c : stack)
            out << c;

        return out.str() == "" ? "0" : out.str();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same IDEA, different handling of leading zeros.

*/

/* Time  Beats: 87.38% */
/* Space Beats: 17.54% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    std::string removeKdigits(std::string num, int k)
    {
        if (num.length() == k)
            return "0";

        std::vector<char> stack;
        for (int i = 0; i < num.length(); i++)
        {
            while (k > 0 && !stack.empty() && stack.back() > num[i]) // We can compare characters
            {
                k--;
                stack.pop_back();
            }

            stack.push_back(num[i]);
        }

        // If, say, all the numbers were increasing: num="12345", k=2
        while (!stack.empty() && k-- > 0)
            stack.pop_back();

        // Make sure leading zeros are ignored
        int i = 0;
        while (i < stack.size())
        {
            if (stack[i] == '0')
                i++;
            else
                break;
        }

        // Make a string
        std::ostringstream out;
        while (i < stack.size())
            out << stack[i++];

        return out.str() == "" ? "0" : out.str();
    }
};
