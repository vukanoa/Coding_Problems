/*
    ============
    === EASY ===
    ============

    ===========================
    917) Reverse Only Letters
    ===========================

    ============
    Description:
    ============

    Given a string s, reverse the string according to the following rules:

        + All the characters that are not English letters remain in the same
          position.

        + All the English letters (lowercase or uppercase) should be reversed.

    Return s after reversing it.

    ==============================================
    FUNCTION: string reverseOnlyLetters(string s);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "ab-cd"
    Output: "dc-ba"

    --- Example 2 ---
    Input: s = "a-bC-dEf-ghIj"
    Output: "j-Ih-gfE-dCba"

    --- Example 3 ---
    Input: s = "Test1ng-Leet=code-Q!"
    Output: "Qedo1ct-eeLg=ntse-T!"

    *** Constraints ***
    1 <= s.length <= 100
    s consists of characters with ASCII values in the range [33, 122].
    s does not contain '\"' or '\\'.

*/

#include <stack>
#include <string>
#include <cctype>
using namespace std;


/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:   5.20% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string reverseOnlyLetters(string s)
    {
        stack<char> letter_stack;
        for (char character : s)
        {
            if (isalpha(character))
            {
                letter_stack.push(character);
            }
        }

        string result;
        for (const char& chr : s)
        {
            if (isalpha(chr))
            {
                result += letter_stack.top();
                letter_stack.pop();
            }
            else
            {
                result += chr;
            }
        }

        return result;
    }
};
