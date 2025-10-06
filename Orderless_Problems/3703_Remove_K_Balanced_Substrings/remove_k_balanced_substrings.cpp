/*
    ==============
    === MEDIUM ===
    ==============

    ==================================
    3703) Remove K-Balanced Substrings
    ==================================

    ============
    Description:
    ============

    You are given a string s consisting of '(' and ')', and an integer k.

    A string is k-balanced if it is exactly k consecutive '(' followed by k
    consecutive ')', i.e., '(' * k + ')' * k.

    For example, if k = 3, k-balanced is "((()))".

    You must repeatedly remove all non-overlapping k-balanced

    from s, and then join the remaining parts. Continue this process until no
    k-balanced substring exists.

    Return the final string after all possible removals.

    ==================================================
    FUNCTION: string removeSubstring(string s, int k);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "(())", k = 1
    Output: ""

    --- Example 2 ---
    Input: s = "(()(", k = 1
    Output: "(("

    --- Example 3 ---
    Input: s = "((()))()()()", k = 3
    Output: "()()()"

    *** Constraints ***
    2 <= s.length <= 10^5
    s consists only of '(' and ')'.
    1 <= k <= s.length / 2

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

/* Time  Beats: 59.04% */
/* Space Beats: 46.02% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string removeSubstring(string s, int k)
    {
        const int N = s.length();

        deque<int> opened = {0};
        deque<int> closed = {0};

        for (int i = 0; i < N; i++)
        {
            if (s[i] == '(')
            {
                if (opened.size() > closed.size())
                {
                    opened.back()++;
                }
                else
                {
                    opened.push_back(1);
                }
            }
            else
            {
                if (opened.size() > closed.size())
                    closed.push_back(1);
                else
                    closed.back()++;
            }

            if (opened.size() == closed.size() && opened.back() >= k && closed.back() == k)
            {
                opened.back() -= k;
                if (opened.back() == 0 && opened.size() > 1)
                    opened.pop_back();

                closed.pop_back();
            }
        }

        // Fill from left to right
        string result = "";
        while ( ! opened.empty() || ! closed.empty())
        {
            // Opening parentheses
            if ( ! opened.empty())
            {
                if (opened.front() > 0)
                    result += string(opened.front(), '(');

                opened.pop_front();
            }

            // Closing parentheses
            if ( ! closed.empty())
            {
                if (closed.front() > 0)
                    result += string(closed.front(), ')');

                closed.pop_front();
            }
        }

        return result;
    }
};
