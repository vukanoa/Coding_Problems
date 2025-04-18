/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    38) Count and Say
    ===========================

    ============
    Description:
    ============

    The count-and-say sequence is a sequence of digit strings defined by the
    recursive formula:

        countAndSay(1) = "1"

        countAndSay(n) is the run-length encoding of countAndSay(n - 1).

    Run-length encoding (RLE) is a string compression method that works by
    replacing consecutive identical characters (repeated 2 or more times) with
    the concatenation of the character and the number marking the count of the
    characters (length of the run). For example, to compress the string
    "3322251" we replace "33" with "23", replace "222" with "32", replace "5"
    with "15" and replace "1" with "11". Thus the compressed string becomes
    "23321511".

    Given a positive integer n, return the nth element of the count-and-say
    sequence.


    ---------------
    -- Follow Up --
    ---------------

    Could you solve it iteratively?


    ====================================
    FUNCTION: string countAndSay(int n);
    ====================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4
    Output: "1211"
    Explanation:
    countAndSay(1) = "1"
    countAndSay(2) = RLE of "1" = "11"
    countAndSay(3) = RLE of "11" = "21"
    countAndSay(4) = RLE of "21" = "1211"

    --- Example 2 ---
    Input: n = 1
    Output: "1"
    Explanation:
    This is the base case.


    *** Constraints ***
    1 <= n <= 30

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Tail-recursion.

*/

/* Time  Beats: 41.53% */
/* Space Beats: 27.67% */

/* Time  Complexity: O(2^N) */
/* Space Complexity: O(2^N) */
class Solution {
public:
    string countAndSay(int n)
    {
        string res = "1";
        helper(1, n, res);
        return res;
    }

    void helper(int idx, int n, string& result)
    {
        if (idx >= n)
            return;

        string prev_str = result;
        result = "";

        unsigned L = 0;
        unsigned R = 0;

        int count = 0;
        while (R < prev_str.size())
        {
            if (prev_str[L] != prev_str[R])
            {
                result += to_string(count) + prev_str[L];
                L = R;
                count = 1;
            }
            else
                count++;

            // Increment
            R++;
        }

        result += to_string(count) + prev_str[L];

        return helper(idx + 1, n, result); // Tail-recursion
    }
};
