/*
    ============
    === HARD ===
    ============

    ===========================
    679) 24 Game
    ===========================

    ============
    Description:
    ============

    You are given an integer array cards of length 4. You have four cards,
    each containing a number in the range [1, 9]. You should arrange the
    numbers on these cards in a mathematical expression using the operators
    ['+', '-', '*', '/'] and the parentheses '(' and ')' to get the value 24.

    You are restricted with the following rules:

        + The division operator '/' represents real division, not integer
        division.
            For example, 4 / (1 - 2 / 3) = 4 / (1 / 3) = 12.

        + Every operation done is between two numbers. In particular, we cannot
        use '-' as a unary operator.
            For example, if cards = [1, 1, 1, 1], the expression
            "-1 - 1 - 1 - 1" is not allowed.

        + You cannot concatenate numbers together
            For example, if cards = [1, 2, 1, 2], the expression "12 + 12" is
            not valid.

    Return true if you can get such expression that evaluates to 24, and false
    otherwise.

    ================================================
    FUNCTION: bool judgePoint24(vector<int>& cards);
    ================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: cards = [4,1,8,7]
    Output: true
    Explanation: (8-4) * (7-1) = 24

    --- Example 2 ---
    Input: cards = [1,2,1,2]
    Output: false


    *** Constraints ***
    cards.length == 4
    1 <= cards[i] <= 9

*/

#include <vector>
#include <cmath>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 57.93% */
/* Space Beats: 56.17% */

/* Time  Complexity: O(N! * N) */ // But for these Constraints it's alright.
/* Space Complexity: O(N)      */
class Solution {
    const double EPSILON = 1e-6;

public:
    bool judgePoint24(vector<int>& cards)
    {
        vector<double> values;
        for (const int& card_val : cards)
            values.push_back(static_cast<double>(card_val));

        return dfs(values);
    }

private:
    bool dfs(vector<double>& values)
    {
        const int N = values.size();

        if (values.size() == 1)
            return fabs(values[0] - 24.0) < EPSILON;

        for (int i = 0; i < N; i++)
        {
            for (int j = i+1; j < N; j++)
            {
                if (i == j)
                    continue;

                vector<double> next;
                for (int k = 0; k < N; k++)
                {
                    if (k != i && k != j) next.push_back(values[k]);
                }

                for (const double& val : compute(values[i], values[j]))
                {
                    next.push_back(val);

                    if (dfs(next))
                        return true;

                    next.pop_back();
                }
            }
        }

        return false;
    }

    vector<double> compute(double& a, double& b)
    {
        vector<double> res;
        res.push_back(a + b);
        res.push_back(a - b);
        res.push_back(b - a);
        res.push_back(a * b);

        if (fabs(b) > EPSILON)
            res.push_back(a / b);

        if (fabs(a) > EPSILON)
            res.push_back(b / a);

        return res;
    }
};
