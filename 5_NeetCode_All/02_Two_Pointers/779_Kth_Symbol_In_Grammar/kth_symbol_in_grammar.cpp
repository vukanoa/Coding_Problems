#include <iostream>

/*
    ==============
    === MEDIUM ===
    ==============

    ===========================
    779) K-th Symbol in Grammar
    ===========================

    ============
    Description:
    ============

    We build a table of n rows (1-indexed). We start by writing 0 in the 1st
    row. Now in every subsequent row, we look at the previous row and replace
    each occurrence of 0 with 01, and each occurrence of 1 with 10.

        For example, for n = 3, the 1st row is 0, the 2nd row is 01, and the
        3rd row is 0110.

    Given two integer n and k, return the kth (1-indexed) symbol in the nth row
    of a table of n rows.

    =======================================
    FUNCTION: int kthGrammar(int n, int k);
    =======================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 1, k = 1
    Output: 0
    Explanation: row 1: 0

    --- Example 2 ---
    Input: n = 2, k = 1
    Output: 0
    Explanation:
    row 1: 0
    row 2: 01

    --- Example 3 ---
    Input: n = 2, k = 2
    Output: 1
    Explanation:
    row 1: 0
    row 2: 01

    *** Constraints ***
    1 <= n <= 30
    1 <= k <= 2^n - 1

*/

/*
    ------------
    --- IDEA ---
    ------------

    TODO
    (Waaaaaaaaaay too difficult. Don't even bother, it's not as important)

*/

/* Time  Beats: 100.00% */
/* Space Beats:  51.73% */

/* Time  Complexity: O(n) */
/* Space Complexity: O(1) */
class Solution {
public:
    int kthGrammar(int n, int k)
    {
        int curr = 0;

        int left  = 0;
        int right = 1 << (n-1);

        for (int i = 0; i < n-1; i++)
        {
            int mid = (left + right) / 2;

            if (k <= mid)
                right = mid;
            else
            {
                left  = mid + 1;
                curr = curr == 1 ? 0 : 1;
            }
        }

        return curr;
    }
};
