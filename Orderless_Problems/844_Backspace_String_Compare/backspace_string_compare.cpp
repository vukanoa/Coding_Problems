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


    ---------------
    -- Follow Up --
    ---------------

        Can you solve it in O(n) time and O(1) space?


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

/* Time  Complexity: O(n + m) */
/* Time  Complexity: O(n + m) */
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




/*
    ------------
    --- IDEA ---
    ------------

    TODO (Follow-up)

*/

/* Time  Beats: 100.00% */
/* Space Beats:   9.32% */

/* Time  Complexity: O(n + m) */
/* Space Complexity: O(1)     */
class Solution_Efficient {
public:
    bool backspaceCompare(string s, string t)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int index_s = s.length()-1;
        int index_t = t.length()-1;

        while (index_s >= 0 || index_t >= 0)
        {
            index_s = next_valid_char(s, index_s);
            index_t = next_valid_char(t, index_t);

            char chr_s = index_s >= 0 ? s[index_s] : '\0';
            char chr_t = index_t >= 0 ? t[index_t] : '\0';

            if (chr_s != chr_t)
                return false;

            index_s--;
            index_t--;
        }

        return true;
    }

private:
    int next_valid_char(string str, int index)
    {
        int backspaces = 0;

        while (index >= 0)
        {
            if (backspaces == 0 && str[index] != '#')
                break;
            else if (str[index] == '#')
                backspaces++;
            else
                backspaces--;

            index--;
        }

        return index;
    }
};
