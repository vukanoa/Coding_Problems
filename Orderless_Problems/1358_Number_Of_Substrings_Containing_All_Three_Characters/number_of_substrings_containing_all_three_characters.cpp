/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================================
    1358) Number of Substrings Containing All Three Characters
    ==========================================================

    ============
    Description:
    ============

    Given a string s consisting only of characters a, b and c.

    Return the number of substrings containing at least one occurrence of all
    these characters a, b and c.

    ===========================================
    FUNCTION: int numberOfSubstrings(string s);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcabc"
    Output: 10
    Explanation: The substrings containing at least one occurrence of the
                 characters a, b and c are "abc", "abca", "abcab", "abcabc",
                 "bca", "bcab", "bcabc", "cab", "cabc" and "abc" (again).

    --- Example 2 ---
    Input: s = "aaacb"
    Output: 3
    Explanation: The substrings containing at least one occurrence of the
                 characters a, b and c are "aaacb", "aacb" and "acb".

    --- Example 3 ---
    Input: s = "abc"
    Output: 1


    *** Constraints ***
    3 <= s.length <= 5 x 10^4
    s only consists of a, b or c characters.

*/

#include <string>
#include <unordered_map>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Sliding-Window problem. When counting Substrings, do NOT forget the
    inter-substrings.

    That's precisely why, when we found a valid substring, we don't increment
    our "result" by one, but by: N - R. To take all the inter-substrings into
    account as well.

*/

/* Time  Beats:  9.68% */
/* Space Beats: 14.74% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numberOfSubstrings(string s)
    {
        const int N = s.length();
        int result = 0;

        int L = 0;
        int R = 0;
        unordered_map<char,int> counter;

        while (R < N)
        {
            char curr_chr = s[R];

            counter[curr_chr]++;

            while (counter.size() == 3)
            {
                result += N - R;

                char leftmost_chr = s[L];

                counter[leftmost_chr]--;
                if (counter[leftmost_chr] == 0)
                    counter.erase(leftmost_chr);

                // Slide-Window
                L++;
            }

            // Increment
            R++;
        }

        return result;
    }
};
