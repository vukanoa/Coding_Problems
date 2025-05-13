/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    3335) Total Characters in String After Transformations I
    ========================================================

    ============
    Description:
    ============

    You are given a string s and an integer t, representing the number of
    transformations to perform. In one transformation, every character in s is
    replaced according to the following rules:

        + If the character is 'z', replace it with the string "ab".
        + Otherwise, replace it with the next character in the alphabet. For
          example, 'a' is replaced with 'b', 'b' is replaced with 'c', and so
          on.

    Return the length of the resulting string after exactly t transformations.

    Since the answer may be very large, return it modulo 10^9 + 7.

    ==========================================================
    FUNCTION: int lengthAfterTransformations(string s, int t);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "abcyy", t = 2
    Output: 7
    Explanation:
        First Transformation (t = 1):
            'a' becomes 'b'
            'b' becomes 'c'
            'c' becomes 'd'
            'y' becomes 'z'
            'y' becomes 'z'
            String after the first transformation: "bcdzz"
        Second Transformation (t = 2):
            'b' becomes 'c'
            'c' becomes 'd'
            'd' becomes 'e'
            'z' becomes "ab"
            'z' becomes "ab"
            String after the second transformation: "cdeabab"
        Final Length of the string: The string is "cdeabab", which has 7
        characters.


    --- Example 2 ---
    Input: s = "azbk", t = 1
    Output: 5
    Explanation:
        First Transformation (t = 1):
            'a' becomes 'b'
            'z' becomes "ab"
            'b' becomes 'c'
            'k' becomes 'l'
            String after the first transformation: "babcl"
        Final Length of the string: The string is "babcl", which has 5
        characters.


    *** Constraints ***
    1 <= s.length <= 10^5
    s consists only of lowercase English letters.
    1 <= t <= 10^5

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

/* Time  Beats: 52.22% */
/* Space Beats: 18.72% */

/* Time  Complexity: O(t * 26) ---> O(t) */
/* Space Complexity: O(26)  ------> O(1) */
class Solution {
private:
    const int MOD = 1e9 + 7;

public:
    int lengthAfterTransformations(string s, int t)
    {
        vector<int> count(26);
        for (const char& chr : s)
            count[chr - 'a']++;

        for (int round = 0; round < t; round++)
        {
            vector<int> next(26);

            next[0] = count[25];
            next[1] = (count[25] + count[0]) % MOD;

            for (int i = 2; i < 26; i++)
                next[i] = count[i - 1];

            count = std::move(next);
        }

        int result = 0;
        for (int i = 0; i < 26; i++)
            result = (result + count[i]) % MOD;

        return result;
    }
};
