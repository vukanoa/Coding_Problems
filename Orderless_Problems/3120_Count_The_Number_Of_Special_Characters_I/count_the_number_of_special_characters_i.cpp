/*
    ============
    === EASY ===
    ============

    ==============================================
    3120) Count the Number of Special Characters I
    ==============================================

    ============
    Description:
    ============

    You are given a string word. A letter is called special if it appears both
    in lowercase and uppercase in word.

    Return the number of special letters in word.

    ================================================
    FUNCTION: int numberOfSpecialChars(string word);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "aaAbcBC"
    Output: 3
    Explanation:
    The special characters in word are 'a', 'b', and 'c'.

    --- Example 2 ---
    Input: word = "abc"
    Output: 0
    Explanation:
    No character in word appears in uppercase.

    --- Example 3 ---
    Input: word = "abBCab"
    Output: 1
    Explanation:
    The only special character in word is 'b'.


    *** Constraints ***
    1 <= word.length <= 50
    word consists of only lowercase and uppercase English letters.

*/

#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Intuitive.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  14.97% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numberOfSpecialChars(string word)
    {
        const int N = word.length();
        int result = 0;
        unordered_set<char> used;

        unordered_set<char> uset;
        for (const char& chr : word)
            uset.insert(chr);

        for (const char& chr : uset)
        {
            if (used.find(chr) != used.end())
                continue;

            if (chr < 95)
            {
                if (uset.count(chr + 32))
                {
                    used.insert(chr);
                    used.insert(chr + 32);
                    result++;
                }
            }
            else
            {
                if (uset.count(chr + 32))
                {
                    used.insert(chr);
                    used.insert(chr - 32);
                    result++;
                }
            }
        }

        return result;
    }
};
