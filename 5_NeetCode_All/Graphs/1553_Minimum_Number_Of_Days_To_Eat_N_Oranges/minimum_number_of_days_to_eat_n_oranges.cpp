#include <iostream>
#include <unordered_map>

/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    1553) Minimum NUmber Of Days To Eat N Oranges
    =============================================

    ============
    Description:
    ============

    There are n oranges in the kitchen and you decided to eat some of these
    oranges every day as follows:

        - Eat one orange.

        - If the number of remaining oranges n is divisible by 2 then you can
          eat n / 2 oranges.

        - If the number of remaining oranges n is divisible by 3 then you can
          eat 2 * (n / 3) oranges.

    You can only choose one of the actions per day.

    Given the integer n, return the minimum number of days to eat n oranges.

    ===============================
    FUNCTION: int minDays(int n);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 10
    Output: 4
    Explanation: You have 10 oranges.
    Day 1: Eat 1 orange,  10 - 1 = 9.
    Day 2: Eat 6 oranges, 9 - 2*(9/3) = 9 - 6 = 3. (Since 9 is divisible by 3)
    Day 3: Eat 2 oranges, 3 - 2*(3/3) = 3 - 2 = 1.
    Day 4: Eat the last orange  1 - 1  = 0.
    You need at least 4 days to eat the 10 oranges.


    --- Example 2 ---
    Input: n = 6
    Output: 3
    Explanation: You have 6 oranges.
    Day 1: Eat 3 oranges, 6 - 6/2 = 6 - 3 = 3. (Since 6 is divisible by 2).
    Day 2: Eat 2 oranges, 3 - 2*(3/3) = 3 - 2 = 1. (Since 3 is divisible by 3)
    Day 3: Eat the last orange  1 - 1  = 0.
    You need at least 3 days to eat the 6 oranges.


    *** Constraints ***
    1 <= n <= 2 * 10^9

*/

/*
    ------------
    --- IDEA ---
    ------------

    We've converted O(3^n) all the way down to O(n) with this approach, however
    for this problem, that's unacceptable. It gives Stack-overflow for:
        n = 85702

    Stack gets out of the allocated Stack fram for this program.

*/

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    int minDays(int n)
    {
        std::unordered_map<int, int> umap;

        return dfs(n, umap);
    }

private:
    int dfs(int oranges, std::unordered_map<int, int>& umap)
    {
        if (oranges == 0)
            return 0;

        if (umap.count(oranges))
            return umap[oranges];

        int one   = INT_MAX;
        int div_2 = INT_MAX;
        int div_3 = INT_MAX;

        if (oranges % 3 == 0)
            div_3 =  1 + dfs(oranges - 2*oranges/3, umap);

        if (oranges % 2 == 0)
            div_2 = 1 + dfs(oranges - oranges/2, umap);

        one = 1 + dfs(oranges - 1, umap);

        umap.insert( {oranges, std::min({one, div_2, div_3}) } );

        return umap[oranges];
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO
    Very cool idea.

*/

/* Time  Beats: 97.78% */
/* Space Beats: 56.01% */

/* Time  Complexity: O(log2(n)) */
/* Space Complexity: O(log2(n)) */
class Solution {
public:
    int minDays(int n)
    {
        std::unordered_map<int, int> umap;
        umap.insert({0, 0});
        umap.insert({1, 1});

        return dfs(n, umap);
    }

private:
    int dfs(int oranges, std::unordered_map<int, int>& umap)
    {
        if (umap.count(oranges))
            return umap[oranges];

        int div_2 = 1 + oranges % 2 + dfs(oranges / 2, umap);
        int div_3 = 1 + oranges % 3 + dfs(oranges / 3, umap);

        umap.insert( { oranges, std::min(div_2, div_3) } );

        return umap[oranges];
    }
};
