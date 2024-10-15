#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ====================================
    2938) Separate Black and White Balls
    ====================================

    ============
    Description:
    ============

    There are n balls on a table, each ball has a color black or white.

    You are given a 0-indexed binary string s of length n, where 1 and 0
    represent black and white balls, respectively.

    In each step, you can choose two adjacent balls and swap them.

    Return the minimum number of steps to group all the black balls to the
    right and all the white balls to the left.

    ===========================================
    FUNCTION: long long minimumSteps(string s);
    ===========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: s = "101"
    Output: 1
    Explanation: We can group all the black balls to the right in the following way:
    - Swap s[0] and s[1], s = "011".
    Initially, 1s are not grouped together, requiring at least 1 step to group them to the right.


    --- Example 2 ---
    Input: s = "100"
    Output: 2
    Explanation: We can group all the black balls to the right in the following way:
    - Swap s[0] and s[1], s = "010".
    - Swap s[1] and s[2], s = "001".
    It can be proven that the minimum number of steps needed is 2.


    --- Example 3 ---
    Input: s = "0111"
    Output: 0
    Explanation: All the black balls are already grouped to the right.


    *** Constraints ***
    1 <= n == s.length <= 10^5
    s[i] is either '0' or '1'.

*/

/*
    ------------
    --- IDEA ---
    ------------

    Whenever we are asked to COUNT the number of steps or something similar,
    that usually(almost always) means that we should NOT actually modify the
    Input, which further means that the Solution is much simpler than you're
    currently thinking about.

    Instead of devising and designing a complicated algorithm which would sort
    these 0s and 1s into its proper place, all we have to do is actually
    calculate what is the amount of positions that each, say 1, is off of his
    "ought" position.

    Let's consider an example:
     _________
    |         |
    |         v
    |   0  0  1  0  0  1  0  1
    |   0  1  2  3  4  5  6  7
    |
    |_______________________________________
                                           |
    Where should be the final position of THIS 1?

    It should be at index 5. But why? It's VERY important to ask yourself the
    "Why?" question, even if it seems absurdly obvious.

    So, why?
    BECAUSE there are a total of N elements and BECAUSE there are exactly 2
    1s to the right of THIS 1. Let's calculate:

        total: 8
        last_possible_index: total-1 ==> 7
        current_index: 2
        ones_to_the_right: 2 // At positions: 5 and 7


        Calculation:
            steps = last_possible_index - ones_to_the_right - current_index

            i.e.

            steps =         7           -         2         -      2

            steps = 4

        That means, that to put THIS 1, to the proper place, in MINIMAL steps,
        it would require steps=4 amount of steps.


    If we do that for EVERY existing 1, and add all of those steps, that's our
    desired result.

    We can do it in 2 passes, therefore the entire Time Complexity is: O(n)

*/

/* Time  Beats: 73.47% */
/* Space Beats:  6.74% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    long long minimumSteps(string s)
    {
        ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0); // Accelerates

        const int n = s.length();
        vector<int> ones_to_the_right(n+1, 0);

        for (int i = n-1; i >= 0; i--)
        {
            if (s[i] == '1')
                ones_to_the_right[i] = ones_to_the_right[i+1] + 1;
            else
                ones_to_the_right[i] = ones_to_the_right[i+1];
        }

        long long result = 0;
        for (int i = n-2; i >= 0; i--)
        {
            if (s[i] == '1')
            {
                result += (n-1 - ones_to_the_right[i+1]) - i;
            }
        }

        return result;
    }
};
