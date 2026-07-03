/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    3941) Password Strength
    ===========================

    ============
    Description:
    ============

    You are given a string password.

    The strength of the password is calculated based on the following rules:

        1 point for each distinct lowercase letter ('a' to 'z').
        2 points for each distinct uppercase letter ('A' to 'Z').
        3 points for each distinct digit ('0' to '9').
        5 points for each distinct special character from the set "!@#$".

    Each character contributes at most once, even if it appears multiple times.

    Return an integer denoting the strength of the password.

    ================================================
    FUNCTION: int passwordStrength(string password);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: password = "aA1!"
    Output: 11
    Explanation:
        The distinct characters are 'a', 'A', '1' and '!'.
        Thus, the strength = 1 + 2 + 3 + 5 = 11.

    --- Example 2 ---
    Input: password = "bbB11#"
    Output: 11
    Explanation:
        The distinct characters are 'b', 'B', '1' and '#'.
        Thus, the strength = 1 + 2 + 3 + 5 = 11.


    *** Constraints ***
    1 <= password.length <= 10^5
    password consists of lowercase and uppercase English letters, digits, and
    special characters from "!@#$".

*/

#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem. Pointless problem.

*/

/* Time  Beats: 52.69% */
/* Space Beats: 11.57% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int passwordStrength(string password)
    {
        const int N = password.size();
        int result = 0;

        unordered_set<char> uset_lowercase;
        unordered_set<char> uset_uppercase;
        unordered_set<char> uset_digit;
        unordered_set<char> uset_special;

        for (const char& chr : password)
        {
            if (islower(chr))
                uset_lowercase.insert(chr);
            else if (isupper(chr))
                uset_uppercase.insert(chr);
            else if (isdigit(chr))
                uset_digit.insert(chr);
            else
                uset_special.insert(chr);
        }



        result = 1 * uset_lowercase.size() +
                 2 * uset_uppercase.size() +
                 3 * uset_digit.size()     +
                 5 * uset_special.size();
                

        return result;
    }
};
