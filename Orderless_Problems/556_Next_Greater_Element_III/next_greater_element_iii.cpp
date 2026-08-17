/*
    ==============
    === MEDIUM ===
    ==============

    =============================
    556) Next Greater Element III
    =============================

    ============
    Description:
    ============

    Given a positive integer n, find the smallest integer which has exactly the
    same digits existing in the integer n and is greater in value than n. If no
    such positive integer exists, return -1.

    =====
    Note: that the returned integer should fit in 32-bit integer, if there is a
          valid answer but it does not fit in 32-bit integer, return -1. 
    =====

    ========================================
    FUNCTION: int nextGreaterElement(int n);
    ========================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 12
    Output: 21

    --- Example 2 ---
    Input: n = 21
    Output: -1


    *** Constraints ***
    1 <= n <= 2^31 - 1

*/

#include <algorithm>
#include <climits>
#include <string>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 100.00% */
/* Space Beats:  85.95% */

/* Time  Complexity: O(N) */
/* Space Complexity: O(N) */
class Solution {
public:
    int nextGreaterElement(int n)
    {
        string digits = to_string(n);

        my_next_permutation(digits);

        long long result = stoll(digits);
        return (result > INT_MAX || result <= n) ? -1 : result;
    }

private:
    void my_next_permutation(string& s)
    {
        const int N = s.size();
        int i = N - 2;

        while (i >= 0 && s[i] >= s[i + 1])
            i--;

        if (i < 0)
            return;

        int j = N - 1;
        while (s[j] <= s[i])
            j--;

        swap(s[i], s[j]);
        reverse(s.begin() + i + 1, s.end());
    }
};
