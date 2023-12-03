#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ==============================
    96) Unique Binary Search Trees
    ==============================

    ============
    Description:
    ============

    Given an integer n, return the number of structurally unique BST's (binary
    search trees) which has exactly n nodes of unique values from 1 to n.

    ===============================
    FUNCTION: int numTrees(int n);
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
        ___________   ___________   ___________   ___________   ___________
        _____1_____   _____1_____   _____2_____   _____3_____   _____3_____
        ________3__   ________3__   __1_____3__   __2________   __1________
        ______2____   __________2   ___________   1__________   ____2______

    Input: n = 3
    Output: 5


    --- Example 2 ---
        _____
        __1__
        2___3

    Input: n = 1
    Output: 1

    *** Constraints ***
    1 <= n <= 19

*/

/*
    ------------
    --- IDEA ---
    ------------

    Recursive.

*/

/* Time  Beats:  5.05% */
/* Space Beats: 85.46% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Recursive {
public:
    int numTrees(int n)
    {
        return trees(1, n);
    }

    int trees(int low, int high)
    {
        if (low >= high)
            return 1;

        int total = 0;
        for (int i = low; i <= high; i++)
            total += trees(low, i - 1) * trees(i + 1, high);

        return total;
    }
};




/* Time  Beats:  5.35% */
/* Space Beats: 61.83% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_Recursive_Catalan {
public:
    int numTrees(int n)
    {
        return (int) catalan(n);
    }

private:
    int catalan(int n)
    {
        // Base case
        if (n <= 1)
            return 1;

        // Catalan(n) is sum of catalan(i) * catalan(n-i-1)
        int res = 0;
        for (int i = 0; i < n; i++)
            res += catalan(i) * catalan(n - i - 1);

        return res;
    }
};




/* Time  Beats:  100% */
/* Space Beats: 85.46% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution_DP_Catalan {
public:
    int numTrees(int n)
    {
        return (int) catalanDP(n);
    }

private:
    unsigned long int catalanDP(unsigned int n)
    {
        unsigned long int catalan[n + 1];

        // Initialize first two values
        catalan[0] = catalan[1] = 1;

        for (int i = 2; i <= n; i++)
        {
            catalan[i] = 0;

            for (int j = 0; j < i; j++)
                catalan[i] += catalan[j] * catalan[i - j - 1];
        }

        return catalan[n];
    }
};
