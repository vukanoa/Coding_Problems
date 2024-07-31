#include <iostream>
#include <vector>

/*
    ============
    === EASY ===
    ============

    =============================
    844) Backspace String Compare
    =============================

    ============
    Description:
    ============

    Given two strings s and t, return true if they are equal when both are
    typed into empty text editors. '#' means a backspace character.

    Note that after backspacing an empty text, the text will continue empty.

    ====================================================
    FUNCTION: bool backspaceCompare(string s, string t);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "ab#c", t = "ad#c"
    Output: true
    Explanation: Both s and t become "ac".

    --- Example 2 ---
    Input: s = "ab##", t = "c#d#"
    Output: true
    Explanation: Both s and t become "".

    --- Example 3 ---
    Input: s = "a#c", t = "b"
    Output: false
    Explanation: s becomes "c" while t becomes "b".


    *** Constraints ***
    1 <= s.length, t.length <= 200
    s and t only contain lowercase letters and '#' characters.

*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 43.51% */
/* Space Beats: 61.03% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    bool backspaceCompare(string s, string t)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        vector<int> vec_s;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '#')
            {
                if ( ! vec_s.empty())
                    vec_s.pop_back();
            }
            else
            {
                vec_s.push_back(s[i]);
            }
        }

        vector<int> vec_t;
        for (int i = 0; i < t.length(); i++)
        {
            if (t[i] == '#')
            {
                if ( ! vec_t.empty())
                    vec_t.pop_back();
            }
            else
            {
                vec_t.push_back(t[i]);
            }
        }

        return vec_s == vec_t;
    }
};
