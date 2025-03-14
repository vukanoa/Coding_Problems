/*
    ============
    === EASY ===
    ============

    ===========================
    3174) Clear Digits
    ===========================

    ============
    Description:
    ============

    You are given a string s.

    Your task is to remove all digits by doing this operation repeatedly:

        Delete the first digit and the closest non-digit character to its left.

    Return the resulting string after removing all digits.

    =======================================
    FUNCTION: string clearDigits(string s);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abc"
    Output: "abc"
    Explanation:
    There is no digit in the string.

    --- Example 2 ---
    Input: s = "cb34"
    Output: ""
    Explanation:
    First, we apply the operation on s[2], and s becomes "c4".
    Then we apply the operation on s[1], and s becomes "".


    *** Constraints ***
    1 <= s.length <= 100
    s consists only of lowercase English letters and digits.
    The input is generated such that it is possible to delete all digits

*/

#include <stack>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  52.72% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string clearDigits(string s)
    {
        const int N = s.length();
        stack<char> stack;

        string result = "";

        int digits = 0;
        for (const char chr : s)
        {
            if (chr >= '0' && chr <= '9') // Is Digit
                result.pop_back();
            else
                result += chr;
        }

        return result;
    }
};
