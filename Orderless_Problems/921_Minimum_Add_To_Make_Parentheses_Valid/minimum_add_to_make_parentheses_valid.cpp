#include <iostream>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ==========================================
    921) Minimum Add to Make Parentheses Valid
    ==========================================

    ============
    Description:
    ============

    A parentheses string is valid if and only if:

        + It is the empty string,
        + It can be written as AB (A concatenated with B), where A and B are
          valid strings, or
        + It can be written as (A), where A is a valid string.

    You are given a parentheses string s. In one move, you can insert a
    parenthesis at any position of the string.

        + For example, if s = "()))", you can insert an opening parenthesis to
          be "(()))" or a closing parenthesis to be "())))".

    Return the minimum number of moves required to make s valid.

    ==========================================
    FUNCTION: int minAddToMakeValid(string s);
    ==========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "())"
    Output: 1

    --- Example 2 ---
    Input: s = "((("
    Output: 3


    *** Constraints ***
    1 <= s.length <= 1000
    s[i] is either '(' or ')'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 42.94% */
/* Space Beats: 15.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_1 {
public:
    int minAddToMakeValid(string s)
    {
        stack<char> stack;
        int c = 0;

        for (const char& chr : s)
        {
            if (chr == '(')
                stack.push(chr);
            else
            {
                if (stack.empty())
                    c++;
                else
                    stack.pop();
            }
        }

        return c + stack.size();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 44.73% */
/* Space Beats: 55.34% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_2 {
public:
    int minAddToMakeValid(string s)
    {
        string stack;

        for (auto c : s)
        {
            if (stack.empty())
                stack.push_back(c);

            else if (stack.back() == '(' && c == ')')
                stack.pop_back();
            else
                stack.push_back(c);
        }

        return stack.size();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 42.94% */
/* Space Beats: 94.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int minAddToMakeValid(string s)
    {
        int open  = 0;
        int close = 0;

        for (const auto& chr: s)
        {
            if (chr == '(')
                open++;
            else
            {
                if (open > 0)
                    open--;
                else
                    close++;
            }
        }

        return open + close;
    }
};
