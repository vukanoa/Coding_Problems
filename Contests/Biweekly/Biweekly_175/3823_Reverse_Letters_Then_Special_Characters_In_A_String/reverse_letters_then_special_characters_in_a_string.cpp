/*
    ============
    === EASY ===
    ============

    ========================================================
    3823) Reverse Letter then Special Characters in a Stirng
    ========================================================

    ============
    Description:
    ============

    You are given a string s consisting of lowercase English letters and
    special characters.

    Your task is to perform these in order:

        + Reverse the lowercase letters and place them back into the positions
          originally occupied by letters.

        + Reverse the special characters and place them back into the positions
          originally occupied by special characters.

    Return the resulting string after performing the reversals.

    =========================================
    FUNCTION: string reverseByType(string s);
    =========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = ")ebc#da@f("
    Output: "(fad@cb#e)"
    Explanation:
        The letters in the string are ['e', 'b', 'c', 'd', 'a', 'f']:
            Reversing them gives ['f', 'a', 'd', 'c', 'b', 'e']
            s becomes ")fad#cb@e("
        The special characters in the string are [')', '#', '@', '(']:
            Reversing them gives ['(', '@', '#', ')']
            s becomes "(fad@cb#e)"

    --- Example 2 ---
    Input: s = "z"
    Output: "z"
    Explanation:
    The string contains only one letter, and reversing it does not change the
    string. There are no special characters.


    --- Example 3 ---
    Input: s = "!@#$%^&*()"
    Output: ")(*&^%$#@!"
    Explanation:
    The string contains no letters. The string contains all special characters,
    so reversing the special characters reverses the whole string.


    *** Constraints ***
    1 <= s.length <= 100
    s consists only of lowercase English letters and the special characters in
    "!@#$%^&*()".

*/

#include <string>
using namespace std;

/* Time  Beats: 100.00% */
/* Space Beats:  25.06% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string reverseByType(string s)
    {
        const int N = s.size();

        string letters;
        string special;

        letters.reserve(N); // To prevent repeated reallocations
        special.reserve(N); // To prevent repeated reallocations

        for (const char& chr : s)
        {
            if (islower(chr))
                letters += chr;
            else
                special += chr;
        }

        for (int i = 0; i < N; i++)
        {
            if (islower(s[i]))
            {
                s[i] = letters.back();
                letters.pop_back();
            }
            else
            {
                s[i] = special.back();
                special.pop_back();
            }
        }

        return s;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one does NOT use any extra Space.

*/

/* Time  Beats: 22.77% */
/* Space Beats: 87.28% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(1) */
class Solution_2 {
public:
    string reverseByType(string s)
    {
        const int N = s.size();

        // Reverse lowercase characters
        int left  = 0;
        int right = N - 1;

        while (left <= right)
        {
            if (isalpha(s[left]) && isalpha(s[right]))
            {
                swap(s[left], s[right]);

                ++left;
                --right;
            }
            else if(isalpha(s[left]))
            {
                --right;
            }
            else if(isalpha(s[right]))
            {
                ++left;
            }
            else
            {
                ++left;
                --right;
            }
        }

        // Reverse special characters
        left  = 0;
        right = N - 1;
        while (left <= right)
        {
            if ( ! isalpha(s[left]) &&  ! isalpha(s[right]))
            {
                swap(s[left], s[right]);

                ++left;
                --right;
            }
            else if(!isalpha(s[left]))
            {
                --right;
            }
            else if(!isalpha(s[right]))
            {
                ++left;
            }
            else
            {
                ++left;
                --right;
            }
        }

        return s;
    }
};
