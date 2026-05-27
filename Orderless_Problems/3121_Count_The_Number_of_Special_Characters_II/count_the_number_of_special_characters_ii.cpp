/*
    ==============
    === MEDIUM ===
    ==============

    ===============================================
    3121) Count the Number of Special Characters II
    ===============================================

    ============
    Description:
    ============

    You are given a string word. A letter c is called special if it appears
    both in lowercase and uppercase in word, and every lowercase occurrence of
    c appears before the first uppercase occurrence of c.

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
    The special characters are 'a', 'b', and 'c'.

    --- Example 2 ---
    Input: word = "abc"
    Output: 0
    Explanation:
    There are no special characters in word.

    --- Example 3 ---
    Input: word = "AbBCab"
    Output: 0
    Explanation:
    There are no special characters in word.


    *** Constraints ***
    1 <= word.length <= 2 * 10^5
    word consists of only lowercase and uppercase English letters.
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

/* Time  Beats: 36.24% */
/* Space Beats: 53.09% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numberOfSpecialChars(string word)
    {
        const int N = word.size();
        int result = 0;

        int leftmost_uppercase[26];
        int rightmost_lowercase[26];

        /* Fill */
        fill(begin(leftmost_uppercase), end(leftmost_uppercase), -1);
        fill(begin(rightmost_lowercase), end(rightmost_lowercase), -1);

        for (int i = 0; i < N; i++)
        {
            char chr = word[i];

            if (isupper(chr) && leftmost_uppercase[chr - 'A'] == -1)
               leftmost_uppercase[chr - 'A'] = i; 

            if (islower(chr))
                rightmost_lowercase[chr - 'a'] = i;
        }

        for (int i = 0; i < 26; i++)
        {
            if (leftmost_uppercase[i] != -1 && rightmost_lowercase[i] != -1)
            {
                if (rightmost_lowercase[i] < leftmost_uppercase[i])
                    result++;
            }
        }

        return result;
    }
};
