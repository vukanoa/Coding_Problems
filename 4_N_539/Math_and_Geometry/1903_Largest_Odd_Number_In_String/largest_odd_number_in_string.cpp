#include <iostream>

/*
    ============
    === EASY ===
    ============

    ==================================
    1903) Largest Odd Number in String
    ==================================

    ============
    Description:
    ============

    You are given a string num, representing a large integer. Return the
    largest-valued odd integer (as a string) that is a non-empty substring of
    num, or an empty string "" if no odd integer exists.

    A substring is a contiguous sequence of characters within a string.

    ==============================================
    FUNCTION: string largestOddNumber(string num);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = "52"
    Output: "5"
    Explanation: The only non-empty substrings are "5", "2", and "52". "5" is
                 the only odd number.


    --- Example 2 ---
    Input: num = "4206"
    Output: ""
    Explanation: There are no odd numbers in "4206".


    --- Example 3 ---
    Input: num = "35427"
    Output: "35427"
    Explanation: "35427" is already an odd number.


    *** Constraints ***
    1 <= num.length <= 10^5
    num only consists of digits and does not contain any leading zeros.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 51.31% */
/* Space Beats: 87.98% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    string largestOddNumber(string num)
    {
        if (static_cast<int>((num[num.size()-1])) % 2 != 0)
            return num;

        const int n = num.size();
        int e = 0;

        for (; e < n; e++)
        {
            if( static_cast<int>((num[e])) % 2 != 0)
                break;
        }

        if (e == n)
            return "";

        e = n-2;

        while (e >= 0 && static_cast<int>((num[e])) % 2 == 0)
            e--;

        return num.substr(0, e+1);
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 21.23% */
/* Space Beats: 56.56% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    string largestOddNumber(string num)
    {
        int idx = num.length() - 1;

        // num[idx] - '0' converts the number character into an integer
        // & 1 checks whether or not the number is odd
        while (idx >= 0 && ((num[idx] - '0') & 1) == 0)
            idx--;

        // return the substring we found based on the index we stopped at
        return num.substr(0, idx + 1);
    }
};
