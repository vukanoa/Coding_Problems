/*
    ==============
    === MEDIUM ===
    ==============

    =========================================================
    1190) Reverse Substrings Between Each Pair of Parentheses
    =========================================================

    ============
    Description:
    ============

    You are given a string s that consists of lower case English letters and
    brackets.

    Reverse the strings in each pair of matching parentheses, starting from the
    innermost one.

    Your result should not contain any brackets.

    ==============================================
    FUNCTION: string reverseParentheses(string s); 
    ==============================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "(abcd)"
    Output: "dcba"

    --- Example 2 ---
    Input: s = "(u(love)i)"
    Output: "iloveu"
    Explanation: The substring "love" is reversed first, then the whole string
                 is reversed.

    --- Example 3 ---
    Input: s = "(ed(et(oc))el)"
    Output: "leetcode"
    Explanation: First, we reverse the substring "oc", then "etco", and
                 finally, the whole string.


    *** Constraints ***
    1 <= s.length <= 2000
    s only contains lower case English characters and parentheses.
    It is guaranteed that all parentheses are balanced.

*/

#include <algorithm>
#include <stack>
#include <vector>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 56.78% */
/* Space Beats: 90.48% */

/* Time  Complexity: O(N^2) */
/* Space Complexity: O(N)   */
class Solution {
public:
    string reverseParentheses(string s)
    {
        string result;

        vector<int> opened;
        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == '(')
            {
                opened.push_back(result.length());
            }
            else if (s[i] == ')')
            {
                int j = opened.back();
                opened.pop_back();

                reverse(result.begin() + j, result.end());
            }
            else
            {
                result += s[i];
            }
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (This one requires extensive explanation)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  70.66% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Wormhole {
public:
    string reverseParentheses(string s)
    {
        const int N = s.length();
        string result;

        vector<int> opened;
        vector<int> pair(N);

        for (int i = 0; i < N; i++)
        {
            if (s[i] == '(')
            {
                opened.push_back(i);
            }
            if (s[i] == ')')
            {
                int j = opened.back();
                opened.pop_back();

                pair[i] = j;
                pair[j] = i;
            }
        }

        int direction = 1;
        for (int i = 0; i < N; i += direction)
        {
            if (s[i] == '(' || s[i] == ')')
            {
                i = pair[i];
                direction = -direction;
            }
            else
                result += s[i];
        }

        return result;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Imagine the string as a path where every matching pair of parentheses--i.e.
    '(' and ')'--form a TWO–WAY portal.


    Algorithm:
        1. We start at the beginning and walk to the right.

        2. When we encounter a letter (i.e. [a-z]), we collect it.

        3. When we encounter a portal (i.e. '(' and ')'), we instantly TELEPORT
           TO THE OTHER END of the portal and then REVERSE(toggle) DIRECTION.


    Toggle-ing direction makes us encounter the letters inside the portal from
    the opposite direction which is exactly what reversing the corresponding
    substirng does in the original string.




    In the first for-loop we're forming portals.
        + Each time we encounter a '(' we push its index onto the stack.

        + Each time we encounter a ')' pop the index from the stack which
          represents the index of the MATCHING OPENING parenthesis. Then we
          put OTHER parenthesis' index inside the "portal" vector for each of
          the parenthessis.

          Example:

                   s =  ( u ( l o v e ) i ) 
                        0 1 2 3 4 5 6 7 8 9
                        |   |       __| __|
                        |   |       |   |  
                        ----C-------C---C--
                            |       |   | |
                            |       |   | |
                        ----C-------C---- |
                        |   |       |     |
                        |   |     ---     |
                        |   |     |       |
                        |   ------C----   |
                        |         |   |   |
                        |         |   |   |
                        |   ------|   |   |
                        |   |         |   |
                        v   v         v   v
              portal = [9   7         2   0]
                        0 1 2 3 4 5 6 7 8 9



    In the second for-loop, since every parenthesis has already been paired
    with exactly one MATCHING parenthesis, there is no need to distinguish
    between '(' and ')'.

    Thus, we simply treat both as a PORTAL.

    We begin with a POSITIVE STEP (i.e. moving to to the RIGHT). Whenever we
    encounter a portal:

        + JUMP to its corresponding matching index using the "portal" vector.
        + TOGGLE the direction by changing this to a negative.

    The letters are then collected into the result string as they are
    encountered.

    The portals only change the location and direction of movement, so no
    actual substring reversal is needed.


    At the end, we simply return result.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  65.80% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_Portal_Jumping {
public:
    string reverseParentheses(string s)
    {
        const int N = s.size();
        string result;
        result.reserve(N);

        vector<int> portal(N);
        stack<int>  stack;

        for (int i = 0; i < N; i++)
        {
            if (s[i] == '(')
            {
                stack.push(i);
            }
            else if (s[i] == ')')
            {
                portal[i]         = stack.top();
                portal[portal[i]] = i;

                stack.pop();
            }
        }

        int direction = 1;
        for (int i = 0; i < N; i += direction)
        {
            if (s[i] >= 'a') // isdigit(s[i]), since ASCII '(' & ')' == 40 & 41
            {
                result += s[i];
            }
            else
            {
                i = portal[i]; // Jump to the MATCHING parenthesis

                // TOGGLE direction
                direction = -direction;
            }
        }

        return result;
    }
};
