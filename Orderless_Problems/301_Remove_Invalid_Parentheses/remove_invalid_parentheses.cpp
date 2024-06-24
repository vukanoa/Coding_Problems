#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

/*
    ============
    === HARD ===
    ============

    ===============================
    301) Remove Invalid Parentheses
    ===============================

    ============
    Description:
    ============

    Given a string s that contains parentheses and letters, remove the minimum
    number of invalid parentheses to make the input string valid.

    Return a list of unique strings that are valid with the minimum number of
    removals. You may return the answer in any order.

    ============================================================
    FUNCTION: vector<string> removeInvalidParentheses(string s); 
    ============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "()())()"
    Output: ["(())()","()()()"]

    --- Example 2 ---
    Input: s = "(a)())()"
    Output: ["(a())()","(a)()()"]

    --- Example 3 ---
    Input: s = ")("
    Output: [""]


    *** Constraints ***
    1 <= s.length <= 25
    s consists of lowercase English letters and parentheses '(' and ')'.
    There will be at most 20 parentheses in s.

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 78.12% */
/* Space Beats: 63.02% */

/* Time  Complexity: O(2^n)     */
/* Space Complexity: O(n * 2^n) */
class Solution {
public:
    std::vector<std::string> removeInvalidParentheses(std::string s) 
    {
        std::vector<std::string> result;
        std::unordered_set<std::string> visited;
        std::queue<std::string> queue;

        queue.push(s);
        visited.insert(s);

        while ( ! queue.empty())
        {
            int size = queue.size();

            for(int i = 0; i < size; ++i)
            {
                string str = queue.front();
                queue.pop();

                char chr_remove = valid(str);

                if (chr_remove == 1)
                    result.push_back(str);

                if (result.size())
                    continue; // All our resultults are on this level - no need to populate queue

                for (int j = 0; j < str.length(); j++)
                {
                    if(str[j] == chr_remove)
                    {
                        string new_str = str.substr(0, j) + str.substr(j+1);
                        if( ! visited.count(new_str)) 
                        {
                            queue.push(new_str);
                            visited.insert(new_str);
                        }
                    }
                }
            }

            if (result.size())
                break;
        }

        return result;
    }

private:
    // Returns 1 if valid; char to be removed otherwise
    char valid(std::string& s)
    {
        int count = 0;
        for (char c : s)
        {
            if (c == '(')
                count++;
            else if (c == ')') 
            {
                if (count > 0)
                    count--;
                else
                    return ')';
            }
        }

        return count == 0 ? 1 : '(';
    }
};
