#include <iostream>

/*
    ============
    === HARD ===
    ============

    =============================
    282) Expression Add Operators
    =============================

    ============
    Description:
    ============

    Given a string num that contains only digits and an integer target, return
    all possibilities to insert the binary operators '+', '-', and/or '*'
    between the digits of num so that the resultant expression evaluates to the
    target value.

    Note that operands in the returned expressions should not contain leading
    zeros.

    ==============================================================
    FUNCTION: vector<string> addOperators(string num, int target); 
    ==============================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: num = "123", target = 6
    Output: ["1*2*3","1+2+3"]
    Explanation: Both "1*2*3" and "1+2+3" evaluate to 6.

    --- Example 2 ---
    Input: num = "232", target = 8
    Output: ["2*3+2","2+3*2"]
    Explanation: Both "2*3+2" and "2+3*2" evaluate to 8.

    --- Example 3 ---
    Input: num = "3456237490", target = 9191
    Output: []
    Explanation: There are no expressions that can be created from "3456237490"
                 to evaluate to 9191.


    *** Constraints ***
    1 <= num.length <= 10
    num consists of only digits.
    -2^31 <= target <= 2^31 - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 32.42% */
/* Space Beats: 82.82% */

/* Time  Complexity: O(n * 4^n) */
/* Space Complexity: O(n)       */
class Solution {
public:
    std::vector<std::string> addOperators(std::string num, int target)
    {
        std::vector<std::string> res;

        if (num.empty())
            return res;

        for (int i = 1; i <= num.size(); i++)
        {
            std::string s = num.substr(0, i);
            long cur = std::stol(s);

            if (std::to_string(cur).size() != s.size())
                continue;

            dfs(res, num, target, s, i, cur, cur, '#'); // no operator defined
        }

        return res;
    }

private:
    void dfs (std::vector<string>& res,
              std::string& num,
              int target,
              std::string curr_expr,
              int idx,
              long curr_sum,
              long prev_sum,
              char prev_operator)
    {
        if (idx == num.size() && curr_sum == target)
            res.push_back(curr_expr);
        else
        {
            for (int i = idx+1; i <= num.size(); i++)
            {
                string t = num.substr(idx, i-idx);
                long now = stol(t);

                if (to_string(now).size() != t.size())
                    continue;

                dfs(res, num, target, curr_expr+'+'+t, i, curr_sum+now, now, '+');
                dfs(res, num, target, curr_expr+'-'+t, i, curr_sum-now, now, '-');

                if (prev_operator == '-')
                    dfs(res, num, target, curr_expr+'*'+t, i, curr_sum+prev_sum - prev_sum*now, prev_sum*now, prev_operator);
                else if (prev_operator == '+')
                    dfs(res, num, target, curr_expr+'*'+t, i, curr_sum-prev_sum + prev_sum*now, prev_sum*now, prev_operator);
                else
                    dfs(res, num, target, curr_expr+'*'+t, i,       prev_sum * now            , prev_sum*now, prev_operator);
            }
        }
    }
};
