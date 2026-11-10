/*
    ============
    === HARD ===
    ============

    ===============================================
    3821) Find Nth Smallest Integer With K One Bits
    ===============================================

    ============
    Description:
    ============

    You are given two positive integers n and k.

    Return an integer denoting the nth smallest positive integer that has
    exactly k ones in its binary representation. It is guaranteed that the
    answer is strictly less than 2^50.

    ====================================================
    FUNCTION: long long nthSmallest(long long n, int k);
    ====================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: n = 4, k = 2
    Output: 9
    Explanation:
    The 4 smallest positive integers that have exactly k = 2 ones in their
    binary representations are:
        3 = 112
        5 = 1012
        6 = 1102
        9 = 10012


    --- Example 2 ---
    Input: n = 3, k = 1
    Output: 4
    Explanation:
    The 3 smallest positive integers that have exactly k = 1 one in their
    binary representations are:
        1 = 12
        2 = 102
        4 = 1002



    *** Constraints ***
    1 <= n <= 250
    1 <= k <= 50
    The answer is strictly less than 250.

*/

#include <cstring>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    TODO

*/

/* Time  Beats: 45.13% */
/* Space Beats: 67.26% */

/* Time  Complexity: O(50 * 50) */
/* Space Complexity: O(50 * 50) */
class Solution {
private:
    long long memo[50][51];

public:
    long long nthSmallest(long long n, int k)
    {
        long long result = 0LL;

        /* Memset */
        memset(memo, -1, sizeof(memo));

        int remaining_ones = k;
        for (int bit = 49; bit >= 0; bit--)
        {
            if (remaining_ones == 0)
                break;
            
            long long count = solve(bit - 1, remaining_ones);
            
            if (count < n)
            {
                n -= count;
                result |= (1LL << bit);

                --remaining_ones;
            }
        }

        return result;
    }

private: 
    long long solve(int idx, int ones)
    {
        if (ones == 0)
            return 1;

        if (idx < 0)
            return 0;

        if (memo[idx][ones] != -1)
            return memo[idx][ones];
        
        long long take = solve(idx - 1, ones - 1);
        long long skip = solve(idx - 1, ones    );
        
        return memo[idx][ones] = take + skip;
    }
};
