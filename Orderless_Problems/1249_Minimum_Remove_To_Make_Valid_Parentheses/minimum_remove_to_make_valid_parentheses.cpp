#include <iostream>
#include <sstream>
#include <string>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================================
    1249) Minimum Remove To Make Valid Parentheses
    ==============================================

    ============
    Description:
    ============

    Given a string s of '(' , ')' and lowercase English characters.

    Your task is to remove the minimum number of parentheses ( '(' or ')', in
    any positions ) so that the resulting parentheses string is valid and
    return any valid string.

    Formally, a parentheses string is valid if and only if:

    - It is the empty string, contains only lowercase characters, or
    - It can be written as AB (A concatenated with B), where A and B are valid
      strings, or
    - It can be written as (A), where A is a valid string.


    ================================================
    FUNCTION: string minRemoveToMakeValid(string s);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "lee(t(c)o)de)"
    Output: "lee(t(c)o)de"
    Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.

    --- Example 2 ---
    Input: s = "a)b(c)d"
    Output: "ab(c)d"

    --- Example 3 ---
    Input: s = "))(("
    Output: ""
    Explanation: An empty string is also valid.


    *** Constraints ***
    1 <= s.length <= 105
    s[i] is either'(' , ')', or lowercase English letter.

*/

/*
    There are 3 Solutions in here. The 3rd one(down most one) is the best.
*/




/* Time  Beats: 35.03% */
/* Space Beats: 23.66% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    string minRemoveToMakeValid(string s)
    {
        int opened = 0;
        std::ostringstream out;

        for (auto& character : s)
        {
            if (character == ')')
            {
                if (opened == 0)
                    continue;
                else
                {
                    opened--;
                    out << character;
                }
            }
            else if (character == '(')
            {
                opened++;
                out << character;
            }
            else
                out << character;
        }

        std::string str = out.str();
        std::ostringstream result;

        opened = 0;

        for (int i = str.length() - 1; i >= 0; i--)
        {
            if (str[i] == '(')
            {
                if (opened == 0)
                    continue;
                else
                {
                    opened--;
                    result << str[i];
                }
            }
            else if (str[i] == ')')
            {
                opened++;
                result << str[i];
            }
            else
                result << str[i];
        }

        std::string final_str = result.str();
        std::reverse(final_str.begin(), final_str.end());

        return final_str;
    }
};




/* Time  Beats: 92.39% */
/* Space Beats: 75.75% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string minRemoveToMakeValid(std::string s)
    {
        int open = 0;
        int position = 0;

        std::string str(s.size(), '#');

        for (char character : s)
        {
            if (character == '(')
                open++;
            else if (character == ')')
            {
                if (open > 0)
                    open--;
                else
                    continue;
            }

            str[position++] = character;
        }

        // Properly sizing res
        std::string final_str(position - open, '*');

        for (int i = position - 1, j = position - open - 1; i >= 0; i--)
        {
            if (str[i] != '(' || open-- <= 0)
                final_str[j--] = str[i];
        }

        return final_str;
    }
};




/* Time  Beats: 97.20% */
/* Space Beats: 95.32% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    std::string minRemoveToMakeValid(std::string s)
    {
        int open = 0;
        int position = 0;

        std::string str(s.size(), '#');

        for (char character : s)
        {
            if (character == '(')
                open++;
            else if (character == ')')
            {
                if (open > 0)
                    open--;
                else
                    continue;
            }

            str[position++] = character;
        }

        // Properly sizing res
        s.resize(position - open);

        for (int i = position - 1, j = position - open - 1; i >= 0; i--)
        {
            if (str[i] != '(' || open-- <= 0)
                s[j--] = str[i];
        }

        return s;
    }
};
