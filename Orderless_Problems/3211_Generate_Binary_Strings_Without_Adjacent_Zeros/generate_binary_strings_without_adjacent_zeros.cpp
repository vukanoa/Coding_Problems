/*
    ==============
    === MEDIUM ===
    ==============

    ====================================================
    3211) Generate Binary Strings Without Adjacent Zeros
    ====================================================

    ============
    Description:
    ============

    You are given a positive integer n.

    A binary string x is valid if all substrings of x of length 2 contain at
    least one "1".

    Return all valid strings with length n, in any order.

    =============================================
    FUNCTION: vector<string> validStrings(int n);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3
    Output: ["010","011","101","110","111"]
    Explanation:
    The valid strings of length 3 are: "010", "011", "101", "110", and "111".

    --- Example 2 ---
    Input: n = 1
    Output: ["0","1"]
    Explanation:
    The valid strings of length 1 are: "0" and "1".


    *** Constraints ***
    1 <= n <= 18

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Backtracking.

*/

/* Time  Beats: 79.91% */
/* Space Beats: 78.25% */

/* Time  Complexity: O(2^N) */
/* Space Complexity: O(N)   */
class Solution {
public:
    vector<string> validStrings(int n)
    {
        vector<string> result;
        string start_with_0 = "0";
        string start_with_1 = "1";

        backtracking(0, start_with_0, n, result);
        backtracking(1, start_with_1, n, result);

        return result;
    }

private:
    void backtracking(int prev, string& str, int n, vector<string>& result)
    {
        if (str.length() == n)
        {
            result.push_back(str);
            return;
        }

        str.push_back('1');
        backtracking(1, str, n, result);
        str.pop_back();

        if (prev == 1)
        {
            str.push_back('0');
            backtracking(0, str, n, result);
            str.pop_back();
        }
    }
};
