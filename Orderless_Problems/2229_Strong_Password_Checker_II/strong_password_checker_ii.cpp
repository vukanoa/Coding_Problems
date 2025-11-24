/*
    ============
    === EASY ===
    ============

    ===============================
    2229) Strong Pasword Checker II
    ===============================

    ============
    Description:
    ============

    A password is said to be strong if it satisfies all the following criteria:

        + It has at least 8 characters.

        + It contains at least one lowercase letter.

        + It contains at least one uppercase letter.

        + It contains at least one digit.

        + It contains at least one special character. The special characters are
          the characters in the following string: "!@#$%^&*()-+".

        It does not contain 2 of the same character in adjacent positions
        (i.e., "aab" violates this condition, but "aba" does not).

    Given a string password, return true if it is a strong password. Otherwise,
    return false.

    ========================================================
    FUNCTION: bool strongPasswordCheckerII(string password);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: password = "IloveLe3tcode!"
    Output: true
    Explanation: The password meets all the requirements. Therefore, we return
                 true.

    --- Example 2 ---
    Input: password = "Me+You--IsMyDream"
    Output: false
    Explanation: The password does not contain a digit and also contains 2 of
                 the same character in adjacent positions. Therefore, we return
                 false.

    --- Example 3 ---
    Input: password = "1aB!"
    Output: false
    Explanation: The password does not meet the length requirement. Therefore,
                 we return false.


    *** Constraints ***
    1 <= password.length <= 100
    password consists of letters, digits, and special characters: "!@#$%^&*()-+".

*/

#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Simulation problem.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  23.65% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool strongPasswordCheckerII(string password)
    {
        const int N = password.size();

        if (N < 8)
            return false;

        unordered_set<int> special_chr = {'!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '+'};

        int lowercase = 0;
        int uppercase = 0;
        int digit     = 0;
        int special   = 0;

        for (int i = 0; i < N; i++)
        {
            if (i > 0   && password[i-1] == password[i]) return false;
            if (i < N-1 && password[i+1] == password[i]) return false;

            if (islower(password[i])) lowercase++;
            if (isupper(password[i])) uppercase++;
            if (isdigit(password[i])) digit++;

            if (special_chr.count(password[i]))
                special++;
        }

        return lowercase >= 1 && uppercase >= 1 && digit >= 1 && special >= 1;
    }
};
