#include <iostream>
#include <vector>

/*
    ==============
    === MEDIUM ===
    ==============

    ============================
    386) Lexicographical Numbers
    ============================

    ============
    Description:
    ============

    Given an integer n, return all the numbers in the range [1, n] sorted in
    lexicographical order.

    You must write an algorithm that runs in O(n) time and uses O(1) extra
    space.

    ==========================================
    FUNCTION: vector<int> lexicalOrder(int n);
    ==========================================

    ===========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 13
    Output: [1,10,11,12,13,2,3,4,5,6,7,8,9]

    --- Example 2 ---
    Input: n = 2
    Output: [1,2]


    *** Constraints ***
    1 <= n <= 5 * 10^4

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  83.13% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(n) */
class Solution {
public:
    vector<int> result;
    int n;

    vector<int> lexicalOrder(int n)
    {
        this->n = n;
        result.reserve(n);
        dfs(0);
        return result;
    }

private:
    void dfs(int i)
    {
        if (i > n)
            return;

        if (i > 0)
            result.push_back(i);

        for (int j = (i == 0) ? 1 : 0; j <= 9; j++)
        {
            int x = 10*i + j;

            if (x > n)
                break;

            dfs(x);
        }
    }
};




/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 87.61% */
/* Space Beats: 96.05% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution_Iterative {
public:
    vector<int> lexicalOrder(int n)
    {
        vector<int> result(n);

        int x = 1;

        for (int i = 0; i < n; i++)
        {
            result[i] = x;

            if (x*10 > n)
            {
                if (x == n)
                    x /= 10;
                x++;

                while (x % 10 == 0)
                    x /= 10;
            }
            else
                x *= 10;
        }

        return result;
    }
};
