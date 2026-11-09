/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    3955) Valid Binary Strings with Cost Limit
    ==========================================

    ============
    Description:
    ============

    You are given two integers n and k.

    The cost of a binary string s is defined as the sum of all indices i
    (0-based) such that s[i] == '1'.

    A binary string is considered valid if:

        + It does not contain two consecutive '1' characters.
        + Its cost is less than or equal to k.

    Return a list of all valid binary strings of length n in any order.

    ============================================================
    FUNCTION: vector<string> generateValidStrings(int n, int k);
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 3, k = 1
    Output: ["000","010","100"]
    Explanation:
    The binary strings of length 3 without consecutive '1' characters are:
        "000" : cost = 0
        "100" : cost = 0
        "010" : cost = 1
        "001" : cost = 2
        "101" : cost = 0 + 2 = 2
    Among these, the strings with cost less than or equal to k = 1 are "000",
    "010" and "100".
    Thus, the valid strings are ["000", "010", "100"].

    --- Example 2 ---
    Input: n = 1, k = 0
    Output: ["0","1"]
    Explanation:
    The valid binary strings of length 1 are "0" and "1".
    Thus the answer is ["0", "1"].


    *** Constraints ***
    1 <= n <= 12
    0 <= k <= n * (n - 1) / 2

*/

#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 22.27% */
/* Space Beats: 63.37% */

/* Time  Complexity: O(N * 2^N) */
/* Space Complexity: O(N)       */
class Solution {
public:
    vector<string> generateValidStrings(int n, int k)
    {
        vector<string> result;
        result.reserve((1 << n)); // To prevent reallocations

        for (int i = 0; i < (1 << n); i++)
        {
            string bin_str = binary_string(i, n);

            bool valid = true;
            int cost = 0;
            for (int j = 0; j < n; j++)
            {
                if ((j+1 < n) && bin_str[j] == '1' && bin_str[j+1] == '1')
                {
                    valid = false;
                    break;
                }

                if (bin_str[j] == '1')
                    cost += j;
            }

            if (valid && (cost <= k))
                result.push_back(bin_str);
        }

        return result;
    }

private:
    string binary_string(unsigned int x, int n)
    {
        string s(n, '0');

        for (size_t i = 0; i < n; ++i)
        {
            s[n - 1 - i] = char('0' + (x & 1));
            x >>= 1;
        }

        return s;
    }
};
