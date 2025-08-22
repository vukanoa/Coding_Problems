/*
    ==============
    === MEDIUM ===
    ==============

    =================================================================
    2734) Lexicographically Smallest String After Substring Operation
    =================================================================

    ============
    Description:
    ============

    Given a string s consisting of lowercase English letters. Perform the
    following operation:

        Select any non-empty substring then replace every letter of the
        substring with the preceding letter of the English alphabet. For
        example, 'b' is converted to 'a', and 'a' is converted to 'z'.

    Return the lexicographically smallest string after performing the
    operation.

    ==========================================
    FUNCTION: string smallestString(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "cbabc"
    Output: "baabc"
    Explanation:
    Perform the operation on the substring starting at index 0, and ending at
    index 1 inclusive.

    --- Example 2 ---
    Input: s = "aa"
    Output: "az"
    Explanation:
    Perform the operation on the last letter.

    --- Example 3 ---
    Input: s = "acbbc"
    Output: "abaab"
    Explanation:
    Perform the operation on the substring starting at index 1, and ending at
    index 4 inclusive.

    --- Example 4 ---
    Input: s = "leetcode"
    Output: "kddsbncd"
    Explanation:
    Perform the operation on the entire string.


    *** Constraints ***
    1 <= s.length <= 3 * 10^5
    s consists of lowercase English letters

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Classic Sliding-Window problem.

*/

/* Time  Beats: 29.54% */
/* Space Beats: 10.84% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    string smallestString(string s)
    {
        const int N = s.length();

        int left  = 0;
        int right = 0;

        bool started = false;
        while (right < N)
        {
            if (s[right] == 'a')
                left = right+1;
            else
            {
                started = true;
                s[right] = static_cast<char>('a' + mathematical_mod(s[right] - 'a' - 1));
            }

            if (started && left > right)
                return s;

            // Increment
            right++;
        }

        if (left < N)
            return s;

        s.pop_back();

        return s + 'z';
    }

private:
    int mathematical_mod(int num)
    {
        const int ALPHABET_LENGTH = 26;
        return (num % ALPHABET_LENGTH + ALPHABET_LENGTH) % ALPHABET_LENGTH;
    }
};
