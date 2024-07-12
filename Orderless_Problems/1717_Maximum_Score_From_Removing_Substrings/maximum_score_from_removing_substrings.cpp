#include <iostream>
#include <stack>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================================
    1717) Maximum Score From Removing Substrings
    ============================================

    ============
    Description:
    ============

       You are given a string s and two integers x and y. You can perform two
       types of operations any number of times.

        Remove substring "ab" and gain x points.
            For example, when removing "ab" from "cabxbae" it becomes "cxbae".

        Remove substring "ba" and gain y points.
            For example, when removing "ba" from "cabxbae" it becomes "cabxe".

    Return the maximum points you can gain after applying the above operations
    on s. 

    ==================================================
    FUNCTION: int maximumGain(string s, int x, int y);
    ==================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "cdbcbbaaabab", x = 4, y = 5
    Output: 19
    Explanation:
    - Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5
      points are added to the score.
    - Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4
      points are added to the score.
    - Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points
      are added to the score.
    - Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are
      added to the score.
    Total score = 5 + 4 + 5 + 5 = 19.

    --- Example 2 ---
    Input: s = "aabbaaxybbaabb", x = 5, y = 4
    Output: 20

    *** Constraints ***
    1 <= s.length <= 10^5
    1 <= x, y <= 10^4
    s consists of lowercase English letters.
*/

using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    Difficult Greedy Algorithm.

*/

/* Time  Beats: 56.10% */
/* Space Beats:  9.76% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int maximumGain(string s, int x, int y)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates
        
        int result = 0;
        string pair = x > y ? "ab" : "ba";

        result += remove_pairs(s, pair,                         max(x, y));
        result += remove_pairs(s, string(1, pair[1]) + pair[0], min(x, y));

        return result;
    }

private:
    int remove_pairs (string &s, string pair, int score)
    {
        int result = 0;
        stack<char> stack;

        for (char c : s)
        {
            if (c == pair[1] && !stack.empty() && stack.top() == pair[0])
            {
                stack.pop();
                result += score;
            }
            else
                stack.push(c);
        }

        string new_s;
        while (!stack.empty())
        {
            new_s += stack.top();
            stack.pop();
        }

        reverse(new_s.begin(), new_s.end());
        s = new_s;

        return result;
    };
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats:  100% */
/* Space Beats: 75.61% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Space_Efficient {
public:
    int maximumGain(string s, int x, int y)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        int result = 0;

        int a_count = 0;
        int b_count = 0;

        int lesser = std::min(x, y);

        for (char c : s)
        {
            if (c > 'b')
            {
                result += std::min(a_count, b_count) * lesser;
                a_count = 0;
                b_count = 0;
            }
            else if (c == 'a')
            {
                if (x < y && b_count > 0)
                {
                    b_count--;
                    result += y;
                }
                else
                    a_count++;
            }
            else
            {
                if (x > y && a_count > 0)
                {
                    a_count--;
                    result += x;
                }
                else
                    b_count++;
            }
        }

        result += std::min(a_count, b_count) * lesser;
        return result;
    }
};
