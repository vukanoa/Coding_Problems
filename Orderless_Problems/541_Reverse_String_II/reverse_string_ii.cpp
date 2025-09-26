/*
    ============
    === EASY ===
    ============

    ===========================
    541) Reverse String II
    ===========================

    ============
    Description:
    ============

    Given a string s and an integer k, reverse the first k characters for every
    2k characters counting from the start of the string.

    If there are fewer than k characters left, reverse all of them. If there
    are less than 2k but greater than or equal to k characters, then reverse
    the first k characters and leave the other as original.

    =============================================
    FUNCTION: string reverseStr(string s, int k);
    =============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcdefg", k = 2
    Output: "bacdfeg"

    --- Example 2 ---
    Input: s = "abcd", k = 2
    Output: "bacd"


    *** Constraints ***
    1 <= s.length <= 10^4
    s consists of only lowercase English letters.
    1 <= k <= 10^4

*/

#include <algorithm>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The only "difficult" part in this one is that you can get in a situation
    where you don't have k elements from certain index, due to lack of the
    characters.

    One such trivial example is:

        s = "a"
        k = 2

    Therefore we need to have these "safe guards" that are not really pretty.

*/

/* Time  Beats: 6.39% */
/* Space Beats: 5.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string reverseStr(string s, int k)
    {
        const int N = s.length();
        string result = "";

        for (int i = 0; i < N; i += 2 * k)
        {
            // Safe guard 1
            if (i + k >= N)
            {
                string one = s.substr(i);
                reverse(one.begin(), one.end());
                result += one;
                break;
            }

            string one = s.substr(i    , k); // Reverse this one

            // Safe guard 2
            if (i + 2 * k >= N)
            {
                string two = s.substr(i);
                reverse(one.begin(), one.end());
                result += one + s.substr(i + k);
                break;
            }

            string two = s.substr(i + k, k);
            reverse(one.begin(), one.end());

            result += one + two;
        }
        
        return result;
    }
};
