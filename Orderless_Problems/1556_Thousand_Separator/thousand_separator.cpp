/*
    ============
    === EASY ===
    ============

    ===========================
    1556) Thousand Separator
    ===========================

    ============
    Description:
    ============

    Given an integer n, add a dot (".") as the thousands separator and return
    it in string format.

    ==========================================
    FUNCTION: string thousandSeparator(int n);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 987
    Output: "987"

    --- Example 2 ---
    Input: n = 1234
    Output: "1.234"


    *** Constraints ***
    0 <= n <= 2^31 - 1

*/

#include <string>
using namespace std;

class Solution {
public:
    string thousandSeparator(int n)
    {
        if (n < 1000)
            return to_string(n);

        string result = "";

        string str = to_string(n);
        const int N = str.length();

        for (int i = 0; i < N; i++)
        {

        }
    }
};
