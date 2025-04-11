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

    Intuitive.

*/

/* Time  Beats: 92.41% */
/* Space Beats: 69.05% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int numberOfSpecialChars(string word)
    {
        const int N = word.size();
        int result = 0;

        vector<int> lower(26, -1);
        vector<int> upper(26, -1);

        for (int i = 0; i < N; i++)
        {
            if (word[i] > 95) // Lower
            {
                lower[word[i] - 'a'] = i;
            }
            else
            {
                if (upper[word[i] - 'A'] == -1)
                    upper[word[i] - 'A'] = i;
            }
        }

        for (int i = 0; i < 26; i++)
        {
            if (lower[i] != -1 && upper[i] != -1 && lower[i] < upper[i])
                result++;
        }


        return result;
    }
};
