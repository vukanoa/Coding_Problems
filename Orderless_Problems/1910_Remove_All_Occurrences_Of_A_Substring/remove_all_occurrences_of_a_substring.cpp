/*
    ==============
    === MEDIUM ===
    ==============

    ===========================================
    1910) Remove All Occurrences of a Substring
    ===========================================

    ============
    Description:
    ============

    Given two strings s and part, perform the following operation on s until
    all occurrences of the substring part are removed:

        Find the leftmost occurrence of the substring part and remove it from s

    Return s after removing all occurrences of part.

    A substring is a contiguous sequence of characters in a string.

    ==========================================================
    FUNCTION: string removeOccurrences(string s, string part);
    ==========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "daabcbaabcbc", part = "abc"
    Output: "dab"
    Explanation: The following operations are done:
    - s = "daabcbaabcbc", remove "abc" starting at index 2, so s = "dabaabcbc".
    - s = "dabaabcbc", remove "abc" starting at index 4, so s = "dababc".
    - s = "dababc", remove "abc" starting at index 3, so s = "dab".
    Now s has no occurrences of "abc".

    --- Example 2 ---
    Input: s = "axxxxyyyyb", part = "xy"
    Output: "ab"
    Explanation: The following operations are done:
    - s = "axxxxyyyyb", remove "xy" starting at index 4 so s = "axxxyyyb".
    - s = "axxxyyyb", remove "xy" starting at index 3 so s = "axxyyb".
    - s = "axxyyb", remove "xy" starting at index 2 so s = "axyb".
    - s = "axyb", remove "xy" starting at index 1 so s = "ab".
    Now s has no occurrences of "xy".


    *** Constraints ***
    1 <= s.length <= 1000
    1 <= part.length <= 1000
    s and part consists of lowercase English letters.

*/

#include <stack>
#include <string>
#include <sstream>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Given the Constraints, we're allowed to perform this Brute-Force kind of
    approach.

    Always look at the Constraints.

*/

/* Time  Beats: 5.85% */
/* Space Beats: 5.32% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N)     */
class Solution {
public:
    string removeOccurrences(string s, string part)
    {
        if (s.length() < part.length())
            return s;

        if (s.length() == part.length())
            return s == part ? "" : s;

        while (s.length() >= part.length())
        {
            int idx = s.find(part);
            if (idx == string::npos)
                return s;

            ostringstream out;

            if (idx > 0)
                out << s.substr(0, idx);

            out << s.substr(idx + part.length());
            s = out.str();
        }

        return s;
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    This one has the same Time and Space Complexity, but it's a different kind
    of approach. It's good to be aware of both, even if they are not the most
    optimal ones.

*/

/* Time  Beats: 5.85% */
/* Space Beats: 5.32% */

/* Time  Complexity: O(N * M) */
/* Space Complexity: O(N)     */
class Solution_Stack {
public:
    string removeOccurrences(string s, string part)
    {
        int s_len = s.length();
        int part_len = part.length();

        stack<char> stack;
        for (int i = 0; i < s_len; i++)
        {
            stack.push(s[i]);

            if (stack.size() >= part_len && check(stack, part, part_len))
            {
                for (int j = 0; j < part_len; j++)
                    stack.pop();
            }
        }

        string result = "";
        while ( ! stack.empty())
        {
            result = stack.top() + result;
            stack.pop();
        }

        return result;
    }

private:
    bool check(stack<char>& stk, string& part, int part_len)
    {
        stack<char> tmp_stack = stk;

        for (int part_idx = part_len - 1; part_idx >= 0; part_idx--)
        {
            if (tmp_stack.top() != part[part_idx])
                return false;

            tmp_stack.pop();
        }

        return true;
    }
};
