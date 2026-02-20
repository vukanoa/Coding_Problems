/*
    ============
    === HARD ===
    ============

    ===========================
    761) Special Binary String
    ===========================

    ============
    Description:
    ============

    Special binary strings are binary strings with the following two
    properties:

        The number of 0's is equal to the number of 1's.
        Every prefix of the binary string has at least as many 1's as 0's.

    You are given a special binary string s.

    A move consists of choosing two consecutive, non-empty, special substrings
    of s, and swapping them. Two strings are consecutive if the last character
    of the first string is exactly one index before the first character of the
    second string.

    Return the lexicographically largest resulting string possible after
    applying the mentioned operations on the string.

    ==============================================
    FUNCTION: string makeLargestSpecial(string s);
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "11011000"
    Output: "11100100"
    Explanation: The strings "10" [occuring at s[1]] and "1100" [at s[3]] are swapped.
    This is the lexicographically largest string possible after some number of swaps.

    --- Example 2 ---
    Input: s = "10"
    Output: "10"


    *** Constraints ***
    1 <= s.length <= 50
    s[i] is either '0' or '1'.
    s is a special binary string.

*/

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  59.31% */

/* Time  Complexity: O(N^2 * logN) */
/* Space Complexity: O(N^2)        */
class Solution {
public:
    string makeLargestSpecial(string s)
    {
        const int N = s.size();
        const int BALANCED_STATE = 0;

        vector<string> result_vec;
        int balance = 0;

        int left  = 0;
        int right = 0;
        while (right < N)
        {
            // Track balance
            balance += (s[right] == '1') ? 1 : -1;
            
            if (balance == BALANCED_STATE)
            {
                // Recursively maximize inner part, wrap with 1...0
                string substr = makeLargestSpecial(s.substr(left + 1, right - left - 1));
                result_vec.push_back('1' + substr + '0');

                left = right + 1; // Move to next potential chunk
            }

            // Increment
            right++;
        }

        /* Sort chunks in DESCENDING order for largest arrangement */
        sort(result_vec.begin(), result_vec.end(), greater<string>());
        
        string result;
        result.reserve(result_vec.size()); // Prevent reallocations

        for (const string& str : result_vec)
            result += str;

        return result;
    }
};
