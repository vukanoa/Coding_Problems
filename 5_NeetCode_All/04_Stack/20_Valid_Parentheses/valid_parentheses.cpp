/*
    ============
    === EASY ===
    ============

    ===========================
    20) Valid Parentheses
    ===========================

    ============
    Description:
    ============

    Given a string s containing just the characters '(', ')', '{', '}', '[' and
    ']', determine if the input string is valid.

    An input string is valid if:
        Open brackets must be closed by the same type of brackets.
        Open brackets must be closed in the correct order.
        Every close bracket has a corresponding open bracket of the same type.

    ======================================
    FUNCTION: bool isValid(std::string s);
    ======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input:  s = "()"
    Output: true

    --- Example 2 ---
    Input:  s = "()[]{}"
    Output: true

    --- Example 3 ---
    Input: s = "(]"
    Output: false

    *** Constraints ***
    1 <= s.legnth <= 10^4
    s consists of parentheses only '()[]{}'.

*/


#include <string>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Self-explanatory.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  99.33% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    bool isValid(string s)
    {
        const int N = s.size();

        string s_stack;
        s_stack.reserve(N); // So that we do NOT construct on every append

        for (const char& chr : s)
        {
            if (chr == '(' || chr == '[' || chr == '{')
            {
                s_stack += chr;
            }
            else
            {
                if (s_stack.empty())
                    return false;

                if (chr == ')' && s_stack.back() != '(')
                    return false;

                if (chr == ']' && s_stack.back() != '[')
                    return false;

                if (chr == '}' && s_stack.back() != '{')
                    return false;

                s_stack.pop_back(); // Pop from the stack
            }
        }

        return s_stack.empty();
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    Same as above but written in another way. This is more concice and more
    verbose.

*/

/* Time  Beats: 100.00% */
/* Space Beats:  20.28% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution_2 {
public:
    bool isValid(string s)
    {
        const int N = s.size();
        string s_stack;
        s_stack.reserve(N); // So that we do NOT construct on every append

        unordered_set<char> open_brackets = {'(', '[', '{'};
        unordered_map<char, char> pair_of = {{')', '('}, {']', '['}, {'}', '{'}};

        for (char& chr : s)
        {
            if (open_brackets.count(chr))
            {
                s_stack += chr;
            }
            else
            {
                if (s_stack.empty() || pair_of[chr] != s_stack.back())
                    return false;

                s_stack.pop_back();
            }
        }

        return s_stack.empty();
    }
};
