/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    678) Valid Parenthesis String
    =============================

    ============
    Description:
    ============

    Given a string s containing only three types of characters: '(', ')' and
    '*', return true if s is valid.

    The following rules define a valid string:

        Any left parenthesis '(' must have a corresponding right parenthesis
        ')'.  Any right parenthesis ')' must have a corresponding left
        parenthesis '('.  Left parenthesis '(' must go before the corresponding
        right parenthesis ')'.  '*' could be treated as a single right
        parenthesis ')' or a single left parenthesis '(' or an empty string "".


    ==========================================
    FUNCTION: bool checkValidString(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "()"
    Output: true


    --- Example 2 ---
    Input: s = "(*)"
    Output: true


    --- Example 3 ---
    Input: s = "(*))"
    Output: true


    *** Constraints ***
    1 <= s.length <= 100
    s[i] is '(', ')' or '*'.

*/

#include <deque>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  20.74% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Two_Deques {
public:
    bool checkValidString(string s)
    {
        const int N = s.size();

        deque<int> open_indices;
        deque<int> star_indices;

        for (int i = 0; i < N; i++)
        {
            switch (s[i])
            {
                case '(':
                    open_indices.push_back(i);
                    break;

                case ')':
                    if ( ! open_indices.empty())
                    {
                        open_indices.pop_back();
                    }
                    else
                    {
                        if ( ! star_indices.empty())
                            star_indices.pop_back();
                        else
                            return false;
                    }

                    break;


                case '*':
                    star_indices.push_back(i);
                    break;
            }
        }

        for (const int& open_idx : open_indices)
        {
            while ( ! star_indices.empty() && star_indices.front() < open_idx)
                star_indices.pop_front();

            if (star_indices.empty())
                return false;

            star_indices.pop_front(); // Let '*' act as a CLOSING parenthesis
        }

        return true;
    }
};
