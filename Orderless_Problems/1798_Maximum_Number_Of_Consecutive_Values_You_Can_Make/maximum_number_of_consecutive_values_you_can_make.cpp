/*
    ==============
    === MEDIUM ===
    ==============

    ========================================================
    1798) Maximum Number of Concsecutive Values YOu Can Make
    ========================================================

    ============
    Description:
    ============

    You are given an integer array coins of length n which represents the n
    coins that you own. The value of the ith coin is coins[i]. You can make
    some value x if you can choose some of your n coins such that their values
    sum up to x.

    Return the maximum number of consecutive integer values that you can make
    with your coins starting from and including 0.

    =====
    Note: that you may have multiple coins of the same value.
    =====

    ========================================================
    FUNCTION: int getMaximumConsecutive(vector<int>& coins);
    ========================================================

    ==========================================================================
    ================================ EXAMPLES ================================
    ==========================================================================

    --- Example 1 ---
    Input: coins = [1,3]
    Output: 2
    Explanation: You can make the following values:
    - 0: take []
    - 1: take [1]
    You can make 2 consecutive integer values starting from 0.


    --- Example 2 ---
    Input: coins = [1,1,1,4]
    Output: 8
    Explanation: You can make the following values:
    - 0: take []
    - 1: take [1]
    - 2: take [1,1]
    - 3: take [1,1,1]
    - 4: take [4]
    - 5: take [4,1]
    - 6: take [4,1,1]
    - 7: take [4,1,1,1]
    You can make 8 consecutive integer values starting from 0.


    --- Example 3 ---
    Input: coins = [1,4,10,3,1]
    Output: 20


    *** Constraints ***
    coins.length == n
    1 <= n <= 4 * 10^4
    1 <= coins[i] <= 4 * 10^4

*/

#include <algorithm>
#include <vector>
using namespace std;

/*
    ------------
    --- IDEA ---
    ------------

    The intuition for this NOT intuitive at all, but it's possible to figure
    out once you lay out a few examples in front of yourself.

    This is the realization:
    If we reached number i, that means that we can make all values 0...i.
    So, if we add a coin with value j, we can also make values i+1...i+j.

    The only case when we can have a gap is the coin value is greater than
    i + 1. So we sort the coins to make sure we process smaller coins first.

    For example, let's assume that we can make all values 0...7.
    Adding a coin of value 5 allows us to make values 8..12 (7+1...7+5).

*/

/* Time  Beats: 96.66% */
/* Space Beats: 97.37% */

/* Time  Complexity: O(N * logN) */
/* Space Complexity: O(logN)     */ // C++'s sort function uses O(logN)
class Solution {
public:
    int getMaximumConsecutive(vector<int>& coins)
    {
        const int N = coins.size();

        /* Sort */
        sort(coins.begin(), coins.end());

        int max_val = 1;
        for (auto i = 0; i < N; ++i)
        {
            if (coins[i] > max_val)
                break;

            max_val += coins[i];
        }

        return max_val;
    }
};
