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
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 33.33% */
/* Space Beats: 77.01% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numberOfSpecialChars(string word)
    {
        const int N = word.size();
        int result = 0;

        bool exist[128] = {false};

        for (const char& chr : word)
            exist[chr] = true;

        for (int i = 65; i <= 91; i++)
        {
            if (exist[i] && exist[i + 32])
                result++;
        }

        return result;
    }
};
