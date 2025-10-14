/*
    ============
    === EASY ===
    ============

    ==========================================
    1704) Determine if String Halves are Alike
    ==========================================

    ============
    Description:
    ============

    You are given a string s of even length. Split this string into two halves
    of equal lengths, and let a be the first half and b be the second half.

    Two strings are alike if they have the same number of vowels
    ('a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'). Notice that s contains
    uppercase and lowercase letters.

    Return true if a and b are alike. Otherwise, return false.

    ========================================
    FUNCTION: bool halvesAreAlike(string s);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "book"
    Output: true
    Explanation: a = "bo" and b = "ok". a has 1 vowel and b has 1 vowel.
                 Therefore, they are alike.

    --- Example 2 ---
    Input: s = "textbook"
    Output: false
    Explanation: a = "text" and b = "book". a has 1 vowel whereas b has 2.
                 Therefore, they are not alike. Notice that the vowel o is
                 counted twice.

    *** Constraints ***
    2 <= s.length <= 1000
    s.length is even.
    s consists of uppercase and lowercase letters.

*/

#include <string>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  33.57% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution {
public:
    bool halvesAreAlike(string s)
    {
        const int N = s.length();

        int left  = 0;
        int right = 0;

        unordered_set<char> vowels = {'a', 'e', 'i', 'o', 'u'};

        for (int i = 0; i < N; i++)
        {
            char chr = tolower(s[i]);

            if (i < N / 2)
            {
                left += vowels.count(chr);
            }
            else
            {
                right += vowels.count(chr);
            }
        }

        return left == right;
    }
};
