/*
    ==============
    === MEDIUM ===
    ==============

    =============================================
    1497) Check If Array Pairs Are Divisible By K
    =============================================

    ============
    Description:
    ============

    Given an array of integers arr of even length n and an integer k.

    We want to divide the array into exactly n / 2 pairs such that the sum of
    each pair is divisible by k.

    Return true If you can find a way to do that or false otherwise.

    ===============================
    FUNCTION:
    ===============================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    <++>

    --- Example 2 ---

    --- Example 3 ---

    *** Constraints ***

*/

#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 98.62% */
/* Space Beats: 97.49% */

/* Time  Complexity: O(n + k) */
/* Space Complexity: O(k)     */
class Solution {
public:
    bool canArrange(vector<int>& arr, int k)
    {
        const int N = arr.size();
        vector<int> freq(k, 0);

        for (int i = 0; i < N; i++)
        {
            int remainder = (k + arr[i] % k) % k;
            freq[remainder]++;
        }

        if (freq[0] & 1)
            return false;

        for (int remainder = 1; remainder <= k / 2; remainder++)
        {
            if (freq[remainder] != freq[k - remainder])
                return false;
        }

        return true;
    }
};
