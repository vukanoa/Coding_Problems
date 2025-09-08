/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    2645) Minimum Additions to Make Valid String
    ============================================

    ============
    Description:
    ============

    Given a string word to which you can insert letters "a", "b" or "c"
    anywhere and any number of times, return the minimum number of letters that
    must be inserted so that word becomes valid.

    A string is called valid if it can be formed by concatenating the string
    "abc" several times.

    ======================================
    FUNCTION: int addMinimum(string word);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: word = "b"
    Output: 2
    Explanation: Insert the letter "a" right before "b", and the letter "c"
                 right next to "b" to obtain the valid string "abc".

    --- Example 2 ---
    Input: word = "aaa"
    Output: 6
    Explanation: Insert letters "b" and "c" next to each "a" to obtain the
                 valid string "abcabcabc".

    --- Example 3 ---
    Input: word = "abc"
    Output: 0
    Explanation: word is already valid. No modifications are needed. 


    *** Constraints ***
    1 <= word.length <= 50
    word consists of letters "a", "b" and "c" only. 

*/

#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  37.91% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    int addMinimum(string word)
    {
        const int N = word.length();
        if (N == 1)
            return 2;

        int result = 0;

        int L = 0;
        for (int R = 1; R < N; R++)
        {
            if (word[R-1] < word[R])
                continue;

            result += 3 - (R - L);
            L = R;
        }

        result += 3 - (N - L);

        return result;
    }
};
