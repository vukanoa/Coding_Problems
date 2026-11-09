/*
    ============
    === HARD ===
    ============

    ===========================================================================
    3816) Lexicographically Smallest String AFter Deleting Duplicate Characters
    ===========================================================================

    ============
    Description:
    ============

    You are given a string s that consists of lowercase English letters.

    You can perform the following operation any number of times (possibly zero times):

        Choose any letter that appears at least twice in the current string s
        and delete any one occurrence.

    Return the lexicographicaly smallest resulting string that can be formed
    this way.

    ====================================================
    FUNCTION: string lexSmallestAfterDeletion(string s);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "aaccb"
    Output: "aacb"
    Explanation:
    We can form the strings "acb", "aacb", "accb", and "aaccb". "aacb" is the
    lexicographically smallest one.
    For example, we can obtain "aacb" by choosing 'c' and deleting its first
    occurrence.

    --- Example 2 ---
    Input: s = "z"
    Output: "z"
    Explanation:
    We cannot perform any operations. The only string we can form is "z".


    *** Constraints ***
    1 <= s.length <= 10^5
    s contains lowercase English letters only.

*/

#include <algorithm>
#include <stack>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 36.02% */
/* Space Beats: 31.72% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    string lexSmallestAfterDeletion(string s)
    {
        const int N = s.size();

        int freq[26] = {};
        for (auto &chr : s)
            ++freq[chr - 'a'];
        
        stack<char> stack;
        for (int i = 0; i < N; i++)
        {
            if (stack.empty() || stack.top() <= s[i])
            {
                stack.push(s[i]);
            }
            else
            {
                while ( ! stack.empty() && stack.top() > s[i] && freq[stack.top() - 'a'] >= 2)
                {
                    --freq[stack.top() - 'a'];
                    stack.pop();
                }

                stack.push(s[i]);
            }
        }

        string result = "";
        result.reserve(N); // To prevent repeated reallocations
        while ( ! stack.empty())
        {
            result += stack.top();  
            stack.pop();
        }

        /* Reverse */
        reverse(result.begin(), result.end());

        while (result.size() >= 2 && freq[result.back() - 'a'] >= 2)
        {
            --freq[result.back() - 'a'];
            result.pop_back();
        }

        return result;
    }
};
