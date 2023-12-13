#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================================
    1849) Splitting a String Into Descending Consecutive Values
    ===========================================================

    ============
    Description:
    ============

    You are given a string s that consists of only digits.

    Check if we can split s into two or more non-empty substrings such that the
    numerical values of the substrings are in descending order and the
    difference between numerical values of every two adjacent substrings is
    equal to 1.

        For example, the string s = "0090089" can be split into ["0090", "089"]
        with numerical values [90,89]. The values are in descending order and
        adjacent values differ by 1, so this way is valid.  Another example,
        the string s = "001" can be split into ["0", "01"], ["00", "1"], or
        ["0", "0", "1"]. However all the ways are invalid because they have
        numerical values [0,1], [0,1], and [0,0,1] respectively, all of which
        are not in descending order.

    Return true if it is possible to split s as described above, or false
    otherwise.

    A substring is a contiguous sequence of characters in a string.

    =====================================
    FUNCTION: bool splitString(string s);
    =====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "1234"
    Output: false
    Explanation: There is no valid way to split s.


    --- Example 2 ---
    Input: s = "050043"
    Output: true
    Explanation: s can be split into ["05", "004", "3"] with numerical values
    [5,4,3].  The values are in descending order with adjacent values differing
    by 1.


    --- Example 3 ---
    Input: s = "9080701"
    Output: false
    Explanation: There is no valid way to split s.


    *** Constraints ***
    1 <= s.length <= 20
    s only consists of digits.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Classic Backtracking.

*/

/* Time  Beats:  100% */
/* Space Beats: 42.61% */

/* Time  Complexity: O(n * 2^n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool splitString(std::string s)
    {
        std::vector<unsigned long long> numbers;

        return backtracking(s, numbers, 0, "");
    }

private:
    bool backtracking(std::string& s, std::vector<unsigned long long>& numbers, int start, std::string curr_str)
    {
        if (start == s.length())
            return numbers.size() >= 2;

        for (int i = start; i < s.length(); i++)
        {
            curr_str += s[i];
            if (curr_str.length() == 20) // Since ULLONG_MAX is 20 characters
                return false;

            // If we didn't return false above and it was a value of 20 digits
            // that is greater than ULLONG_MAX, then we'd get an error called
            // "out of bound" from function std::stoull
            unsigned long long tmp_int = std::stoull(curr_str);

            if (!numbers.empty() && (numbers.back() <= tmp_int || numbers.back() - tmp_int != 1))
                continue;

            numbers.push_back(tmp_int);

            if (backtracking(s, numbers, i+1, ""))
                return true;

            numbers.pop_back();
        }

        return false;
    }
};
